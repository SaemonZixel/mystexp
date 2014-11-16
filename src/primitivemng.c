/***************************************************************************
 *   Copyright (C) 2006 by Saemon Zixel                                    *
 *   saemon@pochta.ru                                                      *
 *                                                                         *
 ***************************************************************************/

#include <dlfcn.h>
#include "types.h"
#include "imagemng.h"
#include "memmng.h"
#include "tests.h"

//#define isOverflow(x) ((x < -2147483647) && (x > 2147483647)) //должно быть: -2147483648, но тогда выробатывается warning
#define isOverflow(x) ((x < -32768) && (x > 32767))
#define isFloatOverflow(x) ((x < -1.18f*100000000000000000000000000000000000000.0f) && (x > 3.40f*100000000000000000000000000000000000000.0f))

#define MaxCallArgs 20
int argsArray[MaxCallArgs];
int argsTop;

#define CallExternalFunction(type, func)  \
	(* (type (*)()) func)(  \
	      argsArray[0],  argsArray[1],  argsArray[2],  argsArray[3],  \
	      argsArray[4],  argsArray[5],  argsArray[6],  argsArray[7],  \
	      argsArray[8],  argsArray[9],  argsArray[10], argsArray[11], \
	      argsArray[12], argsArray[13], argsArray[14], argsArray[15], \
	      argsArray[16], argsArray[17], argsArray[18], argsArray[19]);

objNum SmalltalkDictionary;

