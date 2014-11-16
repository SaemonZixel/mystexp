/***************************************************************************
 *   Copyright (C) 2006 by Saemon Zixel                                    *
 *   saemon@pochta.ru                                                      *
 *                                                                         *
 ***************************************************************************/


#include "vmtypes.h"
#include "memmng.h" // используется функция1, функция2...
#include "imagemng.h"
#include "primitivemng.h"

#define StdSizeFor_tmps sizeof(objNum)*10
#define StdSizeFor_args sizeof(objNum)*7

#define CALL        0	// 00000000b
#define SM          64	// 01000000b
#define LD          128	// 10000000b
#define RET         192	// 11000000b

#define trg_self    0	// 00000000b
#define trg_super   8	// 00001000b
#define trg_trgobj  16	// 00010000b
#define trg_none    24	// 00011000b
#define trg_lit     32	// 00100000b
#define trg_tmp     40	// 00101000b
#define trg_arg     48	// 00110000b
#define trg_inst    56	// 00111000b
#define trg_havetrg 32	// 00100000b

#define src_self    0	// 00000000b
#define src_super   1	// 00000001b
#define src_trgobj  2	// 00000010b
#define src_none    3	// 00000011b
#define src_lit     4	// 00000100b
#define src_tmp     5	// 00000101b
#define src_arg     6	// 00000110b
#define src_inst    7	// 00000111b
#define src_havesrc 4	// 00000100b

#define cmd_mask   192	// 11000000b
#define trg_mask   56	// 00111000b
#define src_mask   7	// 00000111b

#define firstbit   128	// 10000000b

objNum ClassForMethodState = 0;

int getNextInstruction(objNum methodStateObj, unsigned char* type, char* trg_type, char* src_type, long* trg, long* src) { //(перевод: получить следующую инструкцию)
    unsigned char commandByte, trgByte, srcByte;
    struct MethodState *methodState;
    objNum bytecodeObj, bytecodeOffset;
    unsigned char *bytecode;

#ifdef primZero
    if(getNextInstructionHook(type, trg_type, src_type, trg, src)) return 0;
#endif

    // берём указатель на содержимое MethodState
    methodState = (struct MethodState*) &Image[methodStateObj]->data;
    // из метода берём байткод и сравниваем размер
    bytecodeObj = ((struct MethodObject *) &Image[methodState->method]->data)->bytecode;
    // сразу вазьмём указатель на начяло байткода
    bytecode = &Image[bytecodeObj]->dataAsChar;
    // также вазмём текущее смещение в байт-коде
    bytecodeOffset = Image[methodState->bytecodeOffset]->data;

    // стоим ли мы в конце сегмента байткода или ещё есть возможность считать инструкцию
    if(Image[bytecodeObj]->size <= bytecodeOffset) return 1;

    // 1ый байт - "команда"
    commandByte = bytecode[bytecodeOffset];
    *type = commandByte & cmd_mask;
    *trg_type = commandByte & trg_mask;
    *src_type = commandByte & src_mask;

    // теперь если есть "параметры"
    if(commandByte & trg_havetrg) { // есть ли trg в следующем байте
        //  читаем 2ой байт
        bytecodeOffset++;
        trgByte = bytecode[bytecodeOffset];
        *trg = trgByte & 127;
        /* далее можно циклически считывать цепочку байтов пока у предыдущего байта поднят первый бит
           тем самым увеличиваея разрядность (7 -> 14 -> 21 -> 28...)
           но я не думаю что это будет использоватся */
    }

    if(commandByte & src_havesrc) { // есть ли src в байткоде
        // читаем текущий байт
        bytecodeOffset++;
        srcByte = bytecode[bytecodeOffset];
        *src = srcByte & 127;
        /* тоже с цепочкой что и выше */
    }

    bytecodeOffset++; //должен указывать на следующий непрочитанный байт
    Image[methodState->bytecodeOffset]->data = bytecodeOffset;
    return 0; //предположим что всё нормально
}

