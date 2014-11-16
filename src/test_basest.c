/***************************************************************************
 *   Copyright (C) 2006 by Saemon Zixel                                    *
 *   saemon@pochta.ru                                                      *
 *                                                                         *
 ***************************************************************************/

#include "types.h"
#include "imagemng.h"
#include <stdio.h>

#define inithookCall_args hookCall_args[0]=hookCall_args[1]=hookCall_args[2]=hookCall_args[3]=hookCall_args[4]=hookCall_args[5]=hookCall_args[6]=0

int hookCall = 0;
 int hookCall_primitiveNumber;
 objNum hookCall_args[7] = {0, 0, 0, 0, 0, 0, 0};
int Var1,Var2;
double Var3;


int compareStr(char * str, objNum strobj) {
int i;
      if((strobj > ImageLimit) || (strobj == 0) || (Image[strobj] == 0)) {
        printf("compareStr: bad objNum -> %li\n", strobj);
        return 0;
      }
      for(i = 0; ; i++) {
       if((str[i] == 0) && (Image[strobj]->size == i)) return 1;
       if((str[i] == 0) || (Image[strobj]->size == i)) break;
       if(str[i] != (&Image[strobj]->dataAsChar)[i]) break;
      }
      return 0;
}

objNum searchTest(char *testName, objNum tests) {
int i;
objNum *rows;

	rows = &Image[tests]->data;
	for(i = 0; i < Image[tests]->size / 4; i = i + 2) {
	   if(compareStr(testName, rows[i])) return rows[i + 1];
	}
	return 0;
}

int unitest(objNum testmethod, objNum inclass, int need, char *testname, char *needclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if(((Image[retObj]->size == 0) && (compareStr(needclass, Image[Image[retObj]->class]->data)))
	    || ((Image[retObj]->size > 3) && (Image[retObj]->data == need))
	    || ((Image[retObj]->size == 1) && (((char *) &Image[retObj]->data)[0] == (char) need))) {
	 printf("%s... ok!\n", testname);
	 return 0;
	} else {
	 printf("%s... FAILD!\n", testname);
	 printf("Obj(%li).class = %li\n", retObj, Image[retObj]->class);
	 return 1;
	}
}

int test_Block1(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if(Image[retObj]->data == 1){
	 puts("test_Block1 ok!");
	 return 0;
	} else {
	 puts("test_Block1 FAILD!");
	 return 1;
	}
}

int test_Block2(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if(Image[retObj]->size > 3)
	  if(compareStr("Integer",Image[retObj]->data)){
	   puts("test_Block2 ok!");
	   return 0;
	  }
	puts("test_Block2 FAILD!");
	return 1;
}

int test_Block3(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if(Image[retObj]->data == 2){
	 puts("test_Block3 ok!");
	 return 0;
	} else {
	 puts("test_Block3 FAILD!");
	 printf("Obj(%li).class = %li\n", retObj, Image[retObj]->class);
	 return 1;
	}
}

int test_Block4(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if(Image[retObj]->data == 3){
	 puts("test_Block4 ok!");
	 return 0;
	} else {
	 puts("test_Block4 FAILD!");
	 printf("Obj(%li).class = %li\n", retObj, Image[retObj]->class);
	 return 1;
	}
}

int test_Block5(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if(Image[retObj]->data == 6){
	 puts("test_Block5 ok!");
	 return 0;
	} else {
	 puts("test_Block5 FAILD!");
	 printf("Obj(%li).class = %li\n", retObj, Image[retObj]->class);
	 return 1;
	}
}

int test_Block6(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if(Image[retObj]->data == 9){
	 puts("test_Block6 ok!");
	 return 0;
	} else {
	 puts("test_Block6 FAILD!");
	 if(Image[retObj]->data == 1) puts("Returned '1'");
	 printf("Obj(%li).class = %li\n", retObj, Image[retObj]->class);
	 return 1;
	}
}

int test_SymbolSearch1(objNum testmethod, objNum inclass) {
int result;
objNum classNameObj;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	classNameObj = ((struct ClassObject *) &Image[Image[retObj]->class]->data)->name;
	if(Image[classNameObj]->size == 4){
	  // "True" занимает ровно 4 байта что соответствует long и является числом 1702195796
	  if(Image[classNameObj]->data == 1702195796) {
	    puts("test_SymbolSearch1 ok!");
	    return 0;
	  }
	} 

	puts("test_SymbolSearch1 FAILD!");
	printf("Obj(%li).class = %li\n", retObj, Image[retObj]->class);
	return 1;	
}

int test_Block7(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if(Image[retObj]->data == 1){
	 puts("test_Block7 ok!");
	 return 0;
	} else {
	 puts("test_Block7 FAILD!");
	 printf("Obj(%li).class = %li\n", retObj, Image[retObj]->class);
	 return 1;
	}
}

int test_Block7a(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if(Image[retObj]->data == 99){
	 puts("test_Block7a ok!");
	 return 0;
	} else {
	 puts("test_Block7a FAILD!");
	 printf("Obj(%li).class = %li\n", retObj, Image[retObj]->class);
	 return 1;
	}
}

int test_Block8(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if(Image[retObj]->data == 4){
	 puts("test_Block8 ok!");
	 return 0;
	} else {
	 puts("test_Block8 FAILD!");
	 printf("Obj(%li).class = %li\n", retObj, Image[retObj]->class);
	 return 1;
	}
}

int test_Block9(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	puts("test_Block9 ... (BlockClosure style:  3,3,3 -> Squeak   1,2,3 -> VW  )");
	result = doMethod(testmethod, inclass, &retObj);
/*	if(Image[retObj]->data == 4){
	 puts("test_Block9 ok!");
	 return 0;
	} else {
	 puts("test_Block9 FAILD!");
	 printf("Obj(%l).class = %l\n", retObj, Image[retObj]->class);
	 return 1;
	}*/
	return 0;
}

int test_Block10(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 1;

	result = doMethod(testmethod, inclass, &retObj);
	if((signed long)Image[retObj]->data == 0){
	 puts("test_Block10 ok!");
	 return 0;
	} else {
	 puts("test_Block10 FAILD!");
	 printf("Obj(%li).class = %li\n", retObj, Image[retObj]->class);
	 return 1;
	}
}

int test_Block10b(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if((signed long)Image[retObj]->data == -1){
	 puts("test_Block10b ok!");
	 return 0;
	} else {
	 puts("test_Block10b FAILD!");
	 printf("Obj(%li).class = %li\n", retObj, Image[retObj]->class);
	 return 1;
	}
}

int test_Block11(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if(Image[retObj]->data == 10){
	 puts("test_Block11 ok!");
	 return 0;
	} else {
	 puts("test_Block11 FAILD!");
	 printf("Obj(%li).class = %li\n", retObj, Image[retObj]->class);
	 return 1;
	}
}

int test_Block12(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	hookCall = 1;
	hookCall_primitiveNumber = 112;
	inithookCall_args;
	result = doMethod(testmethod, inclass, &retObj);
	if((Image[hookCall_args[0]]->data == 2) && (Image[hookCall_args[1]]->data == 3)){
	 puts("test_Block12 ok!");
	 return 0;
	} else {
	 puts("test_Block12 FAILD!");
	 printf("arg1 = %li , arg2 = %li \n",Image[hookCall_args[0]]->data, Image[hookCall_args[0]]->data);
	 return 1;
	}
	hookCall = 0;
	hookCall_primitiveNumber = 0;
}

