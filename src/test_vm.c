/***************************************************************************
 *   Copyright (C) 2006 by Saemon Zixel                                    *
 *   saemon@pochta.ru                                                      *
 *                                                                         *
 ***************************************************************************/

#include "types.h"
#include "tests.data.h"
#include "imagemng.h"
#include <stdio.h>

#define cmd_mask   192	// 11000000b
#define trg_mask   56	// 00111000b
#define src_mask   7	// 00000111b

#define newImageSize 2000
obj *newImage[newImageSize];

/* --------------------------- Vm.c --------------------------------------------------- */

obj **initTestImage() {
unsigned long i;

	for(i = 0; i < newImageSize; i++) newImage[i] = 0;

	newImage[0]  = (obj*) &nullObject;
	newImage[10] = (obj*) &integerClass1;
	newImage[11] = (obj*) &integerClass1_name;
	newImage[20] = (obj*) &bytearrayClass;
	newImage[21] = (obj*) &bytearrayClass_name;
	newImage[30] = (obj*) &arrayClass;
	newImage[31] = (obj*) &arrayClass_name;
	newImage[40] = (obj*) &SymbolClass;
	newImage[41] = (obj*) &SymbolClass_name;

	newImage[80] = (obj*) &testMS_Symbol32;
	newImage[81] = (obj*) &testMS_Symbol24;
	newImage[82] = (obj*) &testMS_Symbol13;
	newImage[83] = (obj*) &testMS_Symbol41;
	newImage[84] = (obj*) &testMS_Symbol_5;
	newImage[85] = (obj*) &testMS_Symbol;

	newImage[99] = (obj*) &startObject;
	// 1 класс
	newImage[100] = (obj*) &testMS_1class;
	newImage[101] = (obj*) &testMS_1name;
	newImage[102] = (obj*) &testMS_1methoddict1;
	newImage[110] = (obj*) &testMS_1method1name;
	newImage[111] = (obj*) &testMS_1method2name;
	newImage[112] = (obj*) &testMS_1method3name;
	newImage[113] = (obj*) &testMS_1method4name;
	newImage[114] = (obj*) &testMS_1method5name;
	newImage[115] = (obj*) &testMS_1method6name;
	// 2 класс
	newImage[200] = (obj*) &testMS_2class;
	newImage[201] = (obj*) &testMS_2name;
	newImage[202] = (obj*) &testMS_2methoddict;
	newImage[210] = (obj*) &testMS_2method1name;
	newImage[211] = (obj*) &testMS_2method2name;
	newImage[212] = (obj*) &testMS_2method3name;
	newImage[213] = (obj*) &testMS_2method4name;
	newImage[214] = (obj*) &testMS_2method5name;
	newImage[215] = (obj*) &testMS_2method6name;
	// 3 класс
	newImage[300] = (obj*) &testMS_3class;
	newImage[301] = (obj*) &testMS_3name;
	newImage[302] = (obj*) &testMS_3methoddict;
	newImage[310] = (obj*) &testMS_3method1name;
	newImage[311] = (obj*) &testMS_3method2name;
	newImage[312] = (obj*) &testMS_3method3name;
	newImage[313] = (obj*) &testMS_3method4name;
	newImage[314] = (obj*) &testMS_3method5name;
	// 4 класс
	newImage[400] = (obj*) &testMS_4class;
	newImage[401] = (obj*) &testMS_4name;
	newImage[402] = (obj*) &testMS_4methoddict;
	newImage[410] = (obj*) &testMS_4method1name;
	newImage[411] = (obj*) &testMS_4method2name;
	// 1 метод
	newImage[500] = (obj*) &testMS_method1;
	newImage[501] = (obj*) &testMS_method1argCount;
	newImage[502] = (obj*) &testMS_method1tmpCount;
	newImage[503] = (obj*) &testMS_method1bytecode;
	newImage[504] = (obj*) &testMS_method1literals;
	// 1 блок
	newImage[510] = (obj*) &testMS_block1;
	newImage[511] = (obj*) &testMS_block1argCount;
	newImage[512] = (obj*) &testMS_block1tmpCount;
	newImage[513] = (obj*) &testMS_block1bytecode;
	newImage[514] = (obj*) &testMS_block1literals;
	// 2 метод
	newImage[550] = (obj*) &testMS_method2;
	newImage[551] = (obj*) &testMS_method2argCount;
	newImage[552] = (obj*) &testMS_method2tmpCount;
	newImage[553] = (obj*) &testMS_method2bytecode;
	newImage[554] = (obj*) &testMS_method2literals;
	// 2 блок
	newImage[560] = (obj*) &testMS_block2;
	newImage[561] = (obj*) &testMS_block2argCount;
	newImage[562] = (obj*) &testMS_block2tmpCount;
	newImage[563] = (obj*) &testMS_block2bytecode;
	newImage[564] = (obj*) &testMS_block2literals;
	newImage[570] = (obj*) &testMS_method2literal1;
	// 3 метод
	newImage[600] = (obj*) &testMS_method3;
	newImage[601] = (obj*) &testMS_method3argCount;
	newImage[602] = (obj*) &testMS_method3tmpCount;
	newImage[603] = (obj*) &testMS_method3bytecode;
	newImage[604] = (obj*) &testMS_method3literals;
	// 3 блок
	newImage[610] = (obj*) &testMS_block3;
	newImage[611] = (obj*) &testMS_block3argCount;
	newImage[612] = (obj*) &testMS_block3tmpCount;
	newImage[613] = (obj*) &testMS_block3bytecode;
	newImage[614] = (obj*) &testMS_block3literals;
	newImage[620] = (obj*) &testMS_method3literal1;
	newImage[621] = (obj*) &testMS_method3literal2;
	newImage[622] = (obj*) &testMS_method3literal3;
	// 1 MS
	newImage[701] = (obj*) &testMS_MS1;
	testMS_MS1[8] = 1;
	for(i = 3; i < 10; i++) testMS_MS1tmps[i] = (objNum) 0;
	newImage[702] = (obj*) &testMS_MS1tmps; // зачищять!
	for(i = 3; i < 11; i++) testMS_MS1args[i] = (objNum) 0;
	newImage[703] = (obj*) &testMS_MS1args; // зачищять!
	newImage[704] = (obj*) &testMS_MS1bytecodeOffset;
	// 2 MS
	newImage[801] = (obj*) &testMS_MS2;
	for(i = 3; i < 14; i++) testMS_MS2tmps[i] = (objNum) 0;
	newImage[802] = (obj*) &testMS_MS2tmps; // зачищять!
	for(i = 3; i < 11; i++) testMS_MS2args[i] = (objNum) 0;
	newImage[803] = (obj*) &testMS_MS2args; // зачищять!
	newImage[804] = (obj*) &testMS_MS2bytecodeOffset;
	// 2 MS
	newImage[821] = (obj*) &testMS_MS3;
	for(i = 3; i < 8; i++) testMS_MS3tmps[i] = (objNum) i-2;
	newImage[822] = (obj*) &testMS_MS3tmps; // зачищять!
	for(i = 3; i < 8; i++) testMS_MS3args[i] = (objNum) 0;
	newImage[823] = (obj*) &testMS_MS3args; // зачищять!
	newImage[824] = (obj*) &testMS_MS3bytecodeOffset;
	newImage[825] = (obj*) &testMS_MS3self;
	newImage[830] = (obj*) &testMS_method4;
	newImage[831] = (obj*) &testMS_method4argCount;
	newImage[832] = (obj*) &testMS_method4tmpCount;
	newImage[833] = (obj*) &testMS_method4bytecode;
	newImage[834] = (obj*) &testMS_method4literals;

	return newImage;
}

int souldBe_MS(objNum MSObj, objNum self, objNum method, objNum bytecodeOffset, objNum *tmps, int tmpssize, objNum *args, int argssize, objNum returnedObj, objNum previousMethodState, objNum returnTo) {
struct MethodState *MS;
int result = 1; // true
int i;

     if((MSObj != 0) && (Image[MSObj]->size >= sizeof(struct MethodState))){
	MS = (struct MethodState *) &Image[MSObj]->data;
	if(MS->self != self) {
		printf("MethodState not correct!: self=%li but should be %li\n", MS->self, self);
		result = 0;
	}

	if(MS->method != method){
		printf("MethodState not correct!: method=%li but should be %li\n", MS->method, method);
		result = 0;
	}

	if((Image[MS->bytecodeOffset] != 0) && (Image[MS->bytecodeOffset]->data != bytecodeOffset)) {
		printf("MethodState not correct!: bytecodeOffset=%li but should be %li\n", MS->bytecodeOffset, bytecodeOffset);
		result = 0;
	}

	if(Image[MS->tmps_obj]->size == tmpssize * 4){
	for(i = 0; i < Image[MS->tmps_obj]->size / 4; i++){
		if((&Image[MS->tmps_obj]->data)[i] != tmps[i]) {
		  printf("MethodState not correct!: tmps[%i]=%li but should be %li\n", i, (&Image[MS->tmps_obj]->data)[i], tmps[i]);
		  result = 0;
		}
	}} else {
		printf("MethodState not correct!: tmps size=%li but should be %i\n", Image[MS->tmps_obj]->size / 4, tmpssize);
		result = 0;
	}

	if((MS->args_obj != 0) && (Image[MS->args_obj]->size == argssize * 4)){
	for(i = 0; i<Image[MS->args_obj]->size / 4; i++){
		if((&Image[MS->args_obj]->data)[i] != args[i]) {
		  printf("MethodState not correct!: args[%i]=%li but should be %li\n", i, (&Image[MS->args_obj]->data)[i], args[i]);
		  result = 0;
		}
	}} else {
		printf("MethodState not correct!: args size=%li but should be %i\n", Image[MS->args_obj]->size/4, argssize);
		result = 0;
	}

	if(MS->returnedObj != returnedObj) {
		printf("MethodState not correct!: returnedObj=%li but should be %li\n", MS->returnedObj, returnedObj);
		result = 0;
	}

	if(MS->previousMethodState != previousMethodState) {
		printf("MethodState not correct!: previousMethodState=%li but should be %li\n", MS->previousMethodState, previousMethodState);
		result = 0;
	}

	if(MS->returnTo != returnTo) {
		printf("MethodState not correct!: returnTo=%li but should be %li\n", MS->returnTo, returnTo);
		result = 0;
	}
     } else {
	puts("MethodState Invalid!!! (is 0 or too small)");
	result = 0;
     }

	return result;
}

