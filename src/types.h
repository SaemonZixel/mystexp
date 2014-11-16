/***************************************************************************
 *   Copyright (C) 2006 by Saemon Zixel                                    *
 *   saemon@pochta.ru                                                      *
 *                                                                         *
 ***************************************************************************/
#ifndef TYPES_H
#define TYPES_H

//#define debug
//#define primZero

typedef unsigned long objNum; //номер объекта
//typedef unsigned long* objNumPtr; //указатель на номер объекта

struct objHeader{
	unsigned long class; // номер объекта класса
	unsigned long flags; // устанавливается в 1 если внутри содержатся номера объектов, иначе 0 (0 - Integer,Float,String...)
				 // 32 бит начинает последовательность флагов (идущих к младшим битам) и говорит что объект нельзя двигать с места (т.е. на него есть указатель)
	unsigned long size; // в байтах
	union { // размер поля не должен быть больше sizeof(objNum) т.е. <=32
	  objNum data;
	  char dataAsChar;
	  short dataAsShort;
	  float dataAsFloat;
	  void* dataAsPointer;
	  signed long dataAsLong;
	};
};

typedef struct objHeader obj;  //сам объект

#define bitNotMoveableObj (1 << 31)

struct MethodObject {
	objNum bytecode;
	objNum literals;
	objNum argCount; // количество получаемых аргументов
	objNum tmpCount; // количество временных переменных используемых методом
	objNum InTheClass;
	objNum name;
};

struct ClassObject {
	objNum name;
	objNum super;
	objNum methods;
	objNum instCount; //  может использоватся примитивом 11 (сумма или паследнее ?)
};

struct BlockObject {  // привязка tmps и args осуществляется командой CALL 9 (block_assign_tmpsnargs)
	objNum bytecode;
	objNum literals;
	objNum argCount; // количество получаемых аргументов 
	objNum tmpCount; // количество временных переменных используемых блоком
	objNum inTheMethod; // ?
	objNum SavedState; //
};

struct MethodOrBlockHeader { // эта структура объявляется спициально для MethodState, т.к. там могут быть BlockObject и MethodObject
	objNum bytecode;      // первые 4 записи у MethodObject и BlockObject совпадают по формату
	objNum literals;
	objNum argCount;
	objNum tmpCount;
	objNum InTheClass; // у блока здесь InTheMethod, у метода InTheClass
};

struct MethodState { // а сдесь (просто Context,) ProcessContext, CurrentProcContext, _MethodState_
	objNum self;
	objNum method;
	objNum bytecodeOffset;
	objNum tmps_obj;
	objNum args_obj;
	objNum returnedObj; // Для коректного сохранения состояния процесса (чтоб можно было сахранить и загрузит с/на диск)
	objNum previousMethodState; // MethodState в который мы вернёмся если достигним конца bytecode
	objNum returnTo; // MethodState в который мы вернёмся если встретим инструкцию RET
};

/* новый
struct ObjectHeader {
	objNum		class;  // класс к котораму пренадлежит данный объект
	unsigned short	flags;	// разные флаги...
	unsigned short	formemmng; //  для сборьщика мусора и т.д.
	unsigned long	size;   // размер объекта (без заголовка)
};
*/

#endif