int test_OrderedCollection1(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if(compareStr("OrderedCollection",((struct ClassObject *) &Image[Image[retObj]->class]->data)->name)){
	 puts("test_OrderedCollection1 ok!");
	 return 0;
	} else {
	 puts("test_OrderedCollection1 FAILD!");
	 printf("Obj(%li).class = %li\n", retObj, Image[retObj]->class);
	 return 1;
	}
}

int test_OrderedCollection2(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if(Image[retObj]->data == 0){
	 puts("test_OrderedCollection2 ok!");
	 return 0;
	} else {
	 puts("test_OrderedCollection2 FAILD!");
	 printf("Obj(%li).class = %li\n", retObj, Image[retObj]->class);
	 return 1;
	}
}

int test_OrderedCollection3(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if(compareStr("OrderedCollection",((struct ClassObject *) &Image[Image[retObj]->class]->data)->name)
	&& (Image[((objNum *) &Image[retObj]->data)[0]]->data == 1)
	&& (Image[((objNum *) &Image[retObj]->data)[1]]->data == 2)
	&& (Image[((objNum *) &Image[retObj]->data)[2]]->data == 3)){
	 puts("test_OrderedCollection3 ok!");
	 return 0;
	} else {
	 puts("test_OrderedCollection3 FAILD!");
	 printf("Obj(%li).class = %li\n", retObj, Image[retObj]->class);
	 return 1;
	}
}

int test_OrderedCollection4(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if(Image[retObj]->data == 3){
	 puts("test_OrderedCollection4 ok!");
	 return 0;
	} else {
	 puts("test_OrderedCollection4 FAILD!");
	 printf("Obj(%li).class = %li\n", retObj, Image[retObj]->class);
	 return 1;
	}
}

int test_OrderedCollection5(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	hookCall = 1;
	hookCall_primitiveNumber = 112;
	inithookCall_args;
	result = doMethod(testmethod, inclass, &retObj);
	if((Image[hookCall_args[0]]->data == 1) && (Image[hookCall_args[1]]->data == 2) && (Image[hookCall_args[2]]->data == 3)){
	 puts("test_OrderedCollection5 ok!");
	 return 0;
	} else {
	 puts("test_OrderedCollection5 FAILD!");
	 return 1;
	}
	hookCall = 0;
	hookCall_primitiveNumber = 0;
}

int test_OrderedCollection6(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if(compareStr("OrderedCollection",((struct ClassObject *) &Image[Image[retObj]->class]->data)->name)
	&& (Image[((objNum *) &Image[retObj]->data)[0]]->data == 1)
	&& (Image[((objNum *) &Image[retObj]->data)[1]]->data == 2)){
	 puts("test_OrderedCollection6 ok!");
	 return 0;
	} else {
	 puts("test_OrderedCollection6 FAILD!");
	 printf("Obj(%li).class = %li\n", retObj, Image[retObj]->class);
	 return 1;
	}
}

int test_OrderedCollection7(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if(compareStr("OrderedCollection",((struct ClassObject *) &Image[Image[retObj]->class]->data)->name)
	&& (Image[((objNum *) &Image[retObj]->data)[0]]->data == 1)
	&& (Image[((objNum *) &Image[retObj]->data)[2]]->data == 3)
	&& (Image[((objNum *) &Image[retObj]->data)[1]]->data == 2)){
	 puts("test_OrderedCollection7 ok!");
	 return 0;
	} else {
	 puts("test_OrderedCollection7 FAILD!");
	 printf("Obj(%li).class = %li\n", retObj, Image[retObj]->class);
	 return 1;
	}
}

int test_OrderedCollection8(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if(compareStr("OrderedCollection",((struct ClassObject *) &Image[Image[retObj]->class]->data)->name)
	   && (Image[((objNum *) &Image[retObj]->data)[0]]->data == 1)
	   && Image[retObj]->size == 4){
	 puts("test_OrderedCollection8 ok!");
	 return 0;
	} else {
	 puts("test_OrderedCollection8 FAILD!");
	 printf("Obj(%li).class = %li\n", retObj, Image[retObj]->class);
	 return 1;
	}
}

int test_Simple1(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if(Image[retObj]->data == 2){
	 puts("test_Simple1 ok!");
	 return 0;
	} else {
	 puts("test_Simple1 FAILD!");
	 printf("Obj(%li).class = %li\n", retObj, Image[retObj]->class);
	 return 1;
	}
}

int test_Interval1(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if(compareStr("Interval", ((struct ClassObject *) &Image[Image[retObj]->class]->data)->name)
	&& (Image[(&Image[retObj]->data)[0]]->data == 1)
	&& (Image[(&Image[retObj]->data)[1]]->data == 3)
	&& (Image[(&Image[retObj]->data)[2]]->data == 1)){
	 puts("test_Interval1 ok!");
	 return 0;
	} else {
	 puts("test_Interval1 FAILD!");
	 printf("Obj(%li).class = %li\n", retObj, Image[retObj]->class);
	 return 1;
	}
}

int test_Interval2(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if(Image[retObj]->data == 9){
	 puts("test_Interval2 ok!");
	 return 0;
	} else {
	 puts("test_Interval2 FAILD!");
	 printf("Obj(%li).class = %li\n", retObj, Image[retObj]->class);
	 return 1;
	}
}

int test_Interval3(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	hookCall = 1;
	hookCall_primitiveNumber = 112;
	inithookCall_args;
	result = doMethod(testmethod, inclass, &retObj);
	if((Image[hookCall_args[0]]->data == 1) && (Image[hookCall_args[1]]->data == 2) && (Image[hookCall_args[2]]->data == 3)){
	 puts("test_Interval3 ok!");
	 return 0;
	} else {
	 puts("test_Interval3 FAILD!");
	 return 1;
	}
	hookCall = 0;
	hookCall_primitiveNumber = 0;

}

int test_Object1(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if((Image[retObj]->size == 0) &&
	  compareStr("Object",Image[Image[retObj]->class]->data)){
	 puts("test_Object1 ok!");
	 return 0;
	} else {
	 puts("test_Object1 FAILD!");
	 printf("Obj(%li).class = %li\n", retObj, Image[retObj]->class);
	 return 1;
	}
}

int test_Object1a(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if(compareStr("Object",Image[Image[retObj]->class]->data) &&
	  (Image[retObj]->size == 10) &&
	  (Image[retObj]->data == 0) &&
	  ((&Image[retObj]->data)[1] == 0) &&
	  (((char*) &Image[retObj]->data)[8] == 0) &&
	  (((char*) &Image[retObj]->data)[9] == 0)){
	 puts("test_Object1a ok!");
	 return 0;
	} else {
	 puts("test_Object1a FAILD!");
	 printf("Obj(%li).class = %li\n", retObj, Image[retObj]->class);
	 return 1;
	}
}

int test_Object2(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if((((char*) &Image[retObj]->data)[0] == 1) && (Image[retObj]->size == 1)){
	 puts("test_Object2 ok!");
	 return 0;
	} else {
	 puts("test_Object2 FAILD!");
	 printf("Obj(%li).data = %li, size=%li\n", retObj, ((char*) &Image[retObj]->data)[0],Image[retObj]->size);
	 return 1;
	}
}