int test_vm_SMnRET1() {
objNum tempMS = 701; // Стартовый MthodState
objNum *args;
int result;
objNum prevMS1, retMS1;
objNum prevMS2, retMS2;
objNum prevMS3, retMS3;
objNum needtmps[10] = {0,0,0,0,0,0,0,0,0,0};
objNum needargs[10] = {0,0,0,0,0,0,0,0,0,0};

	puts("---- test_vm_SMnRET PHASE 1 ----- ");
	// подготавливаем стартовый контекст
	prevMS1 = 701;
	retMS1 = 701;

	// SM self -  заходим в первый метод (test3method4)
	args = &Image[((struct MethodState *) &Image[tempMS]->data)->args_obj]->data;
	args[0] = 999;
	args[1] = 9999;
	args[2] = 99999;
	executeInstruction(&tempMS, 128, 0, 4, -1, 2); // SM+trg_self+src_lit, 2
	// - проверяем -
	needargs[0] = 999;
	needargs[1] = 9999;
	needargs[2] = 99999;
	if(souldBe_MS(tempMS, 99, 550, 0, (objNum*) &needtmps, 3, (objNum*) &needargs, 7, 1, prevMS1, retMS1)) puts("Step1 ok!");
	else puts("Step1 Faild!");
	prevMS2 = tempMS;
	retMS2 = tempMS;
	((struct MethodState *) &Image[tempMS]->data)->returnedObj = 2;

	// SM super - заходим в метод (test2method4)
	args = &Image[((struct MethodState *) &Image[tempMS]->data)->args_obj]->data;
	args[0] = 888;
	args[1] = 8888;
	args[2] = 0;
	executeInstruction(&tempMS, 128, 0, 4, -1, 1); // SM+trg_self+src_lit, 1
	// - проверяем -
	needargs[0] = 888;
	needargs[1] = 8888;
	needargs[2] = 0;
	if(souldBe_MS(tempMS, 99, 500, 0, (objNum*) &needtmps, 2, (objNum*) &needargs, 7, 2, prevMS2, retMS2)) puts("Step2 ok!");
	else puts("Step2 Faild!");
	prevMS3 = tempMS;
	retMS3 = tempMS;
	((struct MethodState *) &Image[tempMS]->data)->returnedObj = 3;

	// RET - выходим в предыдущий метод
	args = &Image[((struct MethodState *) &Image[tempMS]->data)->args_obj]->data;
	args[0] = 777;
	args[1] = 7777;
	args[2] = 0;
	executeInstruction(&tempMS, 192, 16, -1, -1, -1); // RET+trg_retobj
	// - проверяем -
	needargs[0] = 777;
	needargs[1] = 7777;
	needargs[2] = 0;
	if(souldBe_MS(tempMS, 99, 550, 0, (objNum*) &needtmps, 3, (objNum*) &needargs, 7, 3, prevMS1, retMS1)) puts("Step3 ok!");
	else puts("Step3 Faild!");
	prevMS3 = 0;
	retMS3 = 0;
	((struct MethodState *) &Image[tempMS]->data)->returnedObj = 4;

	// RET - выходим в предыдущий метод
	args = &Image[((struct MethodState *) &Image[tempMS]->data)->args_obj]->data;
	args[0] = 666;
	args[1] = 6666;
	args[2] = 66666;
	executeInstruction(&tempMS, 192, 16, -1, -1, -1); // RET+trg_retobj
	// - проверяем -
	needargs[0] = 666;
	needargs[1] = 6666;
	needargs[2] = 66666;
	if(souldBe_MS(tempMS, 99, 600, 0, (objNum*) &needtmps, 6, (objNum*) &needargs, 7, 4, 0, 0)) puts("Step4 ok!");
	else puts("Step4 Faild!");
}

int test_vm_SMnRET2() {
objNum tempMS = 701; // Стартовый MthodState
objNum *args;
int result;
objNum prevMS1, retMS1;
objNum prevMS2, retMS2;
objNum prevMS3, retMS3;
objNum prevMS4, retMS4;
objNum block1, block2, block3;
objNum needtmps[10] = {0,0,0,0,0,0,0,0,0,0};
objNum needargs[10] = {0,0,0,0,0,0,0,0,0,0};

	puts("---- test_vm_SMnRET PHASE 2 ----- ");
	// Превязываем и заходим в блок (0 - test4 -> block1)
	args = &Image[((struct MethodState *) &Image[tempMS]->data)->args_obj]->data;
	args[0] = 610;
	internalCall(9, &tempMS);  // проверить как работает механизм привязки!!!
	// теперь новый и привязанный блок находится в methodState->returnedObj
	block1 = ((struct MethodState *) &Image[tempMS]->data)->returnedObj;
	args[0] = 66;
	executeInstruction(&tempMS, 128, 16, 6, 0, 1); // SM+trg_retobj+src_arg,0,1
	needargs[0] = 66;
	if(souldBe_MS(tempMS, 99, block1, 0,(objNum*) &needtmps, 2, (objNum*) &needargs, 7, block1, 701, 0)) puts("Step5 ok!");
	else puts("Step5 Faild!");
	prevMS1 = tempMS;
	retMS1 = tempMS;
	((struct MethodState *) &Image[tempMS]->data)->returnedObj = 6;

	// Делаем возврат из блока и смотрим куда вернулись (мы некуда невернулись т.к. ошибка) (0 - test4 - block1)
	args = &Image[((struct MethodState *) &Image[tempMS]->data)->args_obj]->data;
	args[0] = 666;
	args[1] = 6666;
	args[2] = 66666;
	if(executeInstruction(&tempMS, 192, 16, -1, -1, -1) == -1){ // RET+trg_retobj
	  // - проверяем -
	  needargs[0] = 666;
	  needargs[1] = 6666;
	  needargs[2] = 66666;
	  if(souldBe_MS(tempMS, 99, block1, 0, (objNum*) &needtmps, 2, (objNum*) &needargs, 7, 6, 701, 0)) puts("Step6 ok!");
	  else puts("Step6 Faild!");
	} else puts("Step6 Faild!");
	prevMS2 = tempMS;
	retMS2 = tempMS;
	((struct MethodState *) &Image[tempMS]->data)->returnedObj = 7;

	// привязываем block2 к предыдущему блоку и входим в него (0 - test4 - block1 -> block2)
	args = &Image[((struct MethodState *) &Image[tempMS]->data)->args_obj]->data;
	args[0] = 560;
	args[1] = 0;
	args[2] = 0;
	internalCall(9, &tempMS);  // проверить как работает механизм привязки!!!
	// теперь новый и привязанный блок находится в methodState->returnedObj
	block2 = ((struct MethodState *) &Image[tempMS]->data)->returnedObj;
	args[0] = 55;
	args[1] = 555;
	executeInstruction(&tempMS, 128, 16, 6, 0, 2); // SM+trg_retobj+src_arg,0,2
	needargs[0] = 55;
	needargs[1] = 555;
	needargs[2] = 0;
	if(souldBe_MS(tempMS, 99, block2, 0, (objNum*) &needtmps, 2, (objNum*) &needargs, 7, block2, prevMS2, 0)) puts("Step7 ok!");
	else puts("Step7 Faild!");
	prevMS3 = tempMS;
	retMS3 = tempMS;
	((struct MethodState *) &Image[tempMS]->data)->returnedObj = 8;

	// Делаем возврат из блока и смотрим куда вернулись (опять некуда не вернулись) (0 - test4 - block1 - block2)
	args = &Image[((struct MethodState *) &Image[tempMS]->data)->args_obj]->data;
	args[0] = 444;
	args[1] = 4444;
	args[2] = 44444;
	if(executeInstruction(&tempMS, 192, 16, -1, -1, -1) == -1){ // RET+trg_retobj
	  // - проверяем -
	  needargs[0] = 444;
	  needargs[1] = 4444;
	  needargs[2] = 44444;
	  if(souldBe_MS(tempMS, 99, block2, 0, (objNum*) &needtmps, 2, (objNum*) &needargs, 7, 8, prevMS2, 0)) puts("Step8 ok!");
	  else puts("Step8 Faild!");
	} else puts("Step8 Faild!");
	prevMS2 = tempMS;
	retMS2 = tempMS;
	((struct MethodState *) &Image[tempMS]->data)->returnedObj = 9;

	return;
}