int internalCall(int primitiveNumber, objNum *methodStateObj){ // (перевод: внутренний вызов)
	struct MethodState *methodState;
	objNum *args;
	struct BlockObject *block;

	unsigned long i, i2; // для циклов
	unsigned long offset; // смещение внутри объекта (т.е. в Image[]->data)
	signed long result; // для вычеслений с целыми
	float *float1, *float2; // для работы с float в объектах
	double result2; // для вычеслений с float
	objNum firstObj, secondObj; // если будем работать с двумя объектами
	objNum *collection; // если будем работать с коллекциями объектов
	char *str;
	char *pointer; // для работы с указателями
	char filename[255];
	void *func; // для вызова неизвестной функции
	char string[500]; // для вывода строки через puts()

#ifdef primZero
    if(internalCallHook(primitiveNumber, *methodStateObj)) return 0;
#endif

	methodState = (struct MethodState *) &Image[*methodStateObj]->data;
	args = &Image[methodState->args_obj]->data;

#ifdef debug
	printf("Called primitive: %i arg[0]= %i arg[1]= %i \n", primitiveNumber, args[0], args[1]);
#endif

	switch( primitiveNumber ){
		case 0: primitiveZero(args[0], *methodStateObj); break;
		case 1: printf("LoadImage:"); break;
		case 2: // saveImage: (and Exit?) (args: str1 bool1)
			for(i=0; i < Image[args[0]]->size; i++)
			  if(i < 254){
			   filename[i] = ((char *) &Image[args[0]]->data)[i];
			   filename[i+1] = 0;
			  }
			GC_markAndSweep(*methodStateObj);
			SaveImage(&filename[0], *methodStateObj);
/*			if(SaveImage(&filename[0], *methodStateObj)) methodState->returnedObj=falseObject;
			else methodState->returnedObj = trueObject;
			if(args[1] == falseObject)*/ break;
		case 3: printf("Exit VM\n"); return 1;
		case 4: printf("SaveChanges (?)"); break;
		case 5: // set_internal_constants (args: ConstCount, intClass, true, false...)
/*			trueObject = args[1];
			falseObject = args[2];
			nilObject = args[3];
			objClass = (&Image[Image[nilObject]->class]->data)[1]; // nil.class -> super
			integerClass = args[4];
			floatClass = args[5];
			smallIntClass = args[6];
			if(Image[args[0]]->data > 6) pointerClass = args[7];
			else pointerClass = integerClass;*/
			break;
		case 6: // get_internal_calls? (args: obj1=Name pointerclass objectIfFail)
			str = &Image[args[0]]->dataAsChar;
			methodState->returnedObj = args[2];
			if((str[0] == 'd') && (str[1] == 'l') && (str[2] == 's')) { // запрашивается 'dlsym'
			  methodState->returnedObj = newObj(args[1], sizeof(void *), 0);
			  *((void **) &Image[methodState->returnedObj]->data) = dlsym;
			}
			if((str[0] == 'd') && (str[1] == 'l') && (str[2] == 'o')) { // запрашивается 'dlopen'
			  methodState->returnedObj = newObj(args[1], sizeof(void *), 0);
			  *((void **) &Image[methodState->returnedObj]->data) = dlopen;
			}
			if((str[0] == 'p') && (str[1] == 'r') && (str[2] == 'i')) { // запрашивается 'printf'
			  methodState->returnedObj = newObj(args[1], sizeof(void *), 0);
			  *((void **) &Image[methodState->returnedObj]->data) = printf;
			}
#ifdef primZero
			if((str[0] == 't') && (str[1] == 'I') && (str[2] == 'n')) { // запрашивается 'testInt'
			  methodState->returnedObj = newObj(args[1], sizeof(void *), 0);
			  *((void **) &Image[methodState->returnedObj]->data) = testInt;
			}
			if((str[0] == 't') && (str[1] == 'D') && (str[2] == 'o')) { // запрашивается 'testDouble'
			  methodState->returnedObj = newObj(args[1], sizeof(void *), 0);
			  *((void **) &Image[methodState->returnedObj]->data) = testDouble;
			}
			if((str[0] == 't') && (str[1] == 'P') && (str[2] == 'o')) { // запрашивается 'testPointer'
			  methodState->returnedObj = newObj(args[1], sizeof(void *), 0);
			  *((void **) &Image[methodState->returnedObj]->data) = testPointer;
			}
			if((str[0] == 't') && (str[1] == '2') && (str[2] == 'a')) { // запрашивается 'test2args'
			  methodState->returnedObj = newObj(args[1], sizeof(void *), 0);
			  *((void **) &Image[methodState->returnedObj]->data) = test2args;
			}
			if((str[0] == 't') && (str[1] == '3') && (str[2] == 'a')) { // запрашивается 'test3args'
			  methodState->returnedObj = newObj(args[1], sizeof(void *), 0);
			  *((void **) &Image[methodState->returnedObj]->data) = test3args;
			}
			if((str[0] == 't') && (str[1] == 'R') && (str[2] == 'C')) { // запрашивается 'testRetChar'
			  methodState->returnedObj = newObj(args[1], sizeof(void *), 0);
			  *((void **) &Image[methodState->returnedObj]->data) = testRetChar;
			}
			if((str[0] == 't') && (str[1] == 'R') && (str[2] == 'I')) { // запрашивается 'testRetInt'
			  methodState->returnedObj = newObj(args[1], sizeof(void *), 0);
			  *((void **) &Image[methodState->returnedObj]->data) = testRetInt;
			}
			if((str[0] == 't') && (str[1] == 'R') && (str[2] == 'D')) { // запрашивается 'testRetDouble'
			  methodState->returnedObj = newObj(args[1], sizeof(void *), 0);
			  *((void **) &Image[methodState->returnedObj]->data) = testRetDouble;
			}
			if((str[0] == 't') && (str[1] == 'R') && (str[2] == 'P')) { // запрашивается 'testRetPointer'
			  methodState->returnedObj = newObj(args[1], sizeof(void *), 0);
			  *((void **) &Image[methodState->returnedObj]->data) = testRetPointer;
			}
#endif
			break;
		case 7: // call_external_function (args: obj1.data=void* obj2.data=#( C_arg1.class=pointer C_arg2.class=Integer ...) obj3.data = result objectIfFail
			// берём указатель по каторому будем вызывать функцию...
			func = Image[args[0]]->dataAsPointer;

			// положить в стек аргументы...
#ifdef debug
			if((Image[args[1]]->size / sizeof(objNum)) > MaxCallArgs) puts("prim 7: Arguments overflow!"); //переполнение примитив не обрабатывает!
#endif
			argsTop = 0;
			for( i=0; i<Image[args[1]]->size/4; i++ ){
			  firstObj = (&Image[args[1]]->data)[i];
			  switch(Image[firstObj]->size) {
/*			   case 0: if(firstObj == trueObject) argsArray[argsTop] = (int) 1;
			   	   break;*/
			   case 1: argsArray[argsTop] = (int) Image[firstObj]->dataAsChar;
			   	   break;
			   case 2: argsArray[argsTop] = (int) Image[firstObj]->dataAsShort;
			   	   break;
			   case 4: argsArray[argsTop] = (int) Image[firstObj]->dataAsLong;
			   	   break;
			   case 8: if(Image[firstObj]->size < sizeof(int))
			   	     argsArray[argsTop] = (int) *((double*) &Image[firstObj]->data);
			   	   else {
				     argsArray[argsTop] = (int) ((long*) &Image[firstObj]->data)[0];
				     argsTop++;
				     argsArray[argsTop] = (int) ((long*) &Image[firstObj]->data)[1];
				   }
			   	   break;
			   default: argsArray[argsTop] = (int) 0;
			   	   break;
			  }
			  argsTop++;
			}
			while(argsTop < MaxCallArgs) argsArray[argsTop++] = (int) 0; // оставшееся место забиваем нулями

			// теперь определяем тип возвращаемых данных и вызываем функцию...
			methodState->returnedObj = args[2];
			switch(Image[methodState->returnedObj]->size){
			 case 0: CallExternalFunction(void, func);
			 	 break;
			 case 1: Image[methodState->returnedObj]->dataAsChar = CallExternalFunction(char, func);
			 	 break;
			 case 2: Image[methodState->returnedObj]->dataAsShort = CallExternalFunction(short, func);
			 	 break;
			 case 4: Image[methodState->returnedObj]->dataAsLong = CallExternalFunction(long, func);
			 	 break;
			 case 8: *((double*) &Image[methodState->returnedObj]->data) = CallExternalFunction(double, func);
			 	 break;
			 default: methodState->returnedObj = args[3];
			 	 break;
			}
			break;
		case 8: // unwrap_array (args: collection1) - кладет в сегмент arg содержимое collection1 т.е. вместо первого аргумента кладет объекты которые в нем находятся
			firstObj = args[0];
			if(Image[firstObj]->size > Image[methodState->args_obj]->size) resizeObj(methodState->args_obj, Image[firstObj]->size);
			for(i = (Image[firstObj]->size/4)-1; i >= 0; i--)
				(&Image[methodState->args_obj]->data)[i] = (&Image[firstObj]->data)[i];
			methodState->returnedObj = firstObj;
			break;
		case 9: // block_assign_tmpsnargs (args: obj1)
			firstObj = args[0];
			secondObj = newObjWithData(Image[firstObj]->class, Image[firstObj]->size, Image[firstObj]->flags, Image[firstObj]->size, &Image[firstObj]->dataAsChar);
			block = (struct BlockObject *) (&Image[secondObj]->data);
			block->inTheMethod = ((struct MethodObject *) &Image[methodState->method]->data)->InTheClass; // ?
			block->SavedState = *methodStateObj;
			methodState->returnedObj = secondObj;
			break;
		case 10: // obj1 == obj2 (args: obj1 obj2 objectIfTrue objectIfFalse) - сравнение по номерам т.е. obj1 identityHash = obj2 identityHash
			if(args[0] == args[1]) methodState->returnedObj = args[2];
			else methodState->returnedObj = args[3];
			break;
		case 11: // Object new: int1 (args: int1 class1) - создание объекта размером int1 и класса class1
#ifdef debug
			if(Image[args[0]]->dataAsLong < 0) puts("prim: 11(new:) size is NEGATVE! (warning!)");
#endif
			methodState->returnedObj = newObj(args[1], Image[args[0]]->data, 0);
			break;
		case 12: // obj1 runGC (args: )
			GC_markAndSweep(*methodStateObj);
			//methodState->returnedObj = nilObject;
			break;
		case 13: // obj1.size (args: obj1 integerclass)
			methodState->returnedObj = newObj(args[1], 4, 0);
			Image[methodState->returnedObj]->data = Image[args[0]]->size;
			break;
		case 14: // obj1 resize: int1 (args: obj1 int1 objectIfFail)
#ifdef debug
			if(Image[args[1]]->dataAsLong < 0) puts("prim: 14(resize:) new size is NEGATVE! (warning!)");
#endif
			resizeObj(args[0], Image[args[1]]->data);
			if(args[0] == 0)
			  methodState->returnedObj = args[2]; // неудалось сделать resize
			else
			  methodState->returnedObj = args[0];
			break;
		case 15: // obj1 class (args: obj1)
			methodState->returnedObj = Image[args[0]]->class;
			break;
		case 16: // obj1 class: obj2 (args: obj1 obj2)
			Image[args[0]]->class = args[1];
			methodState->returnedObj = args[0];
			break;
		case 17: // obj1 flags  (args: obj1 integerclass)
			methodState->returnedObj = newObj(args[1], 4, 0);
			Image[methodState->returnedObj]->data = Image[args[0]]->flags;
			break;
		case 18: // obj1 flags: (args: obj1 int1)
			Image[args[0]]->flags = Image[args[1]]->data;
			methodState->returnedObj = args[0];
			break;
		case 19: // obj1 byteAt: (args: obj1 int1 smallintegerclass objectIfFail) - возвращает 1 байт (8bit), int1 = номер байта.
			firstObj = args[0];
			offset = Image[args[1]]->data;
			if(offset > Image[firstObj]->size) methodState->returnedObj = args[3];
			else {
			 methodState->returnedObj = newObj(args[2], 1, 0);
			 Image[methodState->returnedObj]->dataAsChar = (&Image[firstObj]->dataAsChar)[offset-1];
			}
			break;
		case 20: // obj1 basicPut: obj2.data startAt: int1 (args: obj1 int1 obj2)- кладёт внутренности obj2 в obj1 начиная с int1, без resize
			firstObj = args[0];
			i = Image[args[1]]->data - 1; // номер текущего байта/char в firstObj, палученый порядковый номер переделывается в смещение
			secondObj = args[2];
			i2 = 0;  // позиция текущего байта/char в secondObj, первый байт находится в нулевой позиции
			while((i < Image[firstObj]->size) && (i2 < Image[secondObj]->size)){
			  (&Image[firstObj]->dataAsChar)[i] = (&Image[secondObj]->dataAsChar)[i2];
			  i++;
			  i2++;
			}
			methodState->returnedObj = firstObj;
			break;
		case 21: // obj1.data = obj2.data (args: obj1 obj2 objectIfTrue objectIfFalse) - побайтное сравнение
			firstObj = args[0];
			secondObj = args[1];
			if((Image[firstObj]->size == Image[secondObj]->size) && (Image[firstObj]->class == Image[secondObj]->class)){
			  methodState->returnedObj = args[2];
			  if(Image[firstObj]->size == 0) break;  // размер = 0 -> данных нет, сравнение закончили
			  for(i = 0; i < Image[firstObj]->size; i++)
			    if((&Image[firstObj]->dataAsChar)[i] != (&Image[secondObj]->dataAsChar)[i]){
			      methodState->returnedObj = args[3];
			      break;
			    }
			} else methodState->returnedObj = args[3];
			break;
		case 22: // obj1 at: int1 (args: obj1 int1 objectIfFail) - возвращает номер объекта (objNum, unsigned long, 32bit), int1 = порядковый номер позиции.
			firstObj = args[0];
			offset = Image[args[1]]->data - 1;
			if(offset+1 > (Image[firstObj]->size/4)) methodState->returnedObj = args[2];
			else methodState->returnedObj = (&Image[args[0]]->data)[offset];
			break;
		case 23: // obj1 at: int1 put: obj2 (args: obj1 int1 obj2 objectIfFail) - кладёт obj2 (т.е. номер объекта) непосретственно в тело obj1
			firstObj = args[0];
			offset = Image[args[1]]->data - 1;
			if(offset+1 > (Image[firstObj]->size/4)) methodState->returnedObj = args[3];
			else {
			  (&Image[firstObj]->data)[offset] = args[2];
			  methodState->returnedObj = firstObj;
			}
			break;
		case 32: // obj1 asPointer (args: obj1 pointerclass)
			 methodState->returnedObj = newObj(args[1], sizeof(void *), 0);
			 Image[methodState->returnedObj]->dataAsPointer = &Image[args[0]]->data;
			 Image[args[0]]->flags = Image[args[0]]->flags | bitNotMoveableObj; // чтоб некто его не сдвигал с текущего места
			break;
		case 33: // ptr1 basicAt: int1 (args: ptr1 int1 smallintclass)
			pointer = Image[args[0]]->dataAsPointer;
			offset = Image[args[1]]->data - 1;
			methodState->returnedObj = newObj(args[2],1,0);
			Image[methodState->returnedObj]->dataAsChar = pointer[offset];
			break;
		case 34: // ptr1 put: obj2 startAt: int1 (args: ptr1 int1 obj2)- кладёт obj2.size bytes
			pointer = Image[args[0]]->dataAsPointer;
			i = Image[args[1]]->data - 1; // смещение текущего байта/char в firstObj, (первая позици -> 0 смещение)
			secondObj = args[2];
			i2 = 0;  // номер текущего байта/char в pointer, первый байт находится в нулевой позиции
			while(i2 < Image[secondObj]->size){
			  pointer[i] = (&Image[secondObj]->dataAsChar)[i2];
			  i++;
			  i2++;
			}
			methodState->returnedObj = args[0];
			break;
		case 65: // int1 + int2 (args: int1 int2 integerclass objectIfFail)
			result = Image[args[0]]->dataAsLong + Image[args[1]]->dataAsLong;
			if(isOverflow(result))
			 methodState->returnedObj = args[3];
			else {
			 methodState->returnedObj = newObj(args[2], 4, 0);
			 Image[methodState->returnedObj]->dataAsLong = (signed long) result;
			}
			break;
		case 66: // int1 - int2 (args: int1 int2 integerclass objectIfFail)
			result = Image[args[0]]->dataAsLong - Image[args[1]]->dataAsLong;
			if(isOverflow(result))
			 methodState->returnedObj = args[3];
			else {
			 methodState->returnedObj = newObj(args[2], 4, 0);
			 Image[methodState->returnedObj]->dataAsLong = (signed long) result;
			}
			break;
		case 67: // int1 * int2 (args: int1 int2 integerclass objectIfFail)
			result = Image[args[0]]->dataAsLong * Image[args[1]]->dataAsLong;
			if(isOverflow(result))
			 methodState->returnedObj = args[3];
			else {
			 methodState->returnedObj = newObj(args[2], 4, 0);
			 Image[methodState->returnedObj]->dataAsLong = (signed long) result;
			}
			break;
		case 68: // int1 / int2 (args: int1 int2 fractionclass)
			methodState->returnedObj = newObj(args[2], 8, 0);
			(&Image[methodState->returnedObj]->data)[0] = args[0];
			(&Image[methodState->returnedObj]->data)[1] = args[1];
			break;
		case 69: // int1 rem: int2 (args: int1 int2 integerclass objectIfFail) - остаток от деления (?)
			if(Image[args[1]]->data == 0) methodState->returnedObj = 0;
			result = Image[args[0]]->dataAsLong % Image[args[1]]->dataAsLong;
			if(isOverflow(result))
			 methodState->returnedObj = args[3];
			else {
			 methodState->returnedObj = newObj(args[2], 4, 0);
			 Image[methodState->returnedObj]->dataAsLong = (signed long) result;
			}
			break;
		case 70: // int1 // int2 (args: int1 int2 integerclass) - целая часть от деления
			if(Image[args[1]]->data == 0) methodState->returnedObj = 0;
			result = Image[args[0]]->dataAsLong / Image[args[1]]->dataAsLong;
			methodState->returnedObj = newObj(args[2], 4, 0);
			Image[methodState->returnedObj]->dataAsLong = (signed long) result;
			break;
		case 71: // int1 quo: int2 (args: int1 int2 integerclass)
			/*if(Image[args[1]]->data == 0) methodState->returnedObj = 0;
			result = Image[args[0]]->dataAsLong / Image[args[1]]->dataAsLong;
			methodState->returnedObj = newObj(args[2], 4, 0);
			Image[methodState->returnedObj]->dataAsLong = (signed long) result;
			break;*/
		case 72: // int1 bitAnd: int2 (args: int int2 integerclass)
			methodState->returnedObj = newObj(args[2], 4, 0);
			Image[methodState->returnedObj]->dataAsLong = Image[args[0]]->dataAsLong & Image[args[1]]->dataAsLong;
			break;
		case 73: // int1 bitOr: int2 (args: int1 int2 integerclass)
			methodState->returnedObj = newObj(args[2], 4, 0);
			Image[methodState->returnedObj]->dataAsLong = Image[args[0]]->dataAsLong | Image[args[1]]->dataAsLong;
			break;
		case 74: // int1 bitXor: int2 (args: int1 int2 integerclass)
			methodState->returnedObj = newObj(args[2], 4, 0);
			Image[methodState->returnedObj]->data = Image[args[0]]->dataAsLong ^ Image[args[1]]->dataAsLong;
			break;
		case 75: // int1 bitShift: int2 (args: int1 int2 integerclass objectIfFail)
			result = Image[args[1]]->dataAsLong;
			if((result > -33) && (result < 33)) {
			  if((result >= 0) && (result < 33)) result = Image[args[0]]->data << result;
			  if((result < 0) && (result > -33)) result = Image[args[0]]->data >> result;
			  methodState->returnedObj = newObj(args[2], 4, 0);
			  Image[methodState->returnedObj]->data = result;
			} else methodState->returnedObj = args[3];
			break;
		case 76: // int1 < int2 (args: int1 int2 objectIfTrue objectIfFalse)
			if(Image[args[0]]->dataAsLong < Image[args[1]]->dataAsLong)
			 methodState->returnedObj = args[2];
			else
			 methodState->returnedObj = args[3];
			break;
		case 77: // int1 > int2 (args: int1 int2 objectIfTrue objectIfFalse)
			/*if(Image[args[0]]->dataAsLong > Image[args[1]]->dataAsLong)
			 methodState->returnedObj = args[2];
			else
			 methodState->returnedObj = args[3];
			break;*/
		case 78: // int1 <= int2 (args: int1 int2 objectIfTrue objectIfFalse)
			/*if(Image[args[0]]->dataAsLong <= Image[args[1]]->dataAsLong)
			 methodState->returnedObj = args[2];
			else
			 methodState->returnedObj = args[3];
			break;*/
		case 79: // int1 >= int2 (args: int1 int2 objectIfTrue objectIfFalse)
			/*if(Image[args[0]]->dataAsLong >= Image[args[1]]->dataAsLong)
			 methodState->returnedObj = args[2];
			else
			 methodState->returnedObj = args[3];
			break;*/
		case 80: // int1 = int2 (args: int1 int2 objectIfTrue objectIfFalse)
			if(Image[args[0]]->dataAsLong == Image[args[1]]->dataAsLong)
			 methodState->returnedObj = args[2];
			else
			 methodState->returnedObj = args[3];
			break;
		case 81: // int ~= int (args: int1 int2 objectIfTrue objectIfFalse)
			/*if(Image[args[0]]->dataAsLong != Image[args[1]]->dataAsLong)
			 methodState->returnedObj = args[2];
			else
			 methodState->returnedObj = args[3];
			break;*/
		case 82: // obj2.data = (float)obj1.data (args: obj1 floatclass) - возвращает объект с предстовлением числа в float
			methodState->returnedObj = newObj(args[1], 4, 0);
			Image[methodState->returnedObj]->dataAsFloat = (float) Image[args[0]]->dataAsLong;
			break;
		case 83: // float1 + float2 (args: float1 float2 floatclass objectIfFail)
			result2 = Image[args[0]]->dataAsFloat + Image[args[1]]->dataAsFloat;
			if(isFloatOverflow(result2))
			  methodState->returnedObj = args[3];
			else {
			  methodState->returnedObj = newObj(args[2], 4, 0);
			  Image[methodState->returnedObj]->dataAsFloat = (float) result2;
			}
			break;
		case 84: // float1 - float2 (args: float1 float2 floatclass objectIfFail)
			result2 = Image[args[0]]->dataAsFloat - Image[args[1]]->dataAsFloat;
			if(isFloatOverflow(result2))
			  methodState->returnedObj = args[3];
			else {
			  methodState->returnedObj = newObj(args[2], 4, 0);
			  Image[methodState->returnedObj]->dataAsFloat = (float) result2;
			}
			break;
		case 85: // float1 < float2 (args: float1 float2 objectIfTrue objectIfFalse)
			if(Image[args[0]]->dataAsFloat < Image[args[1]]->dataAsFloat)
			 methodState->returnedObj = args[2];
			else
			 methodState->returnedObj = args[3];
			break;
		case 86: printf("Float > Float"); break;
		case 87: printf("Float <= Float"); break;
		case 88: printf("Float >= Float"); break;
		case 89: // float1 = float2 (args: float1 float2 objectIfTrue objectIfFalse)
			if(Image[args[0]]->dataAsFloat == Image[args[1]]->dataAsFloat)
			 methodState->returnedObj = args[2];
			else
			 methodState->returnedObj = args[3];
			break;
		case 90: printf("Float ~= Float"); break;
		case 91: // float1 * float2 (args: float1 float2 floatclass objectIfFail)
			result2 = Image[args[0]]->dataAsFloat * Image[args[1]]->dataAsFloat;
			if(isFloatOverflow(result2))
			  methodState->returnedObj = args[3];
			else {
			  methodState->returnedObj = newObj(args[2], 4, 0);
			  Image[methodState->returnedObj]->dataAsFloat = (float) result2;
			}
			break;
		case 92: // float1 / float2 (args: float1 float2 floatclass objectIfFail)
			result2 = Image[args[0]]->dataAsFloat / Image[args[1]]->dataAsFloat;
			if(isFloatOverflow(result2))
			  methodState->returnedObj = args[3];
			else {
			  methodState->returnedObj = newObj(args[2], 4, 0);
			  Image[methodState->returnedObj]->dataAsFloat = (float) result2;
			}
			break;
		case 93: // float1 truncated (args: float1 floatclass) - возвращает только целую часть //!!!
			result = (signed long) Image[args[0]]->dataAsFloat;
/*			if(isOverflow(result)
			  methodState->returnedObj = nilObject;
			else {*/
			  methodState->returnedObj = newObj(args[1], 4, 0);
			  Image[methodState->returnedObj]->dataAsFloat = (float) result;
//			}
			break;
		case 94: // float1 fractionPart (args: float1 floatclass) - вернуть дробную часть
			result2 = Image[args[0]]->dataAsFloat - ((signed long) Image[args[0]]->dataAsFloat);
			if(result2 < 0) result2 = result2 * -1.0f;
			methodState->returnedObj = newObj(args[1], 4, 0);
			Image[methodState->returnedObj]->dataAsFloat = (float) result2;
			break;
		case 95: // float1 exponent (args: float1 floatclass) - вычислить экспоненту
			/*float1 = (float*) &Image[curContext->args_data[0]]->data;
			result2 = exp(*float1);
			methodState->returnedObj = newObj(floatClass,4,0);
			*((float *) &Image[methodState->returnedObj]->data) = (float) result2;*/
			methodState->returnedObj = args[0];
			break;
		case 96: printf("Float timesTwoPower:(?)"); methodState->returnedObj = args[0]; break;
		case 97: printf("largeint + largeint"); methodState->returnedObj = args[0]; break;
		case 98: printf("largeint - largeint"); methodState->returnedObj = args[0]; break;

		case 112: //Transcript showCr: aString (args: obj1) - отладочный вывод через libc функцию puts (используется для тестов)
			string[0] = (char) 0;
			for(i = 0; (i < Image[args[0]]->size) && (i < 500); i++)
				string[i] = (&Image[args[0]]->dataAsChar)[i];
			string[i] = 0;

			extern int testOutFile;  // mystexp.c
			if(testOutFile > 0) compareTestFile(&string, i+1);
			else puts(string);
			break;

		case 126: // compactDictionary1 valueAtKey: obj1 (args: compactDictionary1 obj1 objectIfFail) - поиск значения в словоре compactDictionary1 по ключу obj1
			/*if(args[0] == 0) firstObj = SmalltalkDictionary;
			else*/ firstObj = args[0];		   // compactDictionary
			secondObj = args[1];		    // искомая строка
			collection = &Image[firstObj]->data;
			str = &Image[secondObj]->dataAsChar;
			methodState->returnedObj = args[2];   // на случай если не нашли
			// ищем...
			for(i = 0; i < Image[firstObj]->size/4; i += 2){
				// если длинна совпала то делаем посимвольное сравнение
				if(Image[collection[i]]->size == Image[secondObj]->size){
					for(i2 = 0; i2 < Image[collection[i]]->size; i2++)
						if((&Image[collection[i]]->dataAsChar)[i2] != str[i2]) break;
					if(i2 == Image[collection[i]]->size) {
						methodState->returnedObj = collection[i+1];
						break;
					}
				}
			}
			break;
		case 127: printf("version?"); break;
	}

	return 0;
}

int extendedCall(objNum firstData, objNum secondData, objNum *methodSateObj){ // (перевод: расширенный вызов)
//
	return 0;
}