int test_Object2a(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if((retObj != 0) && (Image[retObj] != 0) && (compareStr("Object",Image[retObj]->data))){
	 puts("test_Object2a (prim: 22) ok!");
	 return 0;
	} else {
	 puts("test_Object2a (prim: 22) FAILD! (It`s very Bad, becouse it is base 'at:' method)");
	 printf("Obj(%li).class = %li\n", retObj, Image[retObj]->class);
	 return 1;
	}
}

int test_Object3a(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if(Image[Image[retObj]->data]->data == 9){
	 puts("test_Object3a ok!");
	 return 0;
	} else {
	 puts("test_Object3a FAILD!");
	 printf("Obj(%li).class = %li\n", retObj, Image[retObj]->class);
	 return 1;
	}
}

int test_Object5(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if((Image[retObj]->size == 8) &&
	  (Image[retObj]->data == 1) &&
	  ((&Image[retObj]->data)[1] == 0)){
	 puts("test_Object5 ok!");
	 return 0;
	} else {
	 puts("test_Object5 FAILD!");
	 printf("Obj(%li).data = %li, size=%li\n", retObj, Image[retObj]->data, Image[retObj]->size);
	 return 1;
	}
}

int test_Object6(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if(compareStr("Integer",Image[retObj]->data)){
	 puts("test_Object6 ok!");
	 return 0;
	} else {
	 puts("test_Object6 FAILD!");
	 printf("Obj(%li).class = %li\n", retObj, Image[retObj]->class);
	 return 1;
	}
}

int test_Object7(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if(compareStr("Tests",Image[Image[retObj]->class]->data)){
	 puts("test_Object7 ok!");
	 return 0;
	} else {
	 puts("test_Object7 FAILD!");
	 printf("Obj(%li).class = %li\n", retObj, Image[retObj]->class);
	 return 1;
	}
}

int test_Object8(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if(Image[retObj]->flags & 4){
	 puts("test_Object8 ok!");
	 Image[retObj]->flags = Image[retObj]->flags ^ 4;
	 return 0;
	} else {
	 puts("test_Object8 FAILD!");
	 printf("Obj(%li).class = %li\n", retObj, Image[retObj]->class);
	 return 1;
	}
}

int test_Character1(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if(compareStr("Character", ((struct ClassObject *) &Image[Image[retObj]->class]->data)->name)
	&& (*((char *) &Image[retObj]->data) == 'a')){
	 puts("test_Character1 ok!");
	 return 0;
	} else {
	 puts("test_Character1 FAILD!");
	 printf("Obj(%li).class = %li\n", retObj, Image[retObj]->class);
	 return 1;
	}
}

int test_ByteArray1a(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if((Image[retObj]->size == 10) &&
	  (Image[retObj]->data == 0) &&
	  ((&Image[retObj]->data)[1] == 0) &&
	  (((unsigned short *) &Image[retObj]->data)[4] == 0)){
	 puts("test_ByteArray1a ok!");
	 return 0;
	} else {
	 puts("test_ByteArray1a FAILD!");
	 printf("Obj(%li).data = %li, size=%li\n", retObj, Image[retObj]->data, Image[retObj]->size);
	 return 1;
	}
}

int test_ByteArray2(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if((Image[retObj]->size == 10) &&
	  (Image[retObj]->data == 0) &&
	  ((&Image[retObj]->data)[1] == 5) &&
	  (((unsigned short *) &Image[retObj]->data)[4] == 0)){
	 puts("test_ByteArray2 ok!");
	 return 0;
	} else {
	 puts("test_ByteArray2 FAILD!");
	 printf("Obj(%li).data = %li, size=%li\n", retObj, Image[retObj]->data, Image[retObj]->size);
	 return 1;
	}
}

int test_ByteArray3(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if((Image[retObj]->size == 1) &&
	  (*((unsigned char *) &Image[retObj]->data) == 3)){
	 puts("test_ByteArray3 ok!");
	 return 0;
	} else {
	 puts("test_ByteArray3 FAILD!");
	 printf("Obj(%li).data = %li, size=%li\n", retObj, Image[retObj]->data, Image[retObj]->size);
	 return 1;
	}
}

int test_ByteArray5(objNum testmethod, objNum inclass) {
int result;
char tmp;
int i;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if(Image[retObj]->size == 40)
	  for(i=0; i < (Image[retObj]->size/4); i++){
	    tmp = Image[(&Image[retObj]->data)[i]]->dataAsChar;
	    if(tmp != 0)
	      if(!((tmp == 3) && (i == 2))){
		 puts("test_ByteArray5 FAILD!");
		 printf("Obj(%li).data = %i, size=%li\n", retObj, (int) Image[retObj]->dataAsChar, Image[retObj]->size);
		 return 1; 
	    }
	  }
	puts("test_ByteArray5 ok!");
	return 0;
}

int test_String1(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if(compareStr("String", ((struct ClassObject *) &Image[Image[retObj]->class]->data)->name)
	&& (compareStr("string ", retObj))){
	 puts("test_String1 ok!");
	 return 0;
	} else {
	 puts("test_String1 FAILD!");
	 printf("Obj(%li).class = %li\n", retObj, Image[retObj]->class);
	 return 1;
	}
}

int test_String5(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;
#warning lits[x] change not detecting!
	result = doMethod(testmethod, inclass, &retObj);
	if(compareStr("String", ((struct ClassObject *) &Image[Image[retObj]->class]->data)->name)
	&& (compareStr("string1string2", retObj))){
	 puts("test_String5 ok!");
	 return 0;
	} else {
	 puts("test_String5 FAILD!");
	 printf("Obj(%li).class = %li\n", retObj, Image[retObj]->class);
	 puts((char *) strndup((char *) &Image[retObj]->data, Image[retObj]->size));
	 return 1;
	}
}

int test_String6(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if(compareStr("Character", ((struct ClassObject *) &Image[Image[retObj]->class]->data)->name)
	&& (*((char*) &Image[retObj]->data) == 't')){
	 puts("test_String6 ok!");
	 return 0;
	} else {
	 puts("test_String6 FAILD!");
	 printf("Obj(%li).class = %li\n", retObj, Image[retObj]->class);
	 return 1;
	}
}

int test_String7(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if(compareStr("String", ((struct ClassObject *) &Image[Image[retObj]->class]->data)->name)
	&& (compareStr("string2", retObj))){
	 puts("test_String7 ok!");
	 return 0;
	} else {
	 puts("test_String7 FAILD!");
	 printf("Obj(%li).class = %li\n", retObj, Image[retObj]->class);
	 return 1;
	}
}

int test_String8(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if(compareStr("ByteArray", ((struct ClassObject *) &Image[Image[retObj]->class]->data)->name)
	&& (compareStr("string1", retObj))){
	 puts("test_String8 ok!");
	 return 0;
	} else {
	 puts("test_String8 FAILD!");
	 printf("Obj(%li).class = %li, size=%li\n", retObj, Image[retObj]->class, Image[retObj]->size);
	 for(result = 0; result < Image[retObj]->size; result++){
	   printf(" %c \n",(&Image[retObj]->dataAsChar)[result]);
	 }
	 return 1;
	}
}