int test_vm_SMnRET3() {
objNum tempMS = 701; // Стартовый MthodState
objNum *args;
int result;
objNum prevMS1, retMS1;
objNum prevMS2, retMS2;
objNum prevMS3, retMS3;
objNum prevMS4, retMS4;
objNum block1, block2, block3;
objNum needtmps[10] = {0,0,0,0,0,0,0,0,0,0};
objNum needargs[10] = {0,0,0,0,0,0,0,0,0,0};

	puts("---- test_vm_SMnRET PHASE 3 ----- ");
	// SM self -  заходим в первый метод (test2method4) (0 - test4 -> test2method4 )
	args = &Image[((struct MethodState *) &Image[tempMS]->data)->args_obj]->data;
	args[0] = 99;
	args[1] = 999;
	args[2] = 9999;
	args[3] = 99999;
	executeInstruction(&tempMS, 128, 0, 4, -1, 3); // SM+trg_self+src_lit, 3
	// - проверяем -
	needargs[0] = 99;
	needargs[1] = 999;
	needargs[2] = 9999;
	needargs[3] = 99999;
	if(souldBe_MS(tempMS, 99, 500, 0,(objNum*) &needtmps, 2, (objNum*) &needargs, 7, 1, 701, 701)) puts("Step9 ok!");
	else puts("Step9 Faild!");
	prevMS1 = tempMS;
	retMS1 = tempMS;
	((struct MethodState *) &Image[tempMS]->data)->returnedObj = 10;

	// Превязываем и заходим в блок (0 - test4 - test2method4 -> block1 )
	args = &Image[((struct MethodState *) &Image[tempMS]->data)->args_obj]->data;
	args[0] = 510;
	args[1] = 0;
	args[2] = 0;
	args[3] = 0;
	internalCall(9, &tempMS);  // проверить как работает механизм привязки!!!
	// теперь новый и привязанный блок находится в methodState->returnedObj
	block1 = ((struct MethodState *) &Image[tempMS]->data)->returnedObj;
	args[0] = 66;
	executeInstruction(&tempMS, 128, 16, 6, 0, 1); // SM+trg_retobj+src_arg,0,1
	needargs[0] = 66;
	needargs[1] = 0;
	needargs[2] = 0;
	needargs[3] = 0;
	if(souldBe_MS(tempMS, 99, block1, 0,(objNum*) &needtmps, 4, (objNum*) &needargs, 7, block1, prevMS1, 701)) puts("Step10 ok!");
	else puts("Step10 Faild!");
	prevMS2 = tempMS;
	retMS2 = tempMS;
	((struct MethodState *) &Image[tempMS]->data)->returnedObj = 11;

	// RET - выходим в предыдущий метод (0 - test4 <- block1 )
	args = &Image[((struct MethodState *) &Image[tempMS]->data)->args_obj]->data;
	args[0] = 888;
	args[1] = 8888;
	args[2] = 88888;
	executeInstruction(&tempMS, 192, 16, -1, -1, -1); // RET+trg_retobj
	// - проверяем -
	needargs[0] = 888;
	needargs[1] = 8888;
	needargs[2] = 88888;                            // MethodState tmps = 6
	if(souldBe_MS(tempMS, 99, 600, 0,(objNum*) &needtmps, 6, (objNum*) &needargs, 7, 11, 0, 0)) puts("Step11 ok!");
	else puts("Step11 Faild!");
	prevMS2 = 0;
	retMS2 = 0;
	prevMS1 = 0;
	retMS1 = 0;
	((struct MethodState *) &Image[tempMS]->data)->returnedObj = 12;

	// заново заходим в первый метод (test2method4) (0 - test4 -> test2method4 )
	args = &Image[((struct MethodState *) &Image[tempMS]->data)->args_obj]->data;
	args[0] = 77;
	args[1] = 777;
	args[2] = 7777;
	args[3] = 77777;
	executeInstruction(&tempMS, 128, 0, 4, -1, 3); // SM+trg_self+src_lit, 3
	// - проверяем -
	needargs[0] = 77;
	needargs[1] = 777;
	needargs[2] = 7777;
	needargs[3] = 77777;
	if(souldBe_MS(tempMS, 99, 500, 0,(objNum*) &needtmps, 2, (objNum*) &needargs, 7, 12, 701, 701)) puts("Step12 ok!");
	else puts("Step12 Faild!");
	prevMS1 = tempMS;
	retMS1 = tempMS;
	((struct MethodState *) &Image[tempMS]->data)->returnedObj = 13;

	// Превязываем и заходим в блок (0 - test4 - test2method4 -> block1 )
	args = &Image[((struct MethodState *) &Image[tempMS]->data)->args_obj]->data;
	args[0] = 510;
	args[1] = 0;
	args[2] = 0;
	args[3] = 0;
	internalCall(9, &tempMS);  // проверить как работает механизм привязки!!!
	// теперь новый и привязанный блок находится в methodState->returnedObj
	block1 = ((struct MethodState *) &Image[tempMS]->data)->returnedObj;
	args[0] = 55;
	args[1] = 555;
	executeInstruction(&tempMS, 128, 16, 6, 0, 2); // SM+trg_retobj+src_arg,0,2
	needargs[0] = 55;
	needargs[1] = 555;
	needargs[2] = 0;
	needargs[3] = 0;
	if(souldBe_MS(tempMS, 99, block1, 0, (objNum*) &needtmps, 4, (objNum*) &needargs, 7, block1, prevMS1, 701)) puts("Step13 ok!");
	else puts("Step13 Faild!");
	prevMS2 = tempMS;
	retMS2 = tempMS;
	((struct MethodState *) &Image[tempMS]->data)->returnedObj = 14;

	// привязываем block2 к предыдущему блоку и входим в него (0 - test4 - test2method4 - block1 -> block2 )
	args = &Image[((struct MethodState *) &Image[tempMS]->data)->args_obj]->data;
	args[0] = 560;
	args[1] = 0;
	args[2] = 0;
	internalCall(9, &tempMS);  // проверить как работает механизм привязки!!!
	// теперь новый и привязанный блок находится в methodState->returnedObj
	block2 = ((struct MethodState *) &Image[tempMS]->data)->returnedObj;
	args[0] = 44;
	args[1] = 444;
	executeInstruction(&tempMS, 128, 16, 6, 0, 2); // SM+trg_retobj+src_arg,0,2
	needargs[0] = 44;
	needargs[1] = 444;
	if(souldBe_MS(tempMS, 99, block2, 0,(objNum*) &needtmps, 2, (objNum*) &needargs, 7, block2, prevMS2, 701)) puts("Step14 ok!");
	else puts("Step14 Faild!");
	prevMS3 = tempMS;
	retMS3 = tempMS;
	((struct MethodState *) &Image[tempMS]->data)->returnedObj = 15;

	// RET - выходим в первый метод (0 - test4 <- block1 )
	args = &Image[((struct MethodState *) &Image[tempMS]->data)->args_obj]->data;
	args[0] = 999;
	args[1] = 9999;
	args[2] = 99999;
	executeInstruction(&tempMS, 192, 16, -1, -1, -1); // RET+trg_retobj
	// - проверяем -
	needargs[0] = 999;
	needargs[1] = 9999;
	needargs[2] = 99999;
	needargs[3] = 0;                            // MethodState tmps = 6
	if(souldBe_MS(tempMS, 99, 600, 0, (objNum*) &needtmps, 6, (objNum*) &needargs, 7, 15, 0, 0)) puts("Step15 ok!");
	else puts("Step15 Faild!");
	prevMS2 = 0;
	retMS2 = 0;
	prevMS3 = 0;
	retMS3 = 0;
	((struct MethodState *) &Image[tempMS]->data)->returnedObj = 16;

	return;
}

