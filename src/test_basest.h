/***************************************************************************
 *   Copyright (C) 2006 by Saemon Zixel                                    *
 *   saemon@pochta.ru                                                      *
 *                                                                         *
 ***************************************************************************/

extern void test_basest(objNum testClass, objNum methodSateObj);

// функции для тестирования externalCall механизма
extern void testInt(int intVar);
extern void testDouble(short doubleVar);
extern void testPointer(void *voidPtr);
extern void test2args(char charVar, int intVar);
extern void test3args(char charVar1, char charVar2, double doubleVar);
extern char testRetChar(void);
extern int testRetInt(void);
extern double testRetDouble(void);
extern int* testRetPointer(void);