int test_Float1(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if((Image[retObj]->size == 4) &&
	  (compareStr("Float", ((struct ClassObject *) &Image[Image[retObj]->class]->data)->name)) &&
	  (*((float *) &Image[retObj]->data) == 1.0f)){
	 puts("test_Float1 ok!");
	 return 0;
	} else {
	 puts("test_Float1 FAILD!");
	 printf("Obj(%li).class = %li, size=%li\n", retObj, Image[retObj]->class, Image[retObj]->size);
	 return 1;
	}
}

int test_Float2(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if((Image[retObj]->size == 4) &&
	  (compareStr("Float", ((struct ClassObject *) &Image[Image[retObj]->class]->data)->name)) &&
	  (*((float *) &Image[retObj]->data) == 0.5f)){
	 puts("test_Float2 ok!");
	 return 0;
	} else {
	 puts("test_Float2 FAILD!");
	 printf("Obj(%li).class = %li, size=%li\n", retObj, Image[retObj]->class, Image[retObj]->size);
	 return 1;
	}
}

int test_Float2a(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if((Image[retObj]->size == 4) &&
	  (compareStr("Float", ((struct ClassObject *) &Image[Image[retObj]->class]->data)->name)) &&
	  (*((float *) &Image[retObj]->data) == -0.5f)){
	 puts("test_Float2a ok!");
	 return 0;
	} else {
	 puts("test_Float2a FAILD!");
	 printf("Obj(%li).class = %li, size=%li\n", retObj, Image[retObj]->class, Image[retObj]->size);
	 return 1;
	}
}

int test_Float3(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if((Image[retObj]->size == 4) &&
	  (compareStr("Float", ((struct ClassObject *) &Image[Image[retObj]->class]->data)->name)) &&
	  (*((float *) &Image[retObj]->data) == -0.75f)){
	 puts("test_Float3 ok!");
	 return 0;
	} else {
	 puts("test_Float3 FAILD!");
	 printf("Obj(%li).data = %f, size=%li\n", retObj, *((float *) &Image[retObj]->data), Image[retObj]->size);
	 return 1;
	}
}

int test_Float4(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if((Image[retObj]->size == 4) &&
	  (compareStr("Float", ((struct ClassObject *) &Image[Image[retObj]->class]->data)->name)) &&
	  (*((float *) &Image[retObj]->data) == 0.0625f)){
	 puts("test_Float4 ok!");
	 return 0;
	} else {
	 puts("test_Float4 FAILD!");
	 printf("Obj(%li).data = %f, size=%li\n", retObj, *((float *) &Image[retObj]->data), Image[retObj]->size);
	 return 1;
	}
}

int test_Float6(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if((Image[retObj]->size == 4) &&
	  (compareStr("Float", ((struct ClassObject *) &Image[Image[retObj]->class]->data)->name)) &&
	  (*((float *) &Image[retObj]->data) == 0.5f)){
	 puts("test_Float6 ok!");
	 return 0;
	} else {
	 puts("test_Float6 FAILD!");
	 printf("Obj(%li).data = %f, size=%li\n", retObj, *((float *) &Image[retObj]->data), Image[retObj]->size);
	 return 1;
	}
}

int test_Float6a(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if((Image[retObj]->size == 4) &&
	  (compareStr("Float", ((struct ClassObject *) &Image[Image[retObj]->class]->data)->name)) &&
	  (*((float *) &Image[retObj]->data) == 0.5f)){
	 puts("test_Float6a ok!");
	 return 0;
	} else {
	 puts("test_Float6a FAILD!");
	 printf("Obj(%li).data = %f, size=%li\n", retObj, *((float *) &Image[retObj]->data), Image[retObj]->size);
	 return 1;
	}
}

int test_Float7(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if((Image[retObj]->size == 4) &&
	  (compareStr("Float", ((struct ClassObject *) &Image[Image[retObj]->class]->data)->name)) &&
	  (*((float *) &Image[retObj]->data) == 1.0f)){
	 puts("test_Float7 ok!");
	 return 0;
	} else {
	 puts("test_Float7 FAILD!");
	 printf("Obj(%li).data = %f, size=%li\n", retObj, *((float *) &Image[retObj]->data), Image[retObj]->size);
	 return 1;
	}
}

int test_smallint1(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if(compareStr("SmallInteger", ((struct ClassObject *) &Image[Image[retObj]->class]->data)->name)
	&& (*((char *) &Image[retObj]->data) == 10)){
	 puts("test_smallint1 ok!");
	 return 0;
	} else {
	 puts("test_smallint1 FAILD!");
	 printf("Obj(%li).class = %li\n", retObj, Image[retObj]->class);
	 return 1;
	}
}

int test_Pointer1(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if((Image[retObj]->size == 4) &&
	  (compareStr("Pointer", ((struct ClassObject *) &Image[Image[retObj]->class]->data)->name)) &&
	  (Image[retObj]->data == 0)){
	 puts("test_Pointer1 ok!");
	 return 0;
	} else {
	 puts("test_Pointer1 FAILD!");
	 printf("Obj(%li).class = %li, size=%li\n", retObj, Image[retObj]->class, Image[retObj]->size);
	 return 1;
	}
}

int test_Pointer1a(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if((Image[retObj]->size == 4) &&
	  (compareStr("Pointer", ((struct ClassObject *) &Image[Image[retObj]->class]->data)->name)) &&
	  (Image[retObj]->data != 0)){
	 puts("test_Pointer1a ok!");
	 return 0;
	} else {
	 puts("test_Pointer1a FAILD!");
	 printf("Obj(%li).class = %li, size=%li\n", retObj, Image[retObj]->class, Image[retObj]->size);
	 return 1;
	}
}

int test_Pointer1b(objNum testmethod, objNum inclass) {
int result;
objNum lit;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if((Image[retObj]->size == 4) &&
	  (compareStr("Pointer", ((struct ClassObject *) &Image[Image[retObj]->class]->data)->name)) &&
	  (Image[retObj]->data != 0)){
	  lit = Image[((struct MethodObject *) &Image[testmethod]->data)->literals]->data;
	  Image[lit]->flags = Image[lit]->flags ^ bitNotMoveableObj;
	 puts("test_Pointer1b ok!");
	 return 0;
	} else {
	 puts("test_Pointer1b FAILD!");
	 printf("Obj(%li).class = %li, size=%li\n", retObj, Image[retObj]->class, Image[retObj]->size);
	 return 1;
	}
}

int test_Pointer3(objNum testmethod, objNum inclass) {
int result;
objNum lit;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if((compareStr("SmallInteger", Image[Image[retObj]->class]->data)) &&
	  (Image[retObj]->size == 1) &&
	  ((&Image[retObj]->dataAsChar)[0] == 's')){
	  lit = Image[((struct MethodObject *) &Image[testmethod]->data)->literals]->data;
	  Image[lit]->flags = Image[lit]->flags ^ bitNotMoveableObj;
	 puts("test_Pointer3 ok!");
	 return 0;
	} else {
	 puts("test_Pointer3 FAILD!");
	 printf("Obj(%li).class = %li, size=%li data=%s\n", retObj, Image[retObj]->class, Image[retObj]->size,((char*) &Image[retObj]->data));
	 return 1;
	}
}