int test_vm_SMnRET4() {
objNum tempMS = 701; // Стартовый MthodState
objNum *args;
int result;
objNum prevMS1, retMS1;
objNum prevMS2, retMS2;
objNum prevMS3, retMS3;
objNum prevMS4, retMS4;
objNum block1, block2, block3;
objNum needtmps[10] = {0,0,0,0,0,0,0,0,0,0};
objNum needargs[10] = {0,0,0,0,0,0,0,0,0,0};

	puts("---- test_vm_SMnRET PHASE 4 ----- ");
	// заходим в первый метод (test3method4) (0 - test4 -> test3method4)
	args = &Image[((struct MethodState *) &Image[tempMS]->data)->args_obj]->data;
	args[0] = 99;
	args[1] = 999;
	args[2] = 9999;
	args[3] = 99999;
	executeInstruction(&tempMS, 128, 0, 4, -1, 2); // SM+trg_self+src_lit, 2
	// - проверяем -
	needargs[0] = 99;
	needargs[1] = 999;
	needargs[2] = 9999;
	needargs[3] = 99999;
	if(souldBe_MS(tempMS, 99, 550, 0, (objNum*) &needtmps, 3, (objNum*) &needargs, 7, 1, 701, 701)) puts("Step16 ok!");
	else puts("Step16 Faild!");
	prevMS1 = tempMS;
	retMS1 = tempMS;
	((struct MethodState *) &Image[tempMS]->data)->returnedObj = 17;

	// Превязываем и заходим в первый блок (0 - test4 - test3method4 -> block1)
	args = &Image[((struct MethodState *) &Image[tempMS]->data)->args_obj]->data;
	args[0] = 560; // block3
	args[1] = 0;
	args[2] = 0;
	args[3] = 0;
	internalCall(9, &tempMS);  // проверить как работает механизм привязки!!!
	// теперь новый и привязанный блок находится в methodState->returnedObj
	block1 = ((struct MethodState *) &Image[tempMS]->data)->returnedObj;
	args[0] = 66;
	args[1] = 666;
	executeInstruction(&tempMS, 128, 16, 6, 0, 2); // SM+trg_retobj+src_arg,0,1
	needargs[0] = 66;
	needargs[1] = 666;
	needargs[2] = 0;
	needargs[3] = 0;
	if(souldBe_MS(tempMS, 99, block1, 0, (objNum*) &needtmps, 2, (objNum*) &needargs, 7, block1, prevMS1, 701)) puts("Step17 ok!");
	else puts("Step17 Faild!");
	prevMS2 = tempMS;
	retMS2 = tempMS;
	((struct MethodState *) &Image[tempMS]->data)->returnedObj = 18;

	// заходим во второй метод (test2method4) (0 - test4 - test3method4 - block1 -> test2method4)
	args = &Image[((struct MethodState *) &Image[tempMS]->data)->args_obj]->data;
	args[0] = 888;
	args[1] = 8888;
	args[2] = 0;
	executeInstruction(&tempMS, 128, 0, 4, -1, 0); // SM+trg_self+src_lit, 0
	// - проверяем -
	needargs[0] = 888;
	needargs[1] = 8888;
	needargs[2] = 0;
	needargs[3] = 0;
	if(souldBe_MS(tempMS, 99, 500, 0, (objNum*) &needtmps, 2, (objNum*) &needargs, 7, 18, prevMS2, retMS2)) puts("Step18 ok!");
	else puts("Step18 Faild!");
	prevMS3 = tempMS;
	retMS3 = tempMS;
	((struct MethodState *) &Image[tempMS]->data)->returnedObj = 19;

	// привязываем block2 к test2method4 и входим в него  (0 - test4 - test3method4 - block1 - test2method4 -> block2)
	args = &Image[((struct MethodState *) &Image[tempMS]->data)->args_obj]->data;
	args[0] = 510;
	args[1] = 0;
	args[2] = 0;
	internalCall(9, &tempMS);  // проверить как работает механизм привязки!!!
	// теперь новый и привязанный блок находится в methodState->returnedObj
	block2 = ((struct MethodState *) &Image[tempMS]->data)->returnedObj;
	args[0] = 44;
	executeInstruction(&tempMS, 128, 16, 6, 0, 1); // SM+trg_retobj+src_arg,0,1
	needargs[0] = 44;
	needargs[1] = 0;
	needargs[2] = 0;
	needargs[3] = 0;
	if(souldBe_MS(tempMS, 99, block2, 0, (objNum*) &needtmps, 4, (objNum*) &needargs, 7, block2, prevMS3, retMS2)) puts("Step19 ok!");
	else puts("Step19 Faild!");
	prevMS4 = tempMS;
	retMS4 = tempMS;
	((struct MethodState *) &Image[tempMS]->data)->returnedObj = 20;

	// RET - выходим в первый блок первого метода (0 - test4 - test3method4 - block1 <- block2)
	args = &Image[((struct MethodState *) &Image[tempMS]->data)->args_obj]->data;
	args[0] = 999;
	args[1] = 9999;
	args[2] = 99999;
	executeInstruction(&tempMS, 192, 16, -1, -1, -1); // RET+trg_retobj
	// - проверяем -
	needargs[0] = 999;
	needargs[1] = 9999;
	needargs[2] = 99999;
	if(souldBe_MS(tempMS, 99, block1, 0, (objNum*) &needtmps, 2, (objNum*) &needargs, 7, 20, prevMS1, 701)) puts("Step20 ok!");
	else puts("Step20 Faild!");
	prevMS3 = 0;
	retMS3 = 0;
	prevMS4 = 0;
	retMS4 = 0;
	((struct MethodState *) &Image[tempMS]->data)->returnedObj = 21;

	// привязываем block2 к block1 и входим в него  (0 - test4 - test3method4 - block1 -> block2)
	args = &Image[((struct MethodState *) &Image[tempMS]->data)->args_obj]->data;
	args[0] = 560; // неподходящий выбран блок!
	args[1] = 0;
	args[2] = 0;
	internalCall(9, &tempMS);  // проверить как работает механизм привязки!!!
	// теперь новый и привязанный блок находится в methodState->returnedObj
	block2 = ((struct MethodState *) &Image[tempMS]->data)->returnedObj;
	args[0] = 44;
	args[1] = 444;
	args[2] = 0;
	executeInstruction(&tempMS, 128, 16, 6, 0, 2); // SM+trg_retobj+src_arg,0,2
	needargs[0] = 44;
	needargs[1] = 444;
	needargs[2] = 0;
	if(souldBe_MS(tempMS, 99, block2, 0, (objNum*) &needtmps, 2, (objNum*) &needargs, 7, block2, prevMS2, 701)) puts("Step21 ok!");
	else puts("Step21 Faild!");
	prevMS3 = tempMS;
	retMS3 = tempMS;
	((struct MethodState *) &Image[tempMS]->data)->returnedObj = 23;

	// RET - выходим в самый первый метод  (0 - test4 <- block2)
	args = &Image[((struct MethodState *) &Image[tempMS]->data)->args_obj]->data;
	args[0] = 999;
	args[1] = 9999;
	args[2] = 99999;
	executeInstruction(&tempMS, 192, 16, -1, -1, -1); // RET+trg_retobj
	// - проверяем -
	needargs[0] = 999;
	needargs[1] = 9999;
	needargs[2] = 99999;                            // MethodState tmps = 6
	if(souldBe_MS(tempMS, 99, 600, 0, (objNum*) &needtmps, 6, (objNum*) &needargs, 7, 23, 0, 0)) puts("Step22 ok!");
	else puts("Step22 Faild!");

}

int test_vm_BlockTmps() {
objNum tempMS = 701; // Стартовый MthodState
objNum *args, *tmps;
int result;
objNum prevMS1, retMS1;
objNum prevMS2, retMS2;
objNum prevMS3, retMS3;
objNum prevMS4, retMS4;
objNum block1, block2, block3;
objNum needtmps[10] = {0,0,0,0,0,0,0,0,0,0};
objNum needargs[10] = {0,0,0,0,0,0,0,0,0,0};

	puts("---- test_vm_BlockTmps ----- ");
	// заходим в первый метод (test3method4)  (0 - test4 -> test3method4)
	args = &Image[((struct MethodState *) &Image[tempMS]->data)->args_obj]->data;
	args[0] = 99;
	args[1] = 999;
	args[2] = 9999;
	args[3] = 99999;
	tmps = &Image[((struct MethodState *) &Image[tempMS]->data)->tmps_obj]->data;
	tmps[0] = 11;
	tmps[1] = 111;
	tmps[2] = 1111;
	executeInstruction(&tempMS, 128, 0, 4, -1, 2); // SM+trg_self+src_lit, 2
	// - проверяем -
	needargs[0] = 99;
	needargs[1] = 999;
	needargs[2] = 9999;
	needargs[3] = 99999;
	if(souldBe_MS(tempMS, 99, 550, 0, (objNum*) &needtmps, 3, (objNum*) &needargs, 7, 1, 701, 701)) puts("preStep1 ok!");
	else puts("preStep1 Faild!");
	prevMS1 = tempMS;
	retMS1 = tempMS;

	// Превязываем и заходим в первый блок  (0 - test4 - test3method4 -> block1)
	args = &Image[((struct MethodState *) &Image[tempMS]->data)->args_obj]->data;
	args[0] = 560; // block1
	args[1] = 0;
	args[2] = 0;
	internalCall(9, &tempMS);
	// теперь новый и привязанный блок находится в methodState->returnedObj
	block1 = ((struct MethodState *) &Image[tempMS]->data)->returnedObj;
	args[0] = 66;
	args[1] = 666;
	args[2] = 0;
	args[3] = 0;
	tmps = &Image[((struct MethodState *) &Image[tempMS]->data)->tmps_obj]->data;
	tmps[0] = 22;
	tmps[1] = 222;
	tmps[2] = 2222;
	executeInstruction(&tempMS, 128, 16, 6, -1, 2); // SM+trg_retobj+src_arg,2
	needargs[0] = 66;
	needargs[1] = 666;
	needargs[2] = 0;
	needargs[3] = 0;
	if(souldBe_MS(tempMS, 99, block1, 0,(objNum*) &needtmps,2,(objNum*) &needargs,7, block1, prevMS1, 701)) puts("preStep2 ok!");
	else puts("preStep2 Faild!");
	prevMS2 = tempMS;
	retMS2 = tempMS;
	((struct MethodState *) &Image[tempMS]->data)->returnedObj = 1;

	tmps = &Image[((struct MethodState *) &Image[tempMS]->data)->tmps_obj]->data;
	tmps[0] = 33;
	tmps[1] = 333;
	
	// начинаем тестирование tmps блока
	executeInstruction(&tempMS, 64, 16, 5, -1, 0); // LD+trg_retobj+src_tmp,0
	if(((struct MethodState *) &Image[tempMS]->data)->returnedObj == 22) puts("BStep1 ok!");
	else{
	 puts("BStep1 Faild!");
	 printf(" returnedObj = %li\n", ((struct MethodState *) &Image[tempMS]->data)->returnedObj);
	}

	executeInstruction(&tempMS, 64, 16, 5, -1, 4); // LD+trg_retobj+src_tmp,4
	if(((struct MethodState *) &Image[tempMS]->data)->returnedObj == 333) puts("BStep2 ok!");
	else{
	 puts("BStep2 Faild!");
	 printf(" returnedObj = %li\n", ((struct MethodState *) &Image[tempMS]->data)->returnedObj);
	}

	// привязываем block2 к предыдущему блоку и входим в него (0 - test4 - test3method4 - block1 -> block2)
	args = &Image[((struct MethodState *) &Image[tempMS]->data)->args_obj]->data;
	args[0] = 610;
	args[1] = 0;
	args[2] = 0;
	internalCall(9, &tempMS);  // проверить как работает механизм привязки!!!
	// теперь новый и привязанный блок находится в methodState->returnedObj
	block2 = ((struct MethodState *) &Image[tempMS]->data)->returnedObj;
	args[0] = 44;
	args[1] = 444;
	executeInstruction(&tempMS, 128, 16, 6, 0, 2); // SM+trg_retobj+src_arg,0,2
	needargs[0] = 44;
	needargs[1] = 444;
	if(souldBe_MS(tempMS, 99, block2, 0,(objNum*) &needtmps, 2, (objNum*) &needargs, 7, block2, prevMS2, 701)) puts("preStep3 ok!");
	else puts("preStep3 Faild!");
	prevMS3 = tempMS;
	retMS3 = tempMS;
	((struct MethodState *) &Image[tempMS]->data)->returnedObj = 2;

	tmps = &Image[((struct MethodState *) &Image[tempMS]->data)->tmps_obj]->data;
	tmps[0] = 44;
	tmps[1] = 444;

	// продолжаем тестирование tmps у блоков
	executeInstruction(&tempMS, 64, 16, 5, -1, 6); // LD+trg_retobj+src_tmp,6
	if(((struct MethodState *) &Image[tempMS]->data)->returnedObj == 444) puts("BStep3 ok!");
	else{
	 puts("BStep3 Faild!");
	 printf(" returnedObj = %li\n", ((struct MethodState *) &Image[tempMS]->data)->returnedObj);
	}

	executeInstruction(&tempMS, 64, 16, 5, -1, 3); // LD+trg_retobj+src_tmp,3
	if(((struct MethodState *) &Image[tempMS]->data)->returnedObj == 33) puts("BStep4 ok!");
	else{
	 puts("BStep4 Faild!");
	 printf(" returnedObj = %li\n", ((struct MethodState *) &Image[tempMS]->data)->returnedObj);
	}

	// возвращаемся к начялу (0 - test4 <- block2)
	((struct MethodState *) &Image[tempMS]->data)->returnedObj = block2;
	executeInstruction(&tempMS, 192, 16, -1, -1, -1); // RET+trg_retobj
	needtmps[0] = 11;
	needtmps[1] = 111;
	needtmps[2] = 1111;
	if(souldBe_MS(tempMS, 99, 600, 0,(objNum*) &needtmps, 6, (objNum*) &needargs, 7, block2, 0, 0)) puts("preStep4 ok!");
	else puts("preStep4 Faild!");

	// заходим в block2 который привязан к block1 привязанный к test3method4 (0 - test4 <- block2)
	((struct MethodState *) &Image[tempMS]->data)->returnedObj = block2;
	args[0] = 99;
	args[1] = 999;
	args[2] = 0;
	executeInstruction(&tempMS, 128, 16, 6, 0, 2); // SM+trg_retobj+src_arg,0,2
	needargs[0] = 99;
	needargs[1] = 999;
	needtmps[0] = 0;
	needtmps[1] = 0;
	needtmps[2] = 0;
	if(souldBe_MS(tempMS, 99, block2, 0,(objNum*) &needtmps, 2, (objNum*) &needargs, 7, block2, 701, 0)) puts("preStep5 ok!");
	else puts("preStep5 Faild!");

	// продолжаем тестирование tmps у блоков
	executeInstruction(&tempMS, 64, 16, 5, -1, 0); // LD+trg_retobj+src_tmp,0
	if(((struct MethodState *) &Image[tempMS]->data)->returnedObj == 22) puts("BStep5 ok!");
	else{
	 puts("BStep5 Faild!");
	 printf(" returnedObj = %li\n", ((struct MethodState *) &Image[tempMS]->data)->returnedObj);
	}

	executeInstruction(&tempMS, 64, 16, 5, -1, 3); // LD+trg_retobj+src_tmp,3
	if(((struct MethodState *) &Image[tempMS]->data)->returnedObj == 33) puts("BStep6 ok!");
	else{
	 puts("BStep6 Faild!");
	 printf(" returnedObj = %li\n", ((struct MethodState *) &Image[tempMS]->data)->returnedObj);
	}

}