int returnInPreviousMethod(objNum *methodStateObj, int isMethodReturn) { // (перевод: вернутся в предшествующий метод)
    struct MethodState * currentMethodState;
    objNum returnTo, previousMethodState;

#ifdef primZero
    if(returnInPreviousMethodHook(isMethodReturn)) return;
#endif

#ifdef debug
	if(isMethodReturn) puts("Method Return");
	else puts("Return");
#endif
    //contextState = (struct MethodState *) &Image[vmContext->currentMethodState_obj]->data;
    currentMethodState = (struct MethodState *) &Image[*methodStateObj]->data;
    if(isMethodReturn){
	// по команде RET (т.е. возврат из метода) ...
	returnTo = currentMethodState->returnTo;
    } else {
	// если кончился байткод то просто возвращаемся в предыдущий контекст
	returnTo = currentMethodState->previousMethodState;
    }
    // если returnTo = 0, который у нас есть, то выходить некуда!
    if(returnTo == 0) return -1; // -1 обозначяет что MethodState кончились...

    // цикл пока не дайдём до нужного метод
    do{
        // берём текуший MethodState
	currentMethodState = (struct MethodState *) &Image[*methodStateObj]->data;
	previousMethodState = currentMethodState->previousMethodState; // предыдущий контекст

	currentMethodState->previousMethodState = 0;
	currentMethodState->returnTo = 0;

	// переключаемся на предыдущий contextState
	*methodStateObj = previousMethodState;

	// если просто кончился байткод (т.е. небыло команды RET), то просто возвращаемся в предыдущий контекст
	if(!isMethodReturn) break;

    }while(*methodStateObj != returnTo); // если недостигли заданный MethodState то повтаряем ещё раз

    return 0;
}

void enterInBlock(objNum *methodStateObj, objNum targetBlock) {
    struct MethodState *methodState, *oldMethodState;
    objNum newMethodStateObj;

    struct BlockObject *block;
    struct MethodState *block_savedMethodState;
    unsigned long argStart, argCount, tmpsSize; // размер tmps сегмента
    objNum arg;

    oldMethodState = (struct MethodState *) &Image[*methodStateObj]->data;
    newMethodStateObj = newObj(Image[*methodStateObj]->class, sizeof(struct MethodState), 1);
    methodState = (struct MethodState *) &Image[newMethodStateObj]->data;

	// ВХОДИМ В БЛОК
#ifdef debug
	puts("enter in Block");
#endif
	block = (struct BlockObject*) &Image[targetBlock]->data;
	block_savedMethodState = (struct MethodState *) &Image[block->SavedState]->data;
	tmpsSize = Image[block->tmpCount]->data + Image[block->argCount]->data;
	methodState->self = block_savedMethodState->self;
        methodState->method  = targetBlock;
	methodState->bytecodeOffset = newObj(Image[oldMethodState->bytecodeOffset]->class, 4, 0);
	Image[methodState->bytecodeOffset]->data = 0;
        if(tmpsSize * 4 > Image[block_savedMethodState->tmps_obj]->size)
	  resizeObj(block_savedMethodState->tmps_obj, tmpsSize * 4);
	methodState->tmps_obj = block_savedMethodState->tmps_obj;
	// иначе 2 одновременно работающих блока подерутся...
	methodState->args_obj = newObj(Image[block_savedMethodState->args_obj]->class,Image[block_savedMethodState->args_obj]->size,Image[block_savedMethodState->args_obj]->formemmng);
	methodState->targetObj = oldMethodState->targetObj;

	// сохроним в переменную с какой позиции надо складывать палученные аргументы и сколько их должно быть (не зависит от реального их количества "больше"/"меньше")
	argStart = Image[block->tmpCount]->data;
	argCount = Image[block->argCount]->data;
	// копируем палученные аргументы в конец сегмента tmps
	while( argCount != 0 ){
	  argCount--; // т.к. счет идёт с нуля... заодно и счетчик уменьшаем
	  arg = (&Image[oldMethodState->args_obj]->data)[argCount];
	  (&Image[methodState->tmps_obj]->data)[argStart + argCount] = arg;
	}

    // незабываем указать старый MethodState как предыдущей (в который можно будет вернутся)
    methodState->previousMethodState = *methodStateObj;
    // при интсрукции RET мы можем вирнутся только в контекст который был перед методом создавшим этот блок
    methodState->returnTo = block_savedMethodState->returnTo; //

    *methodStateObj = newMethodStateObj;
}