int test_Pointer3a(objNum testmethod, objNum inclass) {
int result;
objNum lit;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if((compareStr("ByteArray", Image[Image[retObj]->class]->data)) &&
	  (Image[retObj]->size == 3) &&
	  ((&Image[retObj]->dataAsChar)[0] == 's') &&
	  ((&Image[retObj]->dataAsChar)[1] == 't') &&
	  ((&Image[retObj]->dataAsChar)[2] == 'r')){
	  lit = Image[((struct MethodObject *) &Image[testmethod]->data)->literals]->data;
	  Image[lit]->flags = Image[lit]->flags ^ bitNotMoveableObj;
	 puts("test_Pointer3a ok!");
	 return 0;
	} else {
	 puts("test_Pointer3a FAILD!");
	 printf("Obj(%li).class = %li, size=%li data=%s\n", retObj, Image[retObj]->class, Image[retObj]->size,((char*) &Image[retObj]->data));
	 return 1;
	}
}

int test_Pointer3b(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if((compareStr("Pointer", Image[Image[retObj]->class]->data)) &&
	  (Image[retObj]->data != 0) &&
	  (((char*) Image[retObj]->dataAsPointer)[0] == 'S') &&
	  (((char*) Image[retObj]->dataAsPointer)[6] == '1')){
	  //Image[retObj]->formemmng = Image[retObj]->formemmng ^ bitNotMoveableObj;
	 puts("test_Pointer3b ok!");
	 return 0;
	} else {
	 puts("test_Pointer3b FAILD!");
	 printf("Obj(%li).class = %li, size=%li data=%s\n", retObj, Image[retObj]->class, Image[retObj]->size,((char*) Image[retObj]->data));
	 return 1;
	}
}

int test_Pointer3c(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if((compareStr("Pointer", Image[Image[retObj]->class]->data)) &&
	  (Image[retObj]->data != 0) &&
	  (((char*) Image[retObj]->dataAsPointer)[0] == 'S') &&
	  (((char*) Image[retObj]->dataAsPointer)[2] == 'R') &&
	  (((char*) Image[retObj]->dataAsPointer)[6] == '1')){
	 puts("test_Pointer3c ok!");
	 return 0;
	} else {
	 puts("test_Pointer3c FAILD!");
	 printf("Obj(%li).class = %li, size=%li\n", retObj, Image[retObj]->class, Image[retObj]->size);
	 return 1;
	}
}

int test_Pointer4(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if((compareStr("Pointer", Image[Image[retObj]->class]->data)) &&
	  (Image[retObj]->size == 4) &&
	  (Image[retObj]->data != 0) &&
	  (Image[retObj]->dataAsPointer == &Image[(&Image[retObj]->data)[1]]->data) &&
	  (compareStr("string1", Image[retObj]->data))){
	 puts("test_Pointer4 ok!");
	 return 0;
	} else {
	 puts("test_Pointer4 FAILD!");
	 printf("Obj(%li).class = %li, size=%li\n", retObj, Image[retObj]->class, Image[retObj]->size);
	 return 1;
	}
}

int test_Pointer5(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if((compareStr("Pointer", Image[Image[retObj]->class]->data)) &&
	  (Image[retObj]->size == 4) &&
	  (Image[retObj]->data != 0) &&
	  (((char *) Image[retObj]->dataAsPointer)[0] == 's') &&
	  (((char *) Image[retObj]->dataAsPointer)[6] == '1')){
	 puts("test_Pointer5 ok!");
	 return 0;
	} else {
	 puts("test_Pointer5 FAILD!");
	 printf("Obj(%li).class = %li, size=%li\n", retObj, Image[retObj]->class, Image[retObj]->size);
	 return 1;
	}
}

int test_SaveAndExit(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	puts("it was test_SaveAndExit");
}

int test_externalCall0(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if((Image[retObj]->size == 4) &&
	  (Image[retObj]->dataAsPointer == (void *) printf)){
	 puts("test_externalCall0 ok!");
	 return 0;
	} else {
	 puts("test_externalCall0 FAILD!");
	 printf("Obj(%li).class = %li, size=%li\n", retObj, Image[retObj]->class, Image[retObj]->size);
	 printf("%li == %i \n", Image[retObj]->data, printf);
	 return 1;
	}
}

int test_externalCall1(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if(Var1 == 65567){
	 puts("test_externalCall1 ok!");
	 return 0;
	} else {
	 puts("test_externalCall1 FAILD!");
	 printf("Var1 = %i\n", Var1);
	 return 1;
	}
}

int test_externalCall2(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if(Var3 == (double) 0.0f){
	 puts("test_externalCall2 ok!");
	 return 0;
	} else {
	 puts("test_externalCall2 FAILD! (it`s normal if double type not supported)");
	 printf("Var3 = %f \n", Var3);
	 return 1;
	}
}

int test_externalCall3(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if(((void *) Var1) == &Image[retObj]->data){
	 puts("test_externalCall3 ok!");
	 return 0;
	} else {
	 puts("test_externalCall3 FAILD!");
	 printf("Var1 = %i, need = %i\n", Var1 ,&Image[retObj]->data);
	 return 1;
	}
}

int test_externalCall4(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if((((char)Var1) == ' ') && (Var2 == 65537)){
	 puts("test_externalCall4 ok!");
	 return 0;
	} else {
	 puts("test_externalCall4 FAILD!");
	 printf("Var1 = %i, Var2 = %i\n", Var1 , Var2);
	 return 1;
	}
}

int test_externalCall5(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if((Var1 == (int)' ') && (Var2 == (int)'1')) puts("test_externalCall5 first half ok!");
	else {
	 puts("test_externalCall5 first half FAILD!");
	 printf("Var1 = %i, Var2 = %i\n", Var1 , Var2);
	}
	if(Var3 == (double) 0.0f){
	 puts("test_externalCall5 second half ok!");
	 return 0;
	} else {
	 puts("test_externalCall5 second half FAILD! (it`s normal if double type not supported)");
	 printf("Var3 = %f \n", Var3);
	 return 1;
	}
}

int test_externalCall6(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if((Image[retObj]->size == 1) &&
	(*((char *) &Image[retObj]->data) == ' ')){
	 puts("test_externalCall6 ok!");
	 return 0;
	} else {
	 puts("test_externalCall6 FAILD!");
	 printf("result = %c, size=%li\n", *((char *) &Image[retObj]->data), Image[retObj]->size);
	 return 1;
	}
}

int test_externalCall7(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if((Image[retObj]->size == 4) && (Image[retObj]->data == (int) ((1<<30)+4))){
	 puts("test_externalCall7 ok!");
	 return 0;
	} else {
	 puts("test_externalCall7 FAILD!");
	 printf("result = %li, size=%li\n", Image[retObj]->data, Image[retObj]->size);
	 return 1;
	}
}

int test_externalCall8(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if((Image[retObj]->size == 8) && (*((double *) &Image[retObj]->data) == (double) -1.1 )){
	 puts("test_externalCall8 ok!");
	 return 0;
	} else {
	 puts("test_externalCall8 FAILD!");
	 printf("result = %f, size=%li\n", *((double *) &Image[retObj]->data), Image[retObj]->size);
	 return 1;
	}
}

