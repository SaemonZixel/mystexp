/***************************************************************************
 *   Copyright (C) 2006 by Saemon Zixel                                    *
 *   saemon@pochta.ru                                                      *
 *                                                                         *
 ***************************************************************************/


#include "types.h"
#include "memmng.h" // используется функция1, функция2...
#include "imagemng.h"
#include "primitivemng.h"

#define StdSizeFor_tmps sizeof(objNum)*10
#define StdSizeFor_args sizeof(objNum)*7

#define CALL        0	// 00000000b
#define LD          64	// 01000000b
#define SM          128	// 10000000b
#define RET         192	// 11000000b

#define trg_self    0	// 00000000b
#define trg_super   8	// 00001000b
#define trg_retobj  16	// 00010000b
#define trg_none    24	// 00011000b
#define trg_lit     32	// 00100000b
#define trg_tmp     40	// 00101000b
#define trg_arg     48	// 00110000b
#define trg_inst    56	// 00111000b
#define trg_havetrg 32	// 00100000b

#define src_self    0	// 00000000b
#define src_super   1	// 00000001b
#define src_retobj  2	// 00000010b
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

int getNextInstruction(objNum methodStateObj, unsigned char *type, char *trg_type, char *src_type, long *trg, long *src) { //(перевод: получить следующую инструкцию)
    unsigned char commandByte, trgByte, srcByte;
    struct MethodState *methodState;
    objNum bytecodeObj, bytecodeOffset;
    char *bytecode;

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
        /* далее можно циклически считывать цепочку байтов пока у предыдущего байта не нуливой первый бит
           тем самым увеличивая разрядность (7 -> 14 -> 21 -> 28...)
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
    struct MethodState *currentMethodState;
    objNum returnTo, previousMethodState;
    objNum returnedObj;

#ifdef debug
	if(isMethodReturn) puts("Method Return");
	else puts("Return");
#endif

    currentMethodState = (struct MethodState *) &Image[*methodStateObj]->data;
    // возвращаемый объект в виде результата...
    returnedObj = currentMethodState->returnedObj;
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

	// в случае когда контекст(ы) привязанны к блоку, то теряется возможность правельно вычеслить temp
	if(currentMethodState->previousMethodState == currentMethodState->returnTo) { // только у методов мы обнуляем previousMethodState
		currentMethodState->previousMethodState = 0;
	}
	currentMethodState->returnTo = 0;

	// переключаемся на предыдущий contextState
	*methodStateObj = previousMethodState;

	// если просто кончился байткод (т.е. небыло команды RET), то просто возвращаемся в предыдущий контекст
	if(!isMethodReturn) break;

    }while(*methodStateObj != returnTo); // если недостигли заданный MethodState то повтаряем ещё раз

    // незабываем положить возвращаемый "результат"
    ((struct MethodState *) &Image[*methodStateObj]->data)->returnedObj = returnedObj;
    return 0;
}

void enterInBlock(objNum *methodStateObj, objNum targetBlock) {
    struct MethodState *newMethodState, *oldMethodState;
    objNum newMethodStateObj;

    struct BlockObject *block;
    struct MethodState *block_savedMethodState;
    unsigned long tmpsSize; // размер tmps сегмента

    oldMethodState = (struct MethodState *) &Image[*methodStateObj]->data;
    newMethodStateObj = newObj(Image[*methodStateObj]->class, sizeof(struct MethodState), 1);
    newMethodState = (struct MethodState *) &Image[newMethodStateObj]->data;

	// ВХОДИМ В БЛОК
#ifdef debug
	puts("enter in Block");
#endif
	block = (struct BlockObject*) &Image[targetBlock]->data;
	block_savedMethodState = (struct MethodState *) &Image[block->SavedState]->data;
	tmpsSize = Image[block->tmpCount]->data;
	newMethodState->self = block_savedMethodState->self;
        newMethodState->method  = targetBlock;
	newMethodState->bytecodeOffset = newObj(Image[oldMethodState->bytecodeOffset]->class, 4, 0);
	Image[newMethodState->bytecodeOffset]->data = 0;
	newMethodState->tmps_obj = newObj(Image[block_savedMethodState->tmps_obj]->class, tmpsSize*4, Image[block_savedMethodState->tmps_obj]->flags);
	newMethodState->args_obj = oldMethodState->args_obj;
	newMethodState->returnedObj = oldMethodState->returnedObj;

    // незабываем указать старый MethodState как предыдущей (в который можно будет вернутся)
    newMethodState->previousMethodState = *methodStateObj;
    // при интсрукции RET мы можем вирнутся только в контекст который был перед методом создавшим этот блок
    newMethodState->returnTo = block_savedMethodState->returnTo; // если привязываемся к блоку, то блок уже знает куда возвращатся

    *methodStateObj = newMethodStateObj;
}

void enterInMethod(objNum *methodStateObj, objNum targetMethod, objNum self) {
    struct MethodState *newMethodState, *oldMethodState;
    objNum newMethodStateObj;

    struct MethodObject *method;
    unsigned long tmpsSize; // размер tmps сегмента

    oldMethodState = (struct MethodState *) &Image[*methodStateObj]->data;
    newMethodStateObj = newObj(Image[*methodStateObj]->class, sizeof(struct MethodState), 1);
    newMethodState = (struct MethodState *) &Image[newMethodStateObj]->data;

	// ВХОДИМ В МЕТОД
	method =(struct MethodObject*) &Image[targetMethod]->data;
#ifdef debug
	printf("enter in obj(%li) method: %s class: %s\n",targetMethod,strndup((char *) &Image[method->name]->data, Image[method->name]->size),
	strndup((char *) &Image[((struct ClassObject*)&Image[method->InTheClass]->data)->name]->data, Image[((struct ClassObject*)&Image[method->InTheClass]->data)->name]->size));
#endif
	tmpsSize = Image[method->tmpCount]->data;
        newMethodState->self = self;
        newMethodState->method = targetMethod;
	newMethodState->bytecodeOffset = newObj(Image[oldMethodState->bytecodeOffset]->class, 4, 0);
	Image[newMethodState->bytecodeOffset]->data = 0;
        newMethodState->tmps_obj = newObj(Image[oldMethodState->tmps_obj]->class, tmpsSize * 4, 1);
	newMethodState->args_obj = oldMethodState->args_obj;
	newMethodState->returnedObj = oldMethodState->returnedObj;

  // незабываем указать старый MethodState как предыдущей (в который можно будет вернутся)
    newMethodState->previousMethodState = *methodStateObj;
 // при интсрукции RET мы можем вирнутся только в предыдущий контекст
    newMethodState->returnTo = newMethodState->previousMethodState;

    *methodStateObj = newMethodStateObj;
}

objNum SearchingForMethod(objNum targetClass, objNum SymbolObj) { // (перевод: поиск метода ) надо переделать в рекурсию!
    struct ClassObject *currentClass;
    objNum *currentMethods;
    objNum currentClassObj;
    int row, i, methodsInDict;
    char *currentMethodName, *ourMethodName;

    if(targetClass == 0){
     puts("SearchingForMethod: Error ! message send to 0");
    }

    // берём строковое (char*) предстовление искомого метода
    ourMethodName = &Image[SymbolObj]->dataAsChar;

    // узнаём класс targetObject и сразу берём указатель на содержимое этого класса (объекта-класса)
    currentClassObj = targetClass;
    currentClass = (struct ClassObject *) &Image[currentClassObj]->data;

#ifdef debug
	if(currentClass->methods == 0) {
		puts("SearchingForMethod: no methodDictionary in this class! return 0.");
		return 0;
	}
#endif

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
     if(currentClassObj == currentClass->super)
         return 0; // мы уже поднялись до последнего класса (Class) и рескуем попасть в бесконечный цикл

     // ... если можно то поднимаемся на класс выше
     currentClassObj = currentClass->super;
     currentClass = (struct ClassObject *) &Image[currentClassObj]->data;
    }
}

int searchTempVariable(objNum MethodStateObj, unsigned long num, objNum **result) { // (перевод: поиск временной переменной)
struct MethodState *methodState;
int moreCorrectPosition;

	methodState = (struct MethodState *) &Image[MethodStateObj]->data;
	
	// ищем глубже если Block
	if(methodState->returnTo != methodState->previousMethodState){
		moreCorrectPosition = searchTempVariable(((struct BlockObject*) &Image[methodState->method]->data)->SavedState, num, result);
		if(moreCorrectPosition == -1) return -1; // temp успешна найдена либо возвращено смещение temp относительно нашего tmps_obj
	} else {
		moreCorrectPosition = num; // в случае метода правельно использовать изначяльный num
	}

	// глубже не нашли или мы в методе и глубже нельзя, то ищем в текущем tmps_obj
	if(Image[methodState->tmps_obj]->size/4 <= moreCorrectPosition) {
		return moreCorrectPosition - Image[methodState->tmps_obj]->size/4;
	} else {
		*result = &Image[methodState->tmps_obj]->data + moreCorrectPosition;
		return -1; // сообщаем что поиск закончен успешно
	}

}

int executeInstruction(objNum *methodStateObj, unsigned char type, char trg_type, char src_type, long trg, long src){
struct MethodState *methodState;
struct MethodOrBlockHeader *methodOrBlock;

objNum *pointerToRealTemp; // указатель на ячейку в каком-либо tmps_obj (используется в случае блоков)
objNum LD_transit; // временная переменная 
objNum SM_message, // сообщение
       SM_method,  // метод соответствующий сообщению
       SM_targetObj; // то кому мы шлем сообщение
//objNum CALL_firstData, CALL_secondData;

	// подготовим указатели на содержимое MethodState и метода
	methodState = (struct MethodState *) &Image[*methodStateObj]->data;
	methodOrBlock = (struct MethodOrBlockHeader *) &Image[methodState->method]->data;

	switch( type ){
/* 64 */	case LD:
			// сначяло берём...
			switch( src_type ){
			   case src_lit:
			   		LD_transit = (&Image[methodOrBlock->literals]->data)[src];
					if(Image[methodOrBlock->literals]->size < (src+1)*4){
					  puts("LD: src lits out of range!");
					}
					break;
			   case src_tmp:
					if(searchTempVariable(*methodStateObj, src, &pointerToRealTemp) == -1) {
					  LD_transit = *pointerToRealTemp;
					} else {
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
			   		LD_transit = ((struct ClassObject *) &Image[methodOrBlock->InTheClass]->data)->super;
					break;
			   case src_retobj:
			   		LD_transit = methodState->returnedObj;
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
			   		(&Image[methodOrBlock->literals]->data)[trg] = LD_transit;
					if(Image[methodOrBlock->literals]->size < (trg+1)*4){
					  puts("LD: trg lits out of range!");
					}
					// вообще-то так делать нельзя
					//return -1; // возвращаем ошибку
					break;
			   case trg_tmp:
					if(searchTempVariable(*methodStateObj, trg, &pointerToRealTemp) == -1) {
					  *pointerToRealTemp = LD_transit;
					} else {
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
					((struct ClassObject *) &Image[methodOrBlock->InTheClass]->data)->super = LD_transit;
					//return -1; // возвращаем ошибку
					break;
			   case trg_retobj:
			   		methodState->returnedObj = LD_transit;
					break;
			   case trg_none:
			   		// и что мы должне сдесь делать ?
					break;
			}
			break;
/* 128 */	case SM:
			// узнаём кому адресованно сообщение, и кладём его в SM_newSelf
			switch( trg_type ){
			   case trg_lit:
			   		SM_targetObj = (&Image[methodOrBlock->literals]->data)[trg];
					if(Image[methodOrBlock->literals]->size < (trg+1)*4){
					 puts("SM: trg lits out of range!");
					}
					break;
			   case trg_tmp:
					if(searchTempVariable(*methodStateObj, trg, &pointerToRealTemp) == -1) {
					  SM_targetObj = *pointerToRealTemp;
					} else {
					  puts("SM: trg tmps out of range!");
					}
					break;
			   case trg_arg:
			   		SM_targetObj = (&Image[methodState->args_obj]->data)[trg];
					if(Image[methodState->args_obj]->size < trg*4){
					 puts("SM: trg args out of range!");
					}
					break;
			   case trg_inst:
			   		SM_targetObj = (&Image[methodState->self]->data)[trg];
					if(Image[methodState->self]->size < trg*4){
					 puts("SM: trg inst out of range!");
					}
					break;
			   case trg_self:
			   		SM_targetObj = methodState->self;
					break;
			   case trg_super:
			   		// а сдесь сообщение адресованно к self, только метод будет искатся классом выше
					SM_targetObj = methodState->self;
					break;
			   case trg_retobj:
			   		SM_targetObj = methodState->returnedObj;
					break;
			   case trg_none:
			   		// это как ?
					return -1;
					break;
			}
			switch( src_type ){
			   case src_lit:
			   		SM_message = (&Image[methodOrBlock->literals]->data)[src];
					if(Image[methodOrBlock->literals]->size < (src+1)*4){
					 puts("SM: src lits out of range!");
					}
					break;
			   case src_tmp:
					if(searchTempVariable(*methodStateObj, src, &pointerToRealTemp) == -1) {
					  SM_message = *pointerToRealTemp;
					} else {
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
			   		// super является message ?
					//SM_message = ((struct ClassObject *) &Image[methodOrBlock->InTheClass]->data)->super;
					break;
			   case src_retobj:
			   		SM_message = methodState->returnedObj;
					break;
			   case src_none:
			   		// это как ?
					return -1;
					break;
			}
			if(ImageLimit <= SM_targetObj) puts("SM: SM_targetObj >= ImageLimit!");
			else if(Image[SM_targetObj] == 0) puts("SM: SM_targetObj - this object not available!");

			// если это вызов блока то входим в него и всё
			if(SM_message == 0) { // сообщение пустое значит SM_newSelf это блок, и нам надо в него войти
			  enterInBlock(methodStateObj, SM_targetObj);
			  // на этом всё
			  break;
			}

			// здесь у нас тонкость, если сообщение шлетса суперклассу то надо это сделать явно
			if(trg_type == trg_super)
			    SM_method = SearchingForMethod(((struct ClassObject *) &Image[methodOrBlock->InTheClass]->data)->super, SM_message); // ищем начиная с более верхнего класса целевого объекта
			else
			    SM_method = SearchingForMethod(Image[SM_targetObj]->class, SM_message); // ищем начиная с класса целевого объекта

			// проверяем нашли ли метод
			if(SM_method == 0){
			   // эти две строчки аш блещат своей красотой и краткостью ;)
			   if(trg_type != trg_super) printf("Message Not Understoode '%s' -> %l(class %s)\n",strndup((char*) &Image[SM_message]->data, Image[SM_message]->size), Image[SM_targetObj]->class,strndup((char*) &Image[Image[Image[SM_targetObj]->class]->data]->data,Image[Image[Image[SM_targetObj]->class]->data]->size));
			   else printf("Message Not Understoode '%s' -> %l(class %s)\n",strndup((char*) &Image[SM_message]->data, Image[SM_message]->size),((struct ClassObject *) &Image[methodOrBlock->InTheClass]->data)->super, strndup((char*) &Image[Image[((struct ClassObject *) &Image[methodOrBlock->InTheClass]->data)->super]->data]->data,Image[Image[((struct ClassObject *) &Image[methodOrBlock->InTheClass]->data)->super]->data]->size));
			   return -2;
			}

			enterInMethod(methodStateObj, SM_method, SM_targetObj);
			break;
/* 192 */	case RET: // только возврат из метода (^)
			switch( trg_type ){
			   case trg_lit:
			   		methodState->returnedObj = (&Image[methodOrBlock->literals]->data)[trg];;
					if(Image[methodOrBlock->literals]->size < (trg+1)*4){
					 puts("RET: trg lits out of range!");
					}
					break;
			   case trg_tmp:
					if(searchTempVariable(*methodStateObj, trg, &pointerToRealTemp) == -1) {
					  methodState->returnedObj = *pointerToRealTemp;
					} else {
					  puts("RET: trg tmps out of range!");
					}
					break;
			   case trg_arg:
			   		methodState->returnedObj = (&Image[methodState->args_obj]->data)[trg];
					if(Image[methodState->args_obj]->size < trg*4){
					 puts("RET: trg args out of range!");
					}
					break;
			   case trg_inst:
			   		methodState->returnedObj = (&Image[methodState->self]->data)[trg];
					if(Image[methodState->self]->size < trg*4){
					 puts("RET: trg inst out of range!");
					}
					break;
			   case trg_self:
			   		methodState->returnedObj = methodState->self;
					break;
			   case trg_super:
					methodState->returnedObj = ((struct ClassObject *) &Image[methodOrBlock->InTheClass]->data)->super;
					break;
			   case trg_retobj: // Хммм... забавно...
			   		methodState->returnedObj = methodState->returnedObj;
					break;
			   case trg_none:
			   		// это как ?
					return -1;
					break;
			}
			if(ImageLimit <= methodState->returnedObj){
			  puts("RET: methodState->returnedObj >= ImageLimit!");
			}
			else if(Image[methodState->returnedObj] == 0){
			  puts("RET: methodState->returnedObj - this object not available!");
			}
			return returnInPreviousMethod(methodStateObj, 1); // 1 -> isMethodReturn=true
			break;
/* 0 */ 	case CALL:
			if(src_type & src_havesrc){
			 // расширенный вызов
			/* switch(trg_type){
				case trg_lit: CALL_firstData = (&Image[methodOrBlock->literals]->data)[trg]; break;
				case trg_tmp: CALL_firstData = (&Image[methodState->tmps_obj]->data)[trg]; break;
				case trg_arg: CALL_firstData = (&Image[methodState->args_obj]->data)[trg]; break;
				case trg_inst: CALL_firstData = (&Image[methodState->self]->data)[trg]; break;
				default: puts("CALL: Invalid trg_type"); return 1;
			 }
			 switch(src_type){
				case src_lit: CALL_secondData = (&Image[methodOrBlock->literals]->data)[src]; break;
				case src_tmp: CALL_secondData = (&Image[methodState->tmps_obj]->data)[src]; break;
				case src_arg: CALL_secondData = (&Image[methodState->args_obj]->data)[src]; break;
				case src_inst: CALL_secondData = (&Image[methodState->self]->data)[src]; break;
			 }
			 return extendedCall(CALL_firstData, CALL_secondData, methodStateObj);*/
			} else {
			 // простой вызов внутренего примитива
			 if(trg_type & trg_havetrg) return internalCall((int) trg, methodStateObj);
			 else return internalCall((int) 0, methodStateObj); // если не указан не trg не src то падрузумевается...(?)
			}
			break;
	}
	return 0;
}

int continueContext(objNum methodState){ // (перев. продолжить контекст)
unsigned char type;
char trg_type, src_type;
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
	    // проверяем не кончились ли MethodState
	    if(((struct MethodState *) &Image[currentMethodStateObj]->data)->previousMethodState == 0){ result = -1; break;}
	    // если мы в конце то возвращаемся в предыдущий контекст (без разницы блок или метод)
	    result = returnInPreviousMethod(&currentMethodStateObj, 0);
	  } else {
	    // иначе выполняем инструкцию
	    result = executeInstruction(&currentMethodStateObj, type, trg_type, src_type, trg, src);
	    if(result == -2) puts("MethodNotFound!");
	  }
	}while(result == 0); // если всё хорошо повтаряем ещё раз
	// продублируем на случай если RET был совершен из блока
	((struct MethodState*) &Image[methodState]->data)->returnedObj = ((struct MethodState*) &Image[currentMethodStateObj]->data)->returnedObj;
#ifdef primZero
//	continueContextExitHook(result, vmContext);
#endif

#ifdef debug
	if(result < 0) printf("Error ! (bytecodeOffset: %i)\n",Image[((struct MethodState*) &Image[methodState]->data)->bytecodeOffset]->data);
	else printf("Normal Exit\n");
#endif
	return result;
	// -1 - Встречена RET или просто конец байткода, но возвращатся некуда (достигнут последний контекст)
	// -2 - метод не найден (SearchingForMethod сказал)
}