void enterInMethod(objNum *methodStateObj, objNum targetMethod, objNum self) {
    struct MethodState *methodState, *oldMethodState;
    objNum newMethodStateObj;
    objNum classForArgsnTmps, classForInteger;

    struct MethodObject *method;
    unsigned long argStart, argCount, tmpsSize; // размер tmps сегмента
    objNum arg;

    oldMethodState = (struct MethodState *) &Image[*methodStateObj]->data;
    newMethodStateObj = newObj(Image[*methodStateObj]->class, sizeof(struct MethodState), 1);
    methodState = (struct MethodState *) &Image[newMethodStateObj]->data;

	// ВХОДИМ В МЕТОД
	method =(struct MethodObject*) &Image[targetMethod]->data;
#ifdef debug
	printf("enter in obj(%i) method: %s class: %s\n",targetMethod,strndup((char *) &Image[method->name]->data, Image[method->name]->size),
	strndup((char *) &Image[((struct ClassObject*)&Image[method->InTheClass]->data)->name]->data, Image[((struct ClassObject*)&Image[method->InTheClass]->data)->name]->size));
#endif
	tmpsSize = Image[method->tmpCount]->data + Image[method->argCount]->data;
        methodState->self = self;
        methodState->method = targetMethod;
	methodState->bytecodeOffset = newObj(Image[oldMethodState->bytecodeOffset]->class, 4, 0);
	Image[methodState->bytecodeOffset]->data = 0;
        methodState->tmps_obj = newObj(Image[oldMethodState->tmps_obj]->class, tmpsSize * 4, 1);
        methodState->args_obj = newObj(Image[oldMethodState->args_obj]->class, StdSizeFor_args, 1);
	methodState->targetObj = oldMethodState->targetObj;

	// сохроним в переменную количество временных переменных чтоб знать куда складывать палученные аргументы
	argStart = Image[method->tmpCount]->data;
	argCount = Image[method->argCount]->data;
	// копируем палученные аргументы в конец сегмента tmps
	while( argCount != 0 ){
	  argCount--;
	  arg = (&Image[oldMethodState->args_obj]->data)[argCount];
	  (&Image[methodState->tmps_obj]->data)[argStart + argCount] = arg;
	}

  // незабываем указать старый MethodState как предыдущей (в который можно будет вернутся)
    methodState->previousMethodState = *methodStateObj;
 // при интсрукции RET мы можем вирнутся только в (?предыдущий?) контекст
    methodState->returnTo = methodState->previousMethodState;

    *methodStateObj = newMethodStateObj;
}

objNum SearchingForMethod(objNum TargetClass, objNum SymbolObj) { // (перевод: поиск метода ) надо переделать в рекурсию!
    struct ClassObject * currentClass;
    objNum * currentMethods;
    objNum currentClassObj;
    int row, i, methodsInDict;
    char * currentMethodName, * ourMethodName;

    if(TargetClass == 0){
     puts("SearchingForMethod: Error ! message send to 0");
    }

    // берём строковое (char*) предстовление искомого метода
    ourMethodName = &Image[SymbolObj]->dataAsChar;

    // узнаём класс TargetObject и сразу берём указатель на содержимое этого класса (объекта-класса)
    currentClassObj = TargetClass;
    currentClass = (struct ClassObject *) &Image[currentClassObj]->data;

    // начинается цикл поиска метода вверх по ирархии классов, закончится цикл на классе: Class т.к. его super он-же сам
    while(1){

     // смотрем есть ли словарь у класса, и следовательно есть ли методы у класса, иначе пропускаем
     if((Image[currentClassObj]->size >= 12) && (currentClass->methods != 0)){

	// вычисляем количество объектов (номеров объектов) в славаре (objNum = 4 байта, а размер обьекта (size) в байтах)
	methodsInDict = Image[currentClass->methods]->size / 4;
	// берём указатель на таблицу словарных записей, по которой мы будем искать метод
	currentMethods = &Image[currentClass->methods]->data;

	// перебираем словарные записи, при этом шагаем через один объект т.к. 0-key 1-value 2-key 3-value... а нам нужны только key
	for(row = 0 ; row < methodsInDict ; row += 2) {
            // берём содержимое объекта т.е. строку
            currentMethodName = &Image[currentMethods[row]]->dataAsChar;

            // сравниваем строки только одинаковой длиной
            if(Image[currentMethods[row]]->size == Image[SymbolObj]->size)
                // начинаем посимвольное сравнение
                for(i = 0 ; i < Image[currentMethods[row]]->size ; i++) {
                    // символ не совпал значит разные -> выходим
                    if(currentMethodName[i] != ourMethodName[i])
                        break;
                    // если достигли конца строки в обоих строках, значит строки совпали и мы нашли то что искали
                    if((i == Image[SymbolObj]->size - 1 ) & (currentMethodName[i] == ourMethodName[i]))
                        return currentMethods[row+1];
                }

        }
     }
     // если мы дошли сюда значит метод ещё не нашли, проверяем есть ли возможность поднятся выше классом...
     if(currentClassObj == currentClass->Super)
         return 0; // мы уже поднялись до последнего класса (Class) и рескуем попасть в бесконечный цикл

     // ... если можно то поднимаемся на класс выше
     currentClassObj = currentClass->Super;
     currentClass = (struct ClassObject *) &Image[currentClassObj]->data;
    }
}