int test_externalCall9(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	if((Image[retObj]->size == sizeof(void *)) && (((void *) Image[retObj]->data) == &Var1)){
	 puts("test_externalCall9 ok!");
	 return 0;
	} else {
	 puts("test_externalCall9 FAILD!");
	 printf("result = %i, size=%li\n", ((void *) Image[retObj]->data), Image[retObj]->size);
	 return 1;
	}
}

int test_externalCall10(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	puts("it was test_externalCall10... (if you see 123 test is ok, else FAILD)");
//	printf("Obj(%l).class = %l, size=%i\n", retObj, Image[retObj]->class, Image[retObj]->size);
//	printf("%i == %i \n", Image[retObj]->data, printf);
	return 1;

}

int test_externalCall11(objNum testmethod, objNum inclass) {
int result;
objNum retObj = 0;

	result = doMethod(testmethod, inclass, &retObj);
	puts(" <- it was test_externalCall11...");
	puts("if you see version your installed ALSA library test is ok.");
//	printf("Obj(%l).class = %l, size=%i\n", retObj, Image[retObj]->class, Image[retObj]->size);
//	printf("%i == %i \n", Image[retObj]->data, printf);
	return 1;

}

void test_basest(objNum testClass, objNum methodSateObj) {
objNum tests, currentTest;


    tests = ((struct ClassObject *) &Image[Image[testClass]->class]->data)->methods;
    puts(" ###  Testing Base classes ### \n");
    puts(" # Base Set #");
    currentTest = searchTest("test_Simple1",tests);
    if(currentTest) test_Simple1(currentTest, testClass);
    currentTest = searchTest("test_Object1",tests);
    if(currentTest) test_Object1(currentTest, testClass);
    currentTest = searchTest("test_Object1a",tests);
    if(currentTest) test_Object1a(currentTest, testClass);
    currentTest = searchTest("test_Object2",tests);
    if(currentTest) test_Object2(currentTest, testClass);
    currentTest = searchTest("test_Object2a",tests);
    if(currentTest) test_Object2a(currentTest, testClass);
    currentTest = searchTest("test_Object3",tests);
    if(currentTest) unitest(currentTest, testClass, 256, "test_Object3", " ");
    currentTest = searchTest("test_Object3a",tests);
    if(currentTest) test_Object3a(currentTest, testClass);
    currentTest = searchTest("test_Object4",tests);
    if(currentTest) unitest(currentTest, testClass, 16, "test_Object4", " ");
    currentTest = searchTest("test_Object4a",tests);
    if(currentTest) unitest(currentTest, testClass, 16, "test_Object4a", " ");
    currentTest = searchTest("test_Object5",tests);
    if(currentTest) test_Object5(currentTest, testClass);
    currentTest = searchTest("test_Object6",tests);
    if(currentTest) test_Object6(currentTest, testClass);
    currentTest = searchTest("test_Object7",tests);
    if(currentTest) test_Object7(currentTest, testClass);
    currentTest = searchTest("test_Object8",tests);
    if(currentTest) test_Object8(currentTest, testClass);
    currentTest = searchTest("test_Object9",tests);
    if(currentTest) unitest(currentTest, testClass, -1, "test_Object9", "True");
    currentTest = searchTest("test_Object9a",tests);
    if(currentTest) unitest(currentTest, testClass, -1, "test_Object9a", "False");
    currentTest = searchTest("test_Object11",tests);
    if(currentTest) unitest(currentTest, testClass, 9, "test_Object11", " ");
    currentTest = searchTest("test_Object11a",tests);
    if(currentTest) unitest(currentTest, testClass, 2, "test_Object11a", " ");
    currentTest = searchTest("test_Object11b",tests);
    if(currentTest) unitest(currentTest, testClass, 4, "test_Object11b", " ");
    currentTest = searchTest("test_Object11c",tests);
    if(currentTest) unitest(currentTest, testClass, 5, "test_Object11c", " ");
    currentTest = searchTest("test_Integer1",tests);
    if(currentTest) unitest(currentTest, testClass, -1, "test_Integer1", "True");
    currentTest = searchTest("test_Integer1a",tests);
    if(currentTest) unitest(currentTest, testClass, -1, "test_Integer1a", "False");
    currentTest = searchTest("test_Integer1b",tests);
    if(currentTest) unitest(currentTest, testClass, -1, "test_Integer1b", "True");
    currentTest = searchTest("test_Integer2",tests);
    if(currentTest) unitest(currentTest, testClass, 3, "test_Integer2", " ");
    currentTest = searchTest("test_Integer3",tests);
    if(currentTest) unitest(currentTest, testClass, -1, "test_Integer3", " ");
    currentTest = searchTest("test_Integer4",tests);
    if(currentTest) unitest(currentTest, testClass, 6, "test_Integer4", " ");
    currentTest = searchTest("test_Integer5",tests);
    if(currentTest) unitest(currentTest, testClass, -1, "test_Integer5", "True");
    currentTest = searchTest("test_Integer6",tests);
    if(currentTest) unitest(currentTest, testClass, 2, "test_Integer6", " ");
    currentTest = searchTest("test_Integer7",tests);
    if(currentTest) unitest(currentTest, testClass, 2, "test_Integer7", " ");
    currentTest = searchTest("test_Integer8",tests);
    if(currentTest) unitest(currentTest, testClass, 0, "test_Integer8", " ");
    currentTest = searchTest("test_smallint1",tests);
    if(currentTest) test_smallint1(currentTest, testClass);
    currentTest = searchTest("test_smallint2",tests);
    if(currentTest) unitest(currentTest, testClass, -1, "test_smallint2", "True");
    currentTest = searchTest("test_Block1",tests);
    if(currentTest) test_Block1(currentTest, testClass);
    currentTest = searchTest("test_Block2",tests);
    if(currentTest) test_Block2(currentTest, testClass);
    currentTest = searchTest("test_Block3",tests);
    if(currentTest) test_Block3(currentTest, testClass);
    currentTest = searchTest("test_Block4",tests);
    if(currentTest) test_Block4(currentTest, testClass);
    currentTest = searchTest("test_Block5",tests);
    if(currentTest) test_Block5(currentTest, testClass);
    currentTest = searchTest("test_Block6",tests);
    if(currentTest) test_Block6(currentTest, testClass);
    currentTest = searchTest("test_Block10",tests);
    if(currentTest) test_Block10(currentTest, testClass);
    currentTest = searchTest("test_Block10b",tests);
    if(currentTest) test_Block10b(currentTest, testClass);

    puts("\n # Base Set 2 # ");
    currentTest = searchTest("test_Object10",tests);
    if(currentTest) unitest(currentTest, testClass, -1, "test_Object10", "False");
    currentTest = searchTest("test_Object10a",tests);
    if(currentTest) unitest(currentTest, testClass, -1, "test_Object10a", "True");
    currentTest = searchTest("test_Boolean1",tests);
    if(currentTest) unitest(currentTest, testClass, -1, "test_Boolean1", "True");
    currentTest = searchTest("test_Boolean1a",tests);
    if(currentTest) unitest(currentTest, testClass, -1, "test_Boolean1a", "False");
    currentTest = searchTest("test_Boolean2",tests);
    if(currentTest) unitest(currentTest, testClass, -1, "test_Boolean2", "False");
    currentTest = searchTest("test_Boolean2a",tests);
    if(currentTest) unitest(currentTest, testClass, -1, "test_Boolean2a", "True");
    currentTest = searchTest("test_Boolean3",tests);
    if(currentTest) unitest(currentTest, testClass, -1, "test_Boolean3", "False");
    currentTest = searchTest("test_Boolean3a",tests);
    if(currentTest) unitest(currentTest, testClass, -1, "test_Boolean3a", "True");
    currentTest = searchTest("test_Boolean4",tests);
    if(currentTest) unitest(currentTest, testClass, -1, "test_Boolean4", "True");
    currentTest = searchTest("test_Boolean4a",tests);
    if(currentTest) unitest(currentTest, testClass, -1, "test_Boolean4a", "False");
    currentTest = searchTest("test_Boolean5",tests);
    if(currentTest) unitest(currentTest, testClass, 1, "test_Boolean5", " ");
    currentTest = searchTest("test_Boolean5a",tests);
    if(currentTest) unitest(currentTest, testClass, -1, "test_Boolean5a", "UndefinedObject");
    currentTest = searchTest("test_Boolean6",tests);
    if(currentTest) unitest(currentTest, testClass, -1, "test_Boolean6", "UndefinedObject");
    currentTest = searchTest("test_Boolean6a",tests);
    if(currentTest) unitest(currentTest, testClass, 3, "test_Boolean6a", " ");
    currentTest = searchTest("test_Boolean7",tests);
    if(currentTest) unitest(currentTest, testClass, 6, "test_Boolean7", " ");
    currentTest = searchTest("test_Boolean7a",tests);
    if(currentTest) unitest(currentTest, testClass, 7, "test_Boolean7a", " ");
    currentTest = searchTest("test_Boolean8",tests);
    if(currentTest) unitest(currentTest, testClass, 9, "test_Boolean8", " ");
    currentTest = searchTest("test_Boolean8a",tests);
    if(currentTest) unitest(currentTest, testClass, 12, "test_Boolean8a", " ");
    currentTest = searchTest("test_UndefinedObject1",tests);
    if(currentTest) unitest(currentTest, testClass, -1, "test_UndefinedObject1", "True");
    currentTest = searchTest("test_UndefinedObject2",tests);
    if(currentTest) unitest(currentTest, testClass, -1, "test_UndefinedObject2", "False");
    currentTest = searchTest("test_UndefinedObject3",tests);
    if(currentTest) unitest(currentTest, testClass, 1, "test_UndefinedObject3", " ");
    currentTest = searchTest("test_UndefinedObject3a",tests);
    if(currentTest) unitest(currentTest, testClass, -1, "test_UndefinedObject3a", "UndefinedObject");
    currentTest = searchTest("test_UndefinedObject4",tests);
    if(currentTest) unitest(currentTest, testClass, 3, "test_UndefinedObject4", " ");
    currentTest = searchTest("test_UndefinedObject4a",tests);
    if(currentTest) unitest(currentTest, testClass, 6, "test_UndefinedObject4a", " ");
    currentTest = searchTest("test_SymbolSearch1",tests);
    if(currentTest) test_SymbolSearch1(currentTest, testClass);
    currentTest = searchTest("test_SymbolSearch2",tests);
    if(currentTest) unitest(currentTest, testClass, 0, "test_SymbolSearch2", "UndefinedObject");
    currentTest = searchTest("test_Block7",tests);
    if(currentTest) test_Block7(currentTest, testClass);
    currentTest = searchTest("test_Block7a",tests);
    if(currentTest) test_Block7a(currentTest, testClass);
    currentTest = searchTest("test_Block8",tests);
    if(currentTest) test_Block8(currentTest, testClass);
    currentTest = searchTest("test_Block9",tests);
    if(currentTest) test_Block9(currentTest, testClass);
    currentTest = searchTest("test_Block11",tests);
    if(currentTest) test_Block11(currentTest, testClass);
    currentTest = searchTest("test_Block12",tests);
    if(currentTest) test_Block12(currentTest, testClass);
    currentTest = searchTest("test_OrderedCollection1",tests);
    if(currentTest) test_OrderedCollection1(currentTest, testClass);
    currentTest = searchTest("test_OrderedCollection2",tests);
    if(currentTest) test_OrderedCollection2(currentTest, testClass);
    currentTest = searchTest("test_OrderedCollection3",tests);
    if(currentTest) test_OrderedCollection3(currentTest, testClass);
    currentTest = searchTest("test_OrderedCollection4",tests);
    if(currentTest) test_OrderedCollection4(currentTest, testClass);
    currentTest = searchTest("test_OrderedCollection5",tests);
    if(currentTest) test_OrderedCollection5(currentTest, testClass);
    currentTest = searchTest("test_OrderedCollection6",tests);
    if(currentTest) test_OrderedCollection6(currentTest, testClass);
    currentTest = searchTest("test_OrderedCollection7",tests);
    if(currentTest) test_OrderedCollection7(currentTest, testClass);
    currentTest = searchTest("test_OrderedCollection8",tests);
    if(currentTest) test_OrderedCollection8(currentTest, testClass);
    currentTest = searchTest("test_Interval1",tests);
    if(currentTest) test_Interval1(currentTest, testClass);
    currentTest = searchTest("test_Interval2",tests);
    if(currentTest) test_Interval2(currentTest, testClass);
    currentTest = searchTest("test_Interval3",tests);
    if(currentTest) test_Interval3(currentTest, testClass);
    currentTest = searchTest("test_Integer5a",tests);
    if(currentTest) unitest(currentTest, testClass, -1, "test_Integer5a", "False");
    currentTest = searchTest("test_Integer9",tests);
    if(currentTest) unitest(currentTest, testClass, 0, "test_Integer9", " ");
    currentTest = searchTest("test_Integer10",tests);
    if(currentTest) unitest(currentTest, testClass, 10, "test_Integer10", " ");
    currentTest = searchTest("test_Integer10a",tests);
    if(currentTest) unitest(currentTest, testClass, -1, "test_Integer10a", "UndefinedObject");
    currentTest = searchTest("test_Character1",tests);
    if(currentTest) test_Character1(currentTest, testClass);
    currentTest = searchTest("test_Character2",tests);
    if(currentTest) unitest(currentTest, testClass, 32, "test_Character2", " ");
    currentTest = searchTest("test_Character3",tests);
    if(currentTest) unitest(currentTest, testClass, -1, "test_Character3", "False");
    currentTest = searchTest("test_Character4",tests);
    if(currentTest) unitest(currentTest, testClass, -1, "test_Character4", "True");
    currentTest = searchTest("test_Character5",tests);
    if(currentTest) unitest(currentTest, testClass, (int) 'a', "test_Character5", " ");
    currentTest = searchTest("test_ByteArray1",tests);
    if(currentTest) unitest(currentTest, testClass, -1, "test_ByteArray1", "ByteArray");
    currentTest = searchTest("test_ByteArray1a",tests);
    if(currentTest) test_ByteArray1a(currentTest, testClass);
    currentTest = searchTest("test_ByteArray2",tests);
    if(currentTest) test_ByteArray2(currentTest, testClass);
    currentTest = searchTest("test_ByteArray3",tests);
    if(currentTest) test_ByteArray3(currentTest, testClass);
    currentTest = searchTest("test_ByteArray4",tests);
    if(currentTest) unitest(currentTest, testClass, 12, "test_ByteArray4", " ");
    currentTest = searchTest("test_ByteArray5",tests);
    if(currentTest) test_ByteArray5(currentTest, testClass);
    currentTest = searchTest("test_String1",tests);
    if(currentTest) test_String1(currentTest, testClass);
    currentTest = searchTest("test_String2",tests);
    if(currentTest) unitest(currentTest, testClass, -1, "test_String2", "False");
    currentTest = searchTest("test_String3",tests);
    if(currentTest) unitest(currentTest, testClass, -1, "test_String3", "True");
    currentTest = searchTest("test_String4",tests);
    if(currentTest) unitest(currentTest, testClass, -1, "test_String4", "True");
    currentTest = searchTest("test_String5",tests);
    if(currentTest) test_String5(currentTest, testClass);
    currentTest = searchTest("test_String6",tests);
    if(currentTest) test_String6(currentTest, testClass);
    currentTest = searchTest("test_String7",tests);
    if(currentTest) test_String7(currentTest, testClass);
    currentTest = searchTest("test_String8",tests);
    if(currentTest) test_String8(currentTest, testClass);
    currentTest = searchTest("test_Float1",tests);
    if(currentTest) test_Float1(currentTest, testClass);
    currentTest = searchTest("test_Float2",tests);
    if(currentTest) test_Float2(currentTest, testClass);
    currentTest = searchTest("test_Float2a",tests);
    if(currentTest) test_Float2a(currentTest, testClass);
    currentTest = searchTest("test_Float3",tests);
    if(currentTest) test_Float3(currentTest, testClass);
    currentTest = searchTest("test_Float4",tests);
    if(currentTest) test_Float4(currentTest, testClass);
    currentTest = searchTest("test_Float5",tests);
    if(currentTest) unitest(currentTest, testClass, -1, "test_Float5", "True");
    currentTest = searchTest("test_Float5a",tests);
    if(currentTest) unitest(currentTest, testClass, -1, "test_Float5a", "False");
    currentTest = searchTest("test_Float6",tests);
    if(currentTest) test_Float6(currentTest, testClass);
    currentTest = searchTest("test_Float6a",tests);
    if(currentTest) test_Float6a(currentTest, testClass);
    currentTest = searchTest("test_Float7",tests);
    if(currentTest) test_Float7(currentTest, testClass);
    currentTest = searchTest("test_Float8",tests);
    if(currentTest) unitest(currentTest, testClass, -1, "test_Float8", "True");
    currentTest = searchTest("test_Pointer1",tests);
    if(currentTest) test_Pointer1(currentTest, testClass);
    currentTest = searchTest("test_Pointer1a",tests);
    if(currentTest) test_Pointer1a(currentTest, testClass);
    currentTest = searchTest("test_Pointer1b",tests);
    if(currentTest) test_Pointer1b(currentTest, testClass);
    currentTest = searchTest("test_Pointer2",tests);
    if(currentTest) unitest(currentTest, testClass, -1, "test_Pointer2", "True");
    currentTest = searchTest("test_Pointer2a",tests);
    if(currentTest) unitest(currentTest, testClass, -1, "test_Pointer2a", "False");
    currentTest = searchTest("test_Pointer2b",tests);
    if(currentTest) unitest(currentTest, testClass, -1, "test_Pointer2b", "True");
    currentTest = searchTest("test_Pointer3",tests);
    if(currentTest) test_Pointer3(currentTest, testClass);
    currentTest = searchTest("test_Pointer3a",tests);
    if(currentTest) test_Pointer3a(currentTest, testClass);
    currentTest = searchTest("test_Pointer3b",tests);
    if(currentTest) test_Pointer3b(currentTest, testClass);
    currentTest = searchTest("test_Pointer3c",tests);
    if(currentTest) test_Pointer3c(currentTest, testClass);
    currentTest = searchTest("test_SaveAndExit",tests);
    if(currentTest) test_SaveAndExit(currentTest, testClass);
    currentTest = searchTest("test_externalCall0",tests);
    if(currentTest) test_externalCall0(currentTest, testClass);
    currentTest = searchTest("test_externalCall1",tests);
    if(currentTest) test_externalCall1(currentTest, testClass);
    currentTest = searchTest("test_externalCall2",tests);
    if(currentTest) test_externalCall2(currentTest, testClass);
    currentTest = searchTest("test_externalCall3",tests);
    if(currentTest) test_externalCall3(currentTest, testClass);
    currentTest = searchTest("test_externalCall4",tests);
    if(currentTest) test_externalCall4(currentTest, testClass);
    currentTest = searchTest("test_externalCall5",tests);
    if(currentTest) test_externalCall5(currentTest, testClass);
    currentTest = searchTest("test_externalCall6",tests);
    if(currentTest) test_externalCall6(currentTest, testClass);
    currentTest = searchTest("test_externalCall7",tests);
    if(currentTest) test_externalCall7(currentTest, testClass);
    currentTest = searchTest("test_externalCall8",tests);
    if(currentTest) test_externalCall8(currentTest, testClass);
    currentTest = searchTest("test_externalCall9",tests);
    if(currentTest) test_externalCall9(currentTest, testClass);
    currentTest = searchTest("test_externalCall10",tests);
    if(currentTest) test_externalCall10(currentTest, testClass);
    currentTest = searchTest("test_externalCall11",tests);
    if(currentTest) test_externalCall11(currentTest, testClass);
    puts("End testing Base classes");
}