int test_vm_BlockTmps2() {
objNum tempMS = 701; // Стартовый MthodState
objNum *args, *tmps;
int result;
objNum prevMS1, retMS1;
objNum prevMS2, retMS2;
objNum prevMS3, retMS3;
objNum prevMS4, retMS4;
objNum block1, block2, block3;
objNum needtmps[10] = {0,0,0,0,0,0,0,0,0,0};
objNum needargs[10] = {0,0,0,0,0,0,0,0,0,0};

	puts("---- test_vm_BlockTmps 2 ----- ");
	// заходим в первый метод (test3method4)  (0 - test4 -> test3method4)
	args = &Image[((struct MethodState *) &Image[tempMS]->data)->args_obj]->data;
	args[0] = 99;
	args[1] = 999;
	args[2] = 9999;
	args[3] = 99999;
	tmps = &Image[((struct MethodState *) &Image[tempMS]->data)->tmps_obj]->data;
	tmps[0] = 11;
	tmps[1] = 111;
	tmps[2] = 1111;
	executeInstruction(&tempMS, 128, 0, 4, -1, 2); // SM+trg_self+src_lit, 2
	// - проверяем -
	needargs[0] = 99;
	needargs[1] = 999;
	needargs[2] = 9999;
	needargs[3] = 99999;
	if(souldBe_MS(tempMS, 99, 550, 0,(objNum*) &needtmps, 3, (objNum*) &needargs, 7, 1, 701, 701)) puts("preStep6 ok!");
	else puts("preStep6 Faild!");
	prevMS1 = tempMS;
	retMS1 = tempMS;

	// Превязываем и заходим в первый блок  (0 - test4 - test3method4 -> block1)
	args = &Image[((struct MethodState *) &Image[tempMS]->data)->args_obj]->data;
	args[0] = 560; // block1
	internalCall(9, &tempMS);
	// теперь новый и привязанный блок находится в methodState->returnedObj
	block1 = ((struct MethodState *) &Image[tempMS]->data)->returnedObj;
	args[0] = 66;
	args[1] = 666;
	args[2] = 0;
	args[3] = 0;
	tmps = &Image[((struct MethodState *) &Image[tempMS]->data)->tmps_obj]->data;
	tmps[0] = 22;
	tmps[1] = 222;
	tmps[2] = 2222;
	executeInstruction(&tempMS, 128, 16, 6, -1, 2); // SM+trg_retobj+src_arg,2
	needargs[0] = 66;
	needargs[1] = 666;
	needargs[2] = 0;
	needargs[3] = 0;
	if(souldBe_MS(tempMS, 99, block1, 0,(objNum*) &needtmps, 2, (objNum*) &needargs, 7, block1, prevMS1, 701)) puts("preStep7 ok!");
	else puts("preStep7 Faild!");
	prevMS2 = tempMS;
	retMS2 = tempMS;
	((struct MethodState *) &Image[tempMS]->data)->returnedObj = 1;

	tmps = &Image[((struct MethodState *) &Image[tempMS]->data)->tmps_obj]->data;
	tmps[0] = 33;
	tmps[1] = 333;
	
	// привязываем block2 к предыдущему блоку и входим в него (0 - test4 - test3method4 - block1 * block2)
	args = &Image[((struct MethodState *) &Image[tempMS]->data)->args_obj]->data;
	args[0] = 610;
	internalCall(9, &tempMS);  // проверить как работает механизм привязки!!!
	// теперь новый и привязанный блок находится в methodState->returnedObj
	block2 = ((struct MethodState *) &Image[tempMS]->data)->returnedObj;
	((struct MethodState *) &Image[tempMS]->data)->returnedObj = 1;

	// заходим в первый метод (test3method4)  (0 - test4 - test3method4 - block1 -> test2method4)
	args = &Image[((struct MethodState *) &Image[tempMS]->data)->args_obj]->data;
	args[0] = 44;
	args[1] = 444;
	args[2] = 4444;
	args[3] = 44444;
	executeInstruction(&tempMS, 128, 0, 4, -1, 0); // SM+trg_self+src_lit, 0
	// - проверяем -
	needargs[0] = 44;
	needargs[1] = 444;
	needargs[2] = 4444;
	needargs[3] = 44444;
	if(souldBe_MS(tempMS, 99, 500, 0,(objNum*) &needtmps, 2, (objNum*) &needargs, 7, 1, prevMS2, retMS2)) puts("preStep8 ok!");
	else puts("preStep8 Faild!");
	prevMS3 = tempMS;
	retMS3 = tempMS;

	tmps = &Image[((struct MethodState *) &Image[tempMS]->data)->tmps_obj]->data;
	tmps[0] = 55;
	tmps[1] = 555;
	
	// заходим в block2 привязанному к block1  (0 - test4 - test3method4 - block1 - test2method4 -> block2)
	args = &Image[((struct MethodState *) &Image[tempMS]->data)->args_obj]->data;
	args[0] = 66;
	args[1] = 666;
	args[2] = 0;
	args[3] = 0;
	((struct MethodState *) &Image[tempMS]->data)->returnedObj = block2;
	executeInstruction(&tempMS, 128, 16, 6, -1, 2); // SM+trg_retobj+src_arg,2
	// - проверяем -
	needargs[0] = 66;
	needargs[1] = 666;
	needargs[2] = 0;
	needargs[3] = 0;
	if(souldBe_MS(tempMS, 99, block2, 0,(objNum*) &needtmps, 2, (objNum*) &needargs, 7, block2, prevMS3, 701)) puts("preStep9 ok!");
	else puts("preStep9 Faild!");

	tmps = &Image[((struct MethodState *) &Image[tempMS]->data)->tmps_obj]->data;
	tmps[0] = 44;
	tmps[1] = 444;


	// рпродолжаем тестирование tmps у блоков
	executeInstruction(&tempMS, 64, 16, 5, -1, 6); // LD+trg_retobj+src_tmp,6
	if(((struct MethodState *) &Image[tempMS]->data)->returnedObj == 444) puts("BStep7 ok!");
	else{
	 puts("BStep7 Faild!");
	 printf(" returnedObj = %li\n", ((struct MethodState *) &Image[tempMS]->data)->returnedObj);
	}

	executeInstruction(&tempMS, 64, 16, 5, -1, 3); // LD+trg_retobj+src_tmp,3
	if(((struct MethodState *) &Image[tempMS]->data)->returnedObj == 33) puts("BStep8 ok!");
	else{
	 puts("BStep8 Faild!");
	 printf(" returnedObj = %li\n", ((struct MethodState *) &Image[tempMS]->data)->returnedObj);
	}

	executeInstruction(&tempMS, 64, 16, 5, -1, 0); // LD+trg_retobj+src_tmp,0
	if(((struct MethodState *) &Image[tempMS]->data)->returnedObj == 22) puts("BStep9 ok!");
	else{
	 puts("BStep9 Faild!");
	 printf(" returnedObj = %li\n", ((struct MethodState *) &Image[tempMS]->data)->returnedObj);
	}
}