int executeInstruction(objNum *methodStateObj, unsigned char type, char trg_type, char src_type, long trg, long src){
struct MethodState *methodState;
struct MethodObject *method;

objNum LD_transit;
objNum SM_message, SM_method, SM_newSelf;
objNum CALL_firstData, CALL_secondData; //

	// подготовим указатели на содержимое MethodState и метода
	methodState = (struct MethodState *) &Image[*methodStateObj]->data;
	method = (struct MethodObject *) &Image[methodState->method]->data;

	switch( type ){
		case LD:
			// сначяло берём...
			switch( src_type ){
			   case src_lit:
			   		LD_transit = (&Image[method->literals]->data)[src];
					break;
			   case src_tmp:
			   		LD_transit = (&Image[methodState->tmps_obj]->data)[src];
					if(Image[methodState->tmps_obj]->size < (src+1)*4){
					 puts("LD: src tmps out of range!");
					}
					break;
			   case src_arg:
			   		LD_transit = (&Image[methodState->args_obj]->data)[src];
					if(Image[methodState->args_obj]->size < (src+1)*4){
					 puts("LD: src args out of range!");
					}
					break;
			   case src_inst:
			   		LD_transit = (&Image[methodState->self]->data)[src];
					if(Image[methodState->self]->size < (src+1)*4){
					 puts("LD: src inst out of range!");
					}
					break;
			   case src_self:
			   		LD_transit = methodState->self;
					break;
			   case src_super:
			   		LD_transit = ((struct ClassObject *) &Image[method->InTheClass]->data)->Super;
					break;
			   case src_trgobj:
			   		LD_transit = methodState->targetObj;
					break;
			   case src_none:
			   		LD_transit = 0; // будем считать что это ноль, а вообще как сдесь реагировать неизвестно...
					break;
			}
			if(ImageLimit <= LD_transit) puts("LD: LD_transit >= ImageLimit!");
			else if(Image[LD_transit] == 0) puts("LD: LD_transit - this object not available!");

			// ...а теперь кладём
			switch( trg_type ){
			   case trg_lit:
			   		(&Image[method->literals]->data)[trg] = LD_transit;
					// вообще-то так делать нельзя
					//return -1; // возвращаем ошибку
					break;
			   case trg_tmp:
			   		(&Image[methodState->tmps_obj]->data)[trg] = LD_transit;
					if(Image[methodState->tmps_obj]->size < (trg+1)*4){
					 puts("LD: trg tmps out of range!");
					}
					break;
			   case trg_arg:
			   		(&Image[methodState->args_obj]->data)[trg] = LD_transit;
					if(Image[methodState->args_obj]->size < (trg+1)*4){
					 puts("LD: trg args out of range!");
					}
					break;
			   case trg_inst:
			   		(&Image[methodState->self]->data)[trg] = LD_transit;
					if(Image[methodState->self]->size < (trg+1)*4){
					 puts("LD: trg inst out of range!");
					}
					break;
			   case trg_self:
			   		methodState->self = LD_transit;
					// вообще-то так делать нельзя
					//return -1; // возвращаем ошибку
					break;
			   case trg_super:
			   		// вот так точно нельзя делать
					((struct ClassObject *) &Image[method->InTheClass]->data)->Super = LD_transit;
					//return -1; // возвращаем ошибку
					break;
			   case trg_trgobj:
			   		// так можно делать только в специальных случаях
			   		methodState->targetObj = LD_transit;
					break;
			   case trg_none:
			   		// и что мы должне сдесь делать ?
					break;
			}
			break;
		case SM:
			// узнаём кому адресованно сообщение, и кладём его в SM_newSelf
			switch( trg_type ){
			   case trg_lit:
			   		SM_newSelf = (&Image[method->literals]->data)[trg];
					break;
			   case trg_tmp:
			   		SM_newSelf = (&Image[methodState->tmps_obj]->data)[trg];
					if(Image[methodState->tmps_obj]->size < trg*4){
					 puts("SM: trg tmps out of range!");
					}
					break;
			   case trg_arg:
			   		SM_newSelf = (&Image[methodState->args_obj]->data)[trg];
					if(Image[methodState->args_obj]->size < trg*4){
					 puts("SM: trg args out of range!");
					}
					break;
			   case trg_inst:
			   		SM_newSelf = (&Image[methodState->self]->data)[trg];
					if(Image[methodState->self]->size < trg*4){
					 puts("SM: trg inst out of range!");
					}
					break;
			   case trg_self:
			   		SM_newSelf = methodState->self;
					break;
			   case trg_super:
			   		// а сдесь сообщение адресованно к self, но будет искатся классом выше
					SM_newSelf = ((struct ClassObject *) &Image[method->InTheClass]->data)->Super;
					break;
			   case trg_trgobj:
			   		SM_newSelf = methodState->targetObj;
					break;
			   case trg_none:
			   		// это как ?
					return -1;
					break;
			}
			switch( src_type ){
			   case src_lit:
			   		SM_message = (&Image[method->literals]->data)[src];
					break;
			   case src_tmp:
			   		SM_message = (&Image[methodState->tmps_obj]->data)[src];
					if(Image[methodState->tmps_obj]->size < src*4){
					 puts("SM: src tmps out of range!");
					}
					break;
			   case src_arg:
			   		SM_message = (&Image[methodState->args_obj]->data)[src];
					if(Image[methodState->args_obj]->size < src*4){
					 puts("SM: src args out of range!");
					}
					break;
			   case src_inst:
			   		SM_message = (&Image[methodState->self]->data)[src];
					if(Image[methodState->self]->size < src*4){
					 puts("SM: src inst out of range!");
					}
					break;
			   case src_self:
			   		SM_message = methodState->self;
					break;
			   case src_super:
			   		// а сдесь сообщение адресованно к self, но будет искатся классом выше
					SM_message = ((struct ClassObject *) &Image[method->InTheClass]->data)->Super;
					break;
			   case src_trgobj:
			   		SM_message = methodState->targetObj;
					break;
			   case src_none:
			   		// это как ?
					return -1;
					break;
			}
			if(ImageLimit <= SM_newSelf) puts("SM: SM_newSelf >= ImageLimit!");
			else if(Image[SM_newSelf] == 0) puts("SM: SM_newSelf - this object not available!");

			// если это вызов блока то входим в него и всё
			if(SM_message == 0) { // сообщение пустое значит SM_newSelf это блок, и нам надо в него войти
			  SM_method = SM_newSelf;
			  enterInBlock(methodStateObj, SM_method);
			  // на этом всё
			  break;
			}

			// сдесь у нас тонкость, если сообщение шлетса суперклассу то надо это сделать явно (т.е. использовать класс текущего класса).
			if(trg_type != trg_super)
			    SM_method = SearchingForMethod(Image[SM_newSelf]->class, SM_message); // ищем в MetaClass текущего класса
			else {
			    SM_method = SearchingForMethod(SM_newSelf, SM_message); // ищем в текущем классе
			    SM_newSelf = methodState->self;
			     }

			// проверяем нашли ли метод
			if(SM_method == 0){
			   // эти две строчки аш блещат своей красотой и краткостью ;)
			   if(trg_type != trg_super) printf("Message Not Understoode '%s' -> %i(class %s)\n",strndup((char*) &Image[SM_message]->data, Image[SM_message]->size), Image[SM_newSelf]->class,strndup((char*) &Image[Image[Image[SM_newSelf]->class]->data]->data,Image[Image[Image[SM_newSelf]->class]->data]->size));
			   else printf("Message Not Understoode '%s' -> %i(class %s)\n",strndup((char*) &Image[SM_message]->data, Image[SM_message]->size),((struct ClassObject *) &Image[method->InTheClass]->data)->Super, strndup((char*) &Image[Image[((struct ClassObject *) &Image[method->InTheClass]->data)->Super]->data]->data,Image[Image[((struct ClassObject *) &Image[method->InTheClass]->data)->Super]->data]->size));
			   return -2;
			}

			enterInMethod(methodStateObj, SM_method, SM_newSelf);
			break;
		case RET: // только возврат из метода (^)
			switch( trg_type ){
			   case trg_lit:
			   		methodState->targetObj = (&Image[method->literals]->data)[trg];;
					break;
			   case trg_tmp:
			   		methodState->targetObj = (&Image[methodState->tmps_obj]->data)[trg];
					if(Image[methodState->tmps_obj]->size < trg*4){
					 puts("RET: trg tmps out of range!");
					}
					break;
			   case trg_arg:
			   		methodState->targetObj = (&Image[methodState->args_obj]->data)[trg];
					if(Image[methodState->args_obj]->size < trg*4){
					 puts("RET: trg args out of range!");
					}
					break;
			   case trg_inst:
			   		methodState->targetObj = (&Image[methodState->self]->data)[trg];
					if(Image[methodState->self]->size < trg*4){
					 puts("RET: trg inst out of range!");
					}
					break;
			   case trg_self:
			   		methodState->targetObj = methodState->self;
					break;
			   case trg_super:
					methodState->targetObj = ((struct ClassObject *) &Image[method->InTheClass]->data)->Super;
					break;
			   case trg_trgobj: // Хммм... забавно...
			   		methodState->targetObj = methodState->targetObj;
					break;
			   case trg_none:
			   		// это как ?
					return -1;
					break;
			}
			if(ImageLimit <= methodState->targetObj){
			  puts("RET: vmContext->targetObj >= ImageLimit!");
			}
			else if(Image[methodState->targetObj] == 0){
			 puts("RET: vmContext->targetObj - this object not available!");
			}
			return returnInPreviousMethod(methodStateObj, 1); // 1 -> isMethodReturn=true
			break;
		case CALL:
			if(src_type & src_havesrc){
			 // расширенный вызов
			 switch(trg_type){
				case trg_lit: CALL_firstData = (&Image[method->literals]->data)[trg]; break;
				case trg_tmp: CALL_firstData = (&Image[methodState->tmps_obj]->data)[trg]; break;
				case trg_arg: CALL_firstData = (&Image[methodState->args_obj]->data)[trg]; break;
				case trg_inst: CALL_firstData = (&Image[methodState->self]->data)[trg]; break;
				default: puts("CALL: Invalid trg_type"); return 1;
			 }
			 switch(src_type){
				case src_lit: CALL_secondData = (&Image[method->literals]->data)[src]; break;
				case src_tmp: CALL_secondData = (&Image[methodState->tmps_obj]->data)[src]; break;
				case src_arg: CALL_secondData = (&Image[methodState->args_obj]->data)[src]; break;
				case src_inst: CALL_secondData = (&Image[methodState->self]->data)[src]; break;
			 }
			 return extendedCall(CALL_firstData, CALL_secondData, *methodStateObj);
			} else {
			 // простой вызов, внутренние примитивы
			 if(trg_type & trg_havetrg) return internalCall((int) trg, *methodStateObj);
			 else return internalCall((int) 0, *methodStateObj); // если не указан не trg не src то падрузумевается...(?)
			}
			break;
	}
	return 0;
}