int doMethod(objNum Method, objNum self, objNum *retObj) { // (перевод: выполнить метод)
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
	tmpsSize = Image[method->tmpCount]->data;

	// загружаем в наш стартовый MethodState указанный метод
	tempMethodState->self = self;
	tempMethodState->method = Method;
	tempMethodState->bytecodeOffset = newObj(Image[method->argCount]->class, 4, 0);
        tempMethodState->tmps_obj = newObj(Image[method->literals]->class, tmpsSize * 4, 1);
        tempMethodState->args_obj = newObj(Image[method->literals]->class, StdSizeFor_args, 1);
	tempMethodState->returnedObj = *retObj;
	tempMethodState->previousMethodState = 0;
	tempMethodState->returnTo = 0;

	// подстраховываемся
	Image[tempMethodState->bytecodeOffset]->data = 0;

	// теперь запускаем наш MethodState
	result = continueContext(tempMethodStateObj);

	if(result > -2) *retObj = tempMethodState->returnedObj;
	if(ImageLimit <= *retObj){
	  puts("doMethod: *retObj >= ImageLimit!");
	}
	else if(Image[*retObj] == 0){
	  puts("doMethod: *retObj - this object not available!");
	}

	return result;
}

int doBlock(objNum Block, objNum *retObj) { // (перевод: выполнить блок)
objNum tempMethodStateObj;
struct MethodState *tempMethodState, *block_savedMethodState;
struct BlockObject *block;
int result, tmpsSize;

#ifdef debug
	puts("doBlock: execute Block");
#endif

	tempMethodStateObj = newObj(ClassForMethodState, sizeof(struct MethodState), 1);
	tempMethodState = (struct MethodState *) &Image[tempMethodStateObj]->data;
	block = (struct BlockObject *) &Image[Block]->data;
	block_savedMethodState = (struct MethodState *) &Image[block->SavedState]->data;
	tmpsSize = Image[block->tmpCount]->data;

	// загружаем в наш стартовый MethodState указанный блок
	tempMethodState->self = block_savedMethodState->self;
	tempMethodState->method = Block;
	tempMethodState->bytecodeOffset = newObj(Image[block->argCount]->class, 4, 0);
	tempMethodState->tmps_obj = block_savedMethodState->tmps_obj;
	tempMethodState->args_obj = newObj(Image[block_savedMethodState->args_obj]->class,Image[block_savedMethodState->args_obj]->size,Image[block_savedMethodState->args_obj]->flags); // иначе 2 одновременно работающих блока подерутся...
	tempMethodState->returnedObj = *retObj;
	tempMethodState->previousMethodState = 0;
	tempMethodState->returnTo = 0;

	// подстраховываемся
	Image[tempMethodState->bytecodeOffset]->data = 0;
        if(tmpsSize * 4 > Image[tempMethodState->tmps_obj]->size)
	  resizeObj(tempMethodState->tmps_obj, tmpsSize * 4);

	// теперь запускаем наш MethodState
	result = continueContext(tempMethodStateObj);

	if(result > -2) *retObj = tempMethodState->returnedObj;
	if(ImageLimit <= *retObj){
	  puts("doBlock: *retObj >= ImageLimit!");
	}
	else if(Image[*retObj] == 0){
	  puts("doBlock: *retObj - this object not available!");
	}

	return result;
}