int test_vm_assertequ(objNum methodStateObj, int cmd,int trgnum,int srcnum) {
unsigned char type, trg_type, src_type;
long trg, src;
int result;

	type = trg_type = src_type = 0;
	trg = src = 0;
	result = getNextInstruction(methodStateObj, &type, &trg_type, &src_type, &trg,&src);
	if(result==0){
	 if(type == (cmd & cmd_mask))
	  if(trg_type == (cmd & trg_mask))
	   if(src_type== (cmd & src_mask))
	    if((trg == trgnum) || (trgnum <0))
	     if((src == srcnum) || (srcnum <0)) puts("ok");
	     else puts("FAILD! (src)");
	    else puts("FAILD! (trg)");
	   else puts("FAILD! (src_type)");
	  else puts("FAILD! (trg_type)");
	 else puts("FAILD! (type)");
	} else puts("FAILD! (result != 0)");
	return result;
}

void test_vm_getNextInstruction(void) {
unsigned char type, trg_type, src_type;
long trg, src;
int result;


	puts("---- test_vm_getNextInstruction ----- ");

	type = trg_type = src_type = trg = src = 0;

	// в test.data.h объект 801 это MethodState с методом test2method4(500) специально для этого теста
	printf(" SM+trg_inst+src_inst,1,1... ");
	test_vm_assertequ(801, 191, 1, 1);
	printf(" SM+trg_inst+src_arg,1,1... ");
	test_vm_assertequ(801, 190, 1, 1);
	printf(" SM+trg_inst+src_tmp,1,1... ");
	test_vm_assertequ(801, 189, 1, 1);
	printf(" SM+trg_inst+src_lit,1,1... ");
	test_vm_assertequ(801, 188, 1, 1);
	printf(" SM+trg_inst+src_retobj,1... ");
	test_vm_assertequ(801, 186, 1, -1);
	printf(" SM+trg_inst+src_super,1... ");
	test_vm_assertequ(801, 185, 1, -1);
	printf(" SM+trg_inst+src_self,1... ");
	test_vm_assertequ(801, 184, 1, -1);
	printf(" SM+trg_arg+src_inst,1,1... ");
	test_vm_assertequ(801, 183, 1, 1);
	printf(" SM+trg_arg+src_arg,1,1... ");
	test_vm_assertequ(801, 182, 1, 1);
	printf(" SM+trg_arg+src_tmp,1,1... ");
	test_vm_assertequ(801, 181, 1, 1);
	printf(" SM+trg_arg+src_lit,1,1... ");
	test_vm_assertequ(801, 180, 1, 1);
	printf(" SM+trg_arg+src_retobj,1... ");
	test_vm_assertequ(801, 178, 1, -1);
	printf(" SM+trg_arg+src_super,1... ");
	test_vm_assertequ(801, 177, 1, -1);
	printf(" SM+trg_arg+src_self,1... ");
	test_vm_assertequ(801, 176, 1, -1);
	printf(" SM+trg_tmp+src_inst,1,1... ");
	test_vm_assertequ(801, 175, 1, 1);
	printf(" SM+trg_tmp+src_arg,1,1... ");
	test_vm_assertequ(801, 174, 1, 1);
	printf(" SM+trg_tmp+src_tmp,1,1... ");
	test_vm_assertequ(801, 173, 1, 1);
	printf(" SM+trg_tmp+src_lit,1,1... ");
	test_vm_assertequ(801, 172, 1, 1);
	printf(" SM+trg_tmp+src_retobj,1... ");
	test_vm_assertequ(801, 170, 1, -1);
	printf(" SM+trg_tmp+src_super,1... ");
	test_vm_assertequ(801, 169, 1, -1);
	printf(" SM+trg_tmp+src_self,1... ");
	test_vm_assertequ(801, 168, 1, -1);
	printf(" SM+trg_retobj+src_inst,1... ");
	test_vm_assertequ(801, 151, -1, 1);
	printf(" SM+trg_retobj+src_arg,1... ");
	test_vm_assertequ(801, 150, -1, 1);
	printf(" SM+trg_retobj+src_tmp,1... ");
	test_vm_assertequ(801, 149, -1, 1);
	printf(" SM+trg_retobj+src_lit,1... ");
	test_vm_assertequ(801, 148, -1, 1);
	printf(" SM+trg_retobj+src_retobj... ");
	test_vm_assertequ(801, 146, -1, -1);
	printf(" SM+trg_retobj+src_super... ");
	test_vm_assertequ(801, 145, -1, -1);
	printf(" SM+trg_retobj+src_self... ");
	test_vm_assertequ(801, 144, -1, -1);
	printf(" SM+trg_self+src_inst,1... ");
	test_vm_assertequ(801, 135, -1, 1);
	printf(" SM+trg_self+src_arg,1... ");
	test_vm_assertequ(801, 134, -1, 1);
	printf(" SM+trg_self+src_tmp,1... ");
	test_vm_assertequ(801, 133, -1, 1);
	printf(" SM+trg_self+src_lit,1... ");
	test_vm_assertequ(801, 132, -1, 1);
	printf(" SM+trg_self+src_retobj... ");
	test_vm_assertequ(801, 130, -1, -1);
	printf(" SM+trg_self+src_super... ");
	test_vm_assertequ(801, 129, -1, -1);
	printf(" SM+trg_self+src_self... ");
	test_vm_assertequ(801, 128, -1, -1);
	printf(" RET+trg_inst,1... ");
	test_vm_assertequ(801, 248, 1, -1);
	printf(" RET+trg_arg,1... ");
	test_vm_assertequ(801, 240, 1, -1);
	printf(" RET+trg_tmp,1... ");
	test_vm_assertequ(801, 232, 1, -1);
	printf(" RET+trg_lit,1... ");
	test_vm_assertequ(801, 224, 1, -1);
	printf(" RET+trg_retobj... ");
	test_vm_assertequ(801, 208, -1, -1);
	printf(" RET+trg_super... ");
	test_vm_assertequ(801, 200, -1, -1);
	printf(" RET+trg_self... ");
	test_vm_assertequ(801, 192, -1, -1);
	printf(" LD+trg_inst,1... ");
	test_vm_assertequ(801, 120, 1, -1);
	printf(" LD+trg_arg,1... ");
	test_vm_assertequ(801, 112, 1, -1);
	printf(" LD+trg_tmp,1... ");
	test_vm_assertequ(801, 104, 1, -1);
	printf(" LD+trg_lit,1... ");
	test_vm_assertequ(801, 96, 1, -1);
	printf(" LD+trg_retobj... ");
	test_vm_assertequ(801, 80, -1, -1);
	printf(" LD+trg_super... ");
	test_vm_assertequ(801, 72, -1, -1);
	printf(" LD+trg_self... ");
	test_vm_assertequ(801, 64, -1, -1);
	printf(" CALL+trg_havetrg,1... ");
	test_vm_assertequ(801, 32, 1, -1);
	printf(" CALL+trg_havetrg+src_havesrc,1,1... ");
	test_vm_assertequ(801, 36, 1, 1);
	if(getNextInstruction(801, &type, &trg_type, &src_type, &trg,&src)) puts("bytecode is successfully ended!");
	else puts("bytecode is not ended! FAILD!");

	Image[804]->dataAsLong = 0;
}