int continueContext(objNum methodState){ // (перев. продолжить контекст)
unsigned char type, trg_type, src_type;
long trg, src;
objNum currentMethodStateObj;

int isEnd;
int result;

	if((ClassForMethodState == 0) && (Image[methodState]->class != 0)) ClassForMethodState = Image[methodState]->class;

	currentMethodStateObj = methodState;
	do{
	  // берём инструкцию
	  isEnd = getNextInstruction(currentMethodStateObj, &type, &trg_type, &src_type, &trg, &src);
	  if(isEnd) { // если кончился bytecode
	    // проверяем не кончились ли contextState
	    if(((struct MethodState *) &Image[currentMethodStateObj]->data)->previousMethodState == 0){ result = -1; break;}
	    // если мы в конце то возвращаемся в предыдущий контекст (без разницы блок или метод)
	    result = returnInPreviousMethod(&currentMethodStateObj, 0);
	  } else {
	    // иначе выполняем инструкцию
	    result = executeInstruction(&currentMethodStateObj, type, trg_type, src_type, trg, src);
	    if(result == -2) puts("MethodNotFound!");
	  }
	}while(result == 0); // если всё хорошо повтаряем ещё раз
	// прадублируем на случай если RET был совершен из блока (для блока создаётся "копия контекста" метода)
	((struct MethodState*) &Image[methodState]->data)->targetObj = ((struct MethodState*) &Image[currentMethodStateObj]->data)->targetObj;
#ifdef primZero
//	continueContextExitHook(result, vmContext);
#endif

#ifdef debug
	if(result < 0) printf("Error ! (bytecodeOffset: %i, bytecode: %s)\n",vmContext->bytecodeOffset,vmContext->bytecode);
	else printf("Normal Exit\n");
#endif
	return result;
	// -1 - Встречена RET или просто конец байткода, но возвращатся некуда (достигнут последний контекст)
	// -2 - метод не найден (SearchingForMethod сказал)
}

