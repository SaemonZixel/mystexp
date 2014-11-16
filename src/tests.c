/***************************************************************************
 *   Copyright (C) 2006 by Saemon Zixel                                    *
 *   saemon@pochta.ru                                                      *
 *                                                                         *
 ***************************************************************************/

#include "vm.h"
#include "memmng.h"
#include "imagemng.h"

int hookNI = 0; // отключить хук
int hookNotNeed = 0;
 objNum hookNotNeed_num1, hookNotNeed_num2;
int hookcontinueContextExit;
 int hookcontinueContextExit_code;

void primitiveZero(objNum testClass, objNum methodSateObj) {
objNum tests, currentTest;

    tests = ((struct ClassObject *) &Image[Image[testClass]->class]->data)->methods;
    (&Image[testClass]->data)[3] = methodSateObj;  // первая переменная класса зарезервированна, специально чтоб GC неудалил сахранёный контекст контекст
    puts("Start testing ...\n");
 //   test_memmng_newObj();
 //   test_memmng_resizeObj();
    puts("Start testing VM...");
    test_VmC();
    test_basest(testClass, methodSateObj);

//    initMemMng();
//    test_primitiveZeroEnable; // возможно ли тестирование
//    test_MemMngC(1);
//    test_ImageMngC();

     puts("\n... End testing");
     (&Image[testClass]->data)[3] = 0;
}

int notNeededObjHook(objNum num) {
	if(hookNotNeed) {
	  if(hookNotNeed_num1 == 0) hookNotNeed_num1 = num;
	  else hookNotNeed_num2 = num;
	}
	return hookNotNeed;
}

int continueContextExitHook(int code) {
	if(hookcontinueContextExit) {
	 hookcontinueContextExit_code = code;
//	 hookcontinueContextExit_vmContext = vmContext;
	}
	return code;
}