void test_vm_executeInstruction(void) {
objNum *tmps, *args, *lits, *inst;
objNum testMS = 821; // 821 - наш специально подгатовленный MethodState
struct MethodState *methodState;
struct MethodObject *method;
unsigned char type, trg_type, src_type;
long trg, src;
int result;

	// предворительно в имедже должен пресутствовать объект 6 с классом 9 и сам класс с super=9
	type = trg_type = src_type = trg = src = 0;
	puts("---- test_vm_executeInstruction ----- ");

	methodState = (struct MethodState *) &Image[821]->data;
	method = (struct MethodObject *) &Image[methodState->method]->data;
	tmps = &Image[methodState->tmps_obj]->data;
	args = &Image[methodState->args_obj]->data;
	inst = &Image[methodState->self]->data;
	lits = &Image[method->literals]->data;

	printf(" LD+trg_inst+src_inst,2,1... ");
	executeInstruction(&testMS, 64,56,7,2,1);
	if(inst[2] == inst[1]) puts("ok");
	else puts("FAILD!");
	printf(" LD+trg_inst+src_arg,2,1... ");
	executeInstruction(&testMS, 64,56,6,2,1);
	if(inst[2] == args[1]) puts("ok");
	else puts("FAILD!");
	printf(" LD+trg_inst+src_tmp,2,1... ");
	executeInstruction(&testMS, 64,56,5,2,1);
	if(inst[2] == tmps[1]) puts("ok");
	else puts("FAILD!");
	printf(" LD+trg_inst+src_lit,2,1... ");
	executeInstruction(&testMS, 64,56,4,2,1);
	if(inst[2] == lits[1]) puts("ok");
	else puts("FAILD!");
	printf(" LD+trg_inst+src_retobj,2... ");
	executeInstruction(&testMS, 64,56,2,2,0);
	if(inst[2] == methodState->returnedObj) puts("ok");
	else puts("FAILD!");
	printf(" LD+trg_inst+src_super,2... ");
	executeInstruction(&testMS, 64,56,1,2,0);
	if(inst[2] == ((struct ClassObject *) &Image[method->InTheClass]->data)->super) puts("ok");
	else puts("FAILD!");
	printf(" LD+trg_inst+src_self,2... ");
	executeInstruction(&testMS, 64,56,0,2,0);
	if(inst[2] == methodState->self) puts("ok");
	else puts("FAILD!");


	printf(" LD+trg_arg+src_inst,2,1... ");
	executeInstruction(&testMS, 64,48,7,2,1);
	if(args[2] == inst[1]) puts("ok");
	else puts("FAILD!");
	printf(" LD+trg_arg+src_arg,2,1... ");
	executeInstruction(&testMS, 64,48,6,2,1);
	if(args[2] == args[1]) puts("ok");
	else puts("FAILD!");
	printf(" LD+trg_arg+src_tmp,2,1... ");
	executeInstruction(&testMS, 64,48,5,2,1);
	if(args[2] == tmps[1]) puts("ok");
	else puts("FAILD!");
	printf(" LD+trg_arg+src_lit,2,1... ");
	executeInstruction(&testMS, 64,48,4,2,1);
	if(args[2] == lits[1]) puts("ok");
	else puts("FAILD!");
	printf(" LD+trg_arg+src_retobj,2... ");
	executeInstruction(&testMS, 64,48,2,2,0);
	if(args[2] == methodState->returnedObj) puts("ok");
	else puts("FAILD!");
	printf(" LD+trg_arg+src_super,2... ");
	executeInstruction(&testMS, 64,48,1,2,0);
	if(args[2] == ((struct ClassObject *) &Image[method->InTheClass]->data)->super) puts("ok");
	else puts("FAILD!");
	printf(" LD+trg_arg+src_self,2... ");
	executeInstruction(&testMS, 64,48,0,2,0);
	if(args[2] == methodState->self) puts("ok");
	else puts("FAILD!");

	printf(" LD+trg_tmp+src_inst,2,1... ");
	executeInstruction(&testMS, 64,40,7,2,1);
	if(tmps[2] == inst[1]) puts("ok");
	else puts("FAILD!");
	printf(" LD+trg_tmp+src_arg,2,1... ");
	executeInstruction(&testMS, 64,40,6,2,1);
	if(tmps[2] == args[1]) puts("ok");
	else puts("FAILD!");
	printf(" LD+trg_tmp+src_tmp,2,1... ");
	executeInstruction(&testMS, 64,40,5,2,1);
	if(tmps[2] == tmps[1]) puts("ok");
	else puts("FAILD!");
	printf(" LD+trg_tmp+src_lit,1,1... ");
	executeInstruction(&testMS, 64,40,4,2,1);
	if(tmps[2] == lits[1]) puts("ok");
	else puts("FAILD!");
	printf(" LD+trg_tmp+src_retobj,1... ");
	executeInstruction(&testMS, 64,40,2,2,0);
	if(tmps[2] == methodState->returnedObj) puts("ok");
	else puts("FAILD!");
	printf(" LD+trg_tmp+src_super,1... ");
	executeInstruction(&testMS, 64,40,1,2,0);
	if(tmps[2] == ((struct ClassObject *) &Image[method->InTheClass]->data)->super) puts("ok");
	else puts("FAILD!");
	printf(" LD+trg_tmp+src_self,1... ");
	executeInstruction(&testMS, 64,40,0,2,0);
	if(tmps[2] == methodState->self) puts("ok");
	else puts("FAILD!");

	printf(" LD+trg_retobj+src_inst,1... ");
	executeInstruction(&testMS, 64,16,7,0,1);
	if(methodState->returnedObj == inst[1]) puts("ok");
	else puts("FAILD!");
	printf(" LD+trg_retobj+src_arg,1... ");
	executeInstruction(&testMS, 64,16,6,0,1);
	if(methodState->returnedObj == args[1]) puts("ok");
	else puts("FAILD!");
	printf(" LD+trg_retobj+src_tmp,1... ");
	executeInstruction(&testMS, 64,16,5,0,1);
	if(methodState->returnedObj == tmps[1]) puts("ok");
	else puts("FAILD!");
	printf(" LD+trg_retobj+src_lit,1... ");
	executeInstruction(&testMS, 64,16,4,0,1);
	if(methodState->returnedObj == lits[1]) puts("ok");
	else puts("FAILD!");
	printf(" LD+trg_retobj+src_retobj... ");
	executeInstruction(&testMS, 64,16,2,0,0);
	if(methodState->returnedObj == lits[1]) puts("ok");
	else puts("FAILD!");
	printf(" LD+trg_retobj+src_super... ");
	executeInstruction(&testMS, 64,16,1,0,0);
	if(methodState->returnedObj == ((struct ClassObject *) &Image[method->InTheClass]->data)->super) puts("ok");
	else puts("FAILD!");
	printf(" LD+trg_retobj+src_self... ");
	executeInstruction(&testMS, 64,16,0,0,0);
	if(methodState->returnedObj == methodState->self) puts("ok");
	else puts("FAILD!");

	printf(" LD+trg_self+src_inst,1... ");
	executeInstruction(&testMS, 64,0,7,0,1);
	if(methodState->self == inst[1]) puts("ok");
	else puts("FAILD!");
	printf(" LD+trg_self+src_arg,1... ");
	executeInstruction(&testMS, 64,0,6,0,1);
	if(methodState->self == args[1]) puts("ok");
	else puts("FAILD!");
	printf(" LD+trg_self+src_tmp,1... ");
	executeInstruction(&testMS, 64,0,5,0,1);
	if(methodState->self == tmps[1]) puts("ok");
	else puts("FAILD!");
	printf(" LD+trg_self+src_lit,1... ");
	executeInstruction(&testMS, 64,0,4,0,1);
	if(methodState->self == lits[1]) puts("ok");
	else puts("FAILD!");
	printf(" LD+trg_self+src_retobj... ");
	executeInstruction(&testMS, 64,0,2,0,0);
	if(methodState->self == methodState->returnedObj) puts("ok");
	else puts("FAILD!");
	printf(" LD+trg_self+src_super... ");
	executeInstruction(&testMS, 64,0,1,0,0);
	if(methodState->self == ((struct ClassObject *) &Image[method->InTheClass]->data)->super) puts("ok");
	else puts("FAILD!");
//	printf(" LD+trg_self+src_self... ");
/*
	hookReturn = 1;
	puts(" ^inst[1] = 90... ");
	vmContext->inst_data[1] = 90;
	executeInstruction(&testMS, 192,56,0,1,0);
	if(vmContext->returnedObj == 90) puts("ok");
	else puts("FAILD!");
	puts(" ^args[1] = 91 ... ");
	args[1] = 91;
	executeInstruction(&testMS, 192,48,0,1,0);
	if(vmContext->returnedObj == 91) puts("ok");
	else puts("FAILD!");
	puts(" ^tmps[1] = 92 ... ");
	vmContext->tmps_data[1] = 92;
	executeInstruction(&testMS, 192,40,0,1,0);
	if(vmContext->returnedObj == 92) puts("ok");
	else puts("FAILD!");
	puts(" ^lits[1] = 93 ... ");
	vmContext->lits_data[1] = 93;
	executeInstruction(&testMS, 192,32,0,1,0);
	if(vmContext->returnedObj == 93) puts("ok");
	else puts("FAILD!");
	puts(" ^returnedObj = 94 ... ");
	vmContext->returnedObj = 94;
	executeInstruction(&testMS, 192,16,0,0,0);
	if(vmContext->returnedObj == 94) puts("ok");
	else puts("FAILD!");
	puts(" ^super = 95 ... ");
	vmContext->super = 95;
	executeInstruction(&testMS, 192,8,0,0,0);
	if(vmContext->returnedObj == 95) puts("ok");
	else puts("FAILD!");
	puts(" ^self = 96 ... ");
	vmContext->self = 96;
	executeInstruction(&testMS, 192,0,0,0,0);
	if(vmContext->returnedObj == 96) puts("ok");
	else puts("FAILD!");

	hookReturn = 0;
*/
/*
	hookEnter = 1;
	hookEnter_self = hookEnter_methodobj = 0;
	hookEnter_Offset = hookEnter_isBlock = 1;

	puts(" SM test1method3 -> inst[1]=obj(73) ... ");
	vmContext->inst_data[1] = 73;   // self=obj(73)
	vmContext->args_data[0] = 7030; // obj(7030)='test1method3'
	executeInstruction(&testMS, 64,56,0,1,0);
	if(hookEnter_self == 73)
	 if(hookEnter_methodobj == 3)
	  if(hookEnter_Offset == 0)
	   if(hookEnter_isBlock == 0) puts("ok");
	   else puts("FAILD (isBlock != 0)");
	  else puts("FAILD (Offset != 0)");
	 else puts("FAILD (methodobj != 3)");
	else puts("FAILD (self != 73)");


	puts(" SM test1method2 -> args[1]=obj(73) ... ");
	vmContext->args_data[1] = 73;   // self=obj(73)
	vmContext->args_data[0] = 7020; // obj(7020)='test1method2'
	hookEnter_Offset = hookEnter_isBlock = 1;
	executeInstruction(&testMS, 64,48,0,1,0);
	if(hookEnter_self == 73)
	 if(hookEnter_methodobj == 2)
	  if(hookEnter_Offset == 0)
	   if(hookEnter_isBlock == 0) puts("ok");
	   else puts("FAILD (isBlock != 0)");
	  else puts("FAILD (Offset != 0)");
	 else puts("FAILD (methodobj != 2)");
	else puts("FAILD (self != 73)");

	puts(" SM test1method1 -> tmp[1]=(73) ... ");
	vmContext->tmps_data[1] = 73;   // self=obj(73)
	vmContext->args_data[0] = 7010; // obj(7010)='test1method1'
	hookEnter_Offset = hookEnter_isBlock = 1;
	executeInstruction(&testMS, 64,40,0,1,0);
	if(hookEnter_self == 73)
	 if(hookEnter_methodobj == 1)
	  if(hookEnter_Offset == 0)
	   if(hookEnter_isBlock == 0) puts("ok");
	   else puts("FAILD (isBlock != 0)");
	  else puts("FAILD (Offset != 0)");
	 else puts("FAILD (methodobj != 1)");
	else puts("FAILD (self != 73)");

	puts(" SM test1method4 -> lits[1]=obj(73) ... ");
	vmContext->lits_data[1] = 73;   // self=obj(73)
	vmContext->args_data[0] = 7040; // obj(7040)='test1method4'
	hookEnter_Offset = hookEnter_isBlock = 1;
	executeInstruction(&testMS, 64,32,0,1,0);
	if(hookEnter_self == 73)
	 if(hookEnter_methodobj == 4)
	  if(hookEnter_Offset == 0)
	   if(hookEnter_isBlock == 0) puts("ok");
	   else puts("FAILD (isBlock != 0)");
	  else puts("FAILD (Offset != 0)");
	 else puts("FAILD (methodobj != 4)");
	else puts("FAILD (self != 73)");

	puts(" SM test_method5 -> returnedObj=obj(73) ... ");
	vmContext->returnedObj = 73;   // self=obj(73)
	vmContext->args_data[0] = 7050; // obj(7060)='test_method6'
	hookEnter_Offset = hookEnter_isBlock = 1;
	executeInstruction(&testMS, 64,16,0,0,0);
	if(hookEnter_self == 73)
	 if(hookEnter_methodobj == 50)
	  if(hookEnter_Offset == 0)
	   if(hookEnter_isBlock == 0) puts("ok");
	   else puts("FAILD (isBlock != 0)");
	  else puts("FAILD (Offset != 0)");
	 else puts("FAILD (methodobj != 50)");
	else puts("FAILD (self != 73)");

	puts(" SM test2method1 -> super=obj(73) ... ");
	vmContext->super = 73;   // self=obj(73)
	vmContext->args_data[0] = 7110; // obj(7110)='test2method1'
	hookEnter_Offset = hookEnter_isBlock = 1;
	executeInstruction(&testMS, 64,8,0,0,0);
	if(hookEnter_self == 73)
	 if(hookEnter_methodobj == 10)
	  if(hookEnter_Offset == 0)
	   if(hookEnter_isBlock == 0) puts("ok");
	   else puts("FAILD (isBlock != 0)");
	  else puts("FAILD (Offset != 0)");
	 else puts("FAILD (methodobj != 10)");
	else puts("FAILD (self != 73)");

	puts(" SM test2method2 -> self=obj(73) ... ");
	vmContext->self = 73;   // self=obj(73)
	vmContext->args_data[0] = 7120; // obj(7120)='test2method2'
	hookEnter_Offset = hookEnter_isBlock = 1;
	executeInstruction(&testMS, 64,0,0,0,0);
	if(hookEnter_self == 73)
	 if(hookEnter_methodobj == 20)
	  if(hookEnter_Offset == 0)
	   if(hookEnter_isBlock == 0) puts("ok");
	   else puts("FAILD (isBlock != 0)");
	  else puts("FAILD (Offset != 0)");
	 else puts("FAILD (methodobj != 20)");
	else puts("FAILD (self != 73)");

	hookEnter = 0;
*/
/*	hookCall = 1;
	hookCall_primitiveNumber = 0;

	puts(" <primitive: 1> ... ");
	executeInstruction(&testMS, 0,32,0,1,0);
	if(hookCall_primitiveNumber == 1)
	 if(1) puts("ok");
	 else puts("FAILD (unknown context)");
	else puts("FAILD (primitiveNumber != 1)");
	puts(" CALL+trg_havetrg+src_havesrc,1,1... ");
	test_vm_assertequ(36,1,1);

	hookCall = 0;*/
}