int doMethod(objNum Method, objNum self, objNum * trgObj) { // выполнить метод...
objNum tempMethodStateObj;
struct MethodState *tempMethodState;
struct MethodObject *method;
int result, tmpsSize;

#ifdef debug
	puts("doMethod: execute Method");
#endif

	tempMethodStateObj = newObj(ClassForMethodState, sizeof(struct MethodState), 1);
	tempMethodState = (struct MethodState *) &Image[tempMethodStateObj]->data;
	method = (struct MethodObject *) &Image[Method]->data;
	tmpsSize = Image[method->tmpCount]->data + Image[method->argCount]->data;

	// загружаем в наш стартовый MethodState указанный метод
	tempMethodState->self = self;
	tempMethodState->method = Method;
	tempMethodState->bytecodeOffset = newObj(Image[method->argCount]->class, 4, 0);
        tempMethodState->tmps_obj = newObj(Image[method->literals]->class, tmpsSize * 4, 1);
        tempMethodState->args_obj = newObj(Image[method->literals]->class, StdSizeFor_args, 1);
	tempMethodState->targetObj = *trgObj;
	tempMethodState->previousMethodState = 0;
	tempMethodState->returnTo = 0;

	// подстраховываемся
	Image[tempMethodState->bytecodeOffset]->data = 0;

	// теперь запускаем наш MethodState
	result = continueContext(tempMethodStateObj);

	if(result > -2) *trgObj = tempMethodState->targetObj;
	if(ImageLimit <= *trgObj){
	  puts("doMethod: *trgObj >= ImageLimit!");
	}
	else if(Image[*trgObj] == 0){
	  puts("doMethod: *trgObj - this object not available!");
	}

	return result;
}