int internalCallHook(int primitiveNumber, objNum curMS) {
int i;
    if((hookCall == 1) && (hookCall_primitiveNumber == primitiveNumber)) {
	for(i=0; i<10; i++)
	 if(hookCall_args[i] == 0){
	  hookCall_args[i] = Image[((struct MethodState *) &Image[curMS]->data)->args_obj]->data;
	  break;
	 }
	return hookCall;
    } else {
        return 0;
    }
}

void testInt(int intVar) {
	Var1 = Var2 = 0;
	Var3 = 0;
	Var1 = intVar;
}

void testDouble(short doubleVar) {
	Var1 = Var2 = 0;
	Var3 = 0;
	Var3 = (double) doubleVar;
}

// вконце должен быть возвращен объект на каторого была передана ссылка
void testPointer(void * voidPtr) {
	Var1 = Var2 = 0;
	Var3 = 0;
	Var1 = (int) voidPtr;
}

void test2args(char charVar, int intVar) { // можно по теории вызвать с 3 аргументами
	Var1 = Var2 = 0;
	Var3 = 0;
	Var1 = (int) charVar;
	Var2 = intVar;
}

void test3args(char charVar1, char charVar2, double doubleVar) {
	Var1 = Var2 = 0;
	Var3 = 0;
	Var1 = (int) charVar1;
	Var2 = (int) charVar2;
	Var3 = (double) doubleVar;
}

char testRetChar(void) {
	return ' ';
}

int testRetInt(void) {
	return (int) ((1<<30)+4);
}

double testRetDouble(void) {
	return (double) -1.1;
}

int * testRetPointer(void) {
	return &Var1;
}