void test_vm_SearchingForMethod(void) {
	puts("---- test_vm_executeInstruction ----- ");
	printf(" SearchingForMethod [in stright class]: obj(80)='test3method2' self=400... ");
	if(SearchingForMethod(400, 80) == 200) puts("ok");
	else puts("FAILD!");
	printf(" SearchingForMethod [in super class]: obj(81)='test2method4' self=400... ");
	if(SearchingForMethod(400, 81) == 500) puts("ok");
	else puts("FAILD!");
	printf(" SearchingForMethod [in root class]: obj(82)='test1method3' self=400... ");
	if(SearchingForMethod(400, 82) == 3) puts("ok");
	else puts("FAILD!");
	printf(" SearchingForMethod [never]: obj(83)='test4method1' self=400... ");
	if(SearchingForMethod(300, 83) == 0) puts("ok");
	else puts("FAILD!");
	printf(" SearchingForMethod : obj(84)='test_method5' self=200... ");
	if(SearchingForMethod(100, 84) == 5) puts("ok");
	else puts("FAILD!");
	printf(" SearchingForMethod : obj(84)='test_method5' self=400... ");
	if(SearchingForMethod(400, 84) == 50) puts("ok");
	else puts("FAILD!");
	printf(" SearchingForMethod : obj(85)='\\' self=400... ");
	if(SearchingForMethod(400, 85) == 6) puts("ok");
	else puts("FAILD!");

}

void test_vm_returnInPreviousMethod() {

	puts("---- test_vm_returnInPreviousMethod ----- ");
	puts(" NOT IMPLEMENT ");
}

int test_prim126() {
objNum testMS = 701;
struct MethodState *methodState;
objNum savedNilObject;
	
	puts("---- test primitive 126 ---- ");
	methodState = (struct MethodState *) &Image[testMS]->data;
	(&Image[methodState->args_obj]->data)[0] = 102; // CompactDictionary instance
	(&Image[methodState->args_obj]->data)[1] = 82;  // #test1method3
	(&Image[methodState->args_obj]->data)[2] = 999; // objIfFaild - if not found
	internalCall(126, &testMS);
	if(methodState->returnedObj == 3) puts("test1method3 found ... ok!");
	else if(methodState->returnedObj == 999) puts("test1method3 not found ... FAILD! (nil returned)");
	     else puts("test1method3 not found ... FAILD!");
	methodState->returnedObj = 0;
	(&Image[methodState->args_obj]->data)[0] = 102;
	(&Image[methodState->args_obj]->data)[1] = 81;
	internalCall(126, &testMS);
	if(methodState->returnedObj == 999) puts("test2method4 not found ... ok!");
	else puts("test2method4 ... FAILD!");
	return 0;
}

void test_VmC(void) {
obj **savedImage = 0;
unsigned long savedImageTop = 0;

    puts(" ###  Testing <vm.c> ### \n");
    savedImage = Image;
    savedImageTop = ImageTop;
    ImageTop = newImageLength;
    Image = initTestImage();

    //getNextInstruction использует из Context: bytecode, bytecodeOffset, maximumBytecodeOffset
    test_vm_getNextInstruction();
    test_vm_executeInstruction();
    test_vm_SearchingForMethod();
//    test_vm_returnInPreviousMethod();
    ImageTop = newImageLength;
    Image = initTestImage();
    test_prim126();
    ImageTop = newImageLength;
    Image = initTestImage();
    test_vm_SMnRET1();
    ImageTop = newImageLength;
    Image = initTestImage();
    test_vm_SMnRET2();
    ImageTop = newImageLength;
    Image = initTestImage();
    test_vm_SMnRET3();
    ImageTop = newImageLength;
    Image = initTestImage();
    test_vm_SMnRET4();
    ImageTop = newImageLength;
    Image = initTestImage();
    test_vm_BlockTmps();
    ImageTop = newImageLength;
    Image = initTestImage();
    test_vm_BlockTmps2();

    // ...
    // проверяем умение continueContext подготавливать контекст
    // ...

    ImageTop = savedImageTop;
    Image = savedImage;
    puts(" ###  End Testing <vm.c> ### \n");

}

/* ------------------------------------ END Vm.c -------------------------------------*/