int doBlock(objNum Block, objNum * trgObj) { // выполнить блок...
objNum tempMethodStateObj;
struct MethodState *tempMethodState, *block_savedMethodState;
struct BlockObject * block;
int result, tmpsSize;

#ifdef debug
	puts("doBlock: execute Block");
#endif

	tempMethodStateObj = newObj(ClassForMethodState, sizeof(struct MethodState), 1);
	tempMethodState = (struct MethodState *) &Image[tempMethodStateObj]->data;
	block = (struct BlockObject *) &Image[Block]->data;
	block_savedMethodState = (struct MethodState *) &Image[block->SavedState]->data;
	tmpsSize = Image[block->tmpCount]->data + Image[block->argCount]->data;

	// загружаем в наш стартовый MethodState указанный блок
	tempMethodState->self = block_savedMethodState->self;
	tempMethodState->method = Block;
	tempMethodState->bytecodeOffset = newObj(Image[block->argCount]->class, 4, 0);
	tempMethodState->tmps_obj = block_savedMethodState->tmps_obj;
	tempMethodState->args_obj = newObj(Image[block_savedMethodState->args_obj]->class,Image[block_savedMethodState->args_obj]->size,Image[block_savedMethodState->args_obj]->formemmng); // иначе 2 одновременно работающих блока подерутся...
	tempMethodState->targetObj = *trgObj;
	tempMethodState->previousMethodState = 0;
	tempMethodState->returnTo = 0;

	// подстраховываемся
	Image[tempMethodState->bytecodeOffset]->data = 0;
        if(tmpsSize * 4 > Image[tempMethodState->tmps_obj]->size)
	  resizeObj(tempMethodState->tmps_obj, tmpsSize * 4);


	// теперь запускаем наш MethodState
	result = continueContext(tempMethodStateObj);

	if(result > -2) *trgObj = tempMethodState->targetObj;
	if(ImageLimit <= *trgObj){
	  puts("doBlock: *trgObj >= ImageLimit!");
	}
	else if(Image[*trgObj] == 0){
	  puts("doBlock: *trgObj - this object not available!");
	}

	return result;
}
