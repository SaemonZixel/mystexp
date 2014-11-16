/***************************************************************************
 *   Copyright (C) 2006 by Saemon Zixel                                    *
 *   saemon@pochta.ru                                                      *
 *                                                                         *
 ***************************************************************************/

#ifndef TESTS_H
#define TESTS_H

#include "test_basest.h"

extern void primitiveZero(objNum testClass, objNum methodSateObj);
extern int internalCallHook(int primitiveNumber, objNum methodSateObj);
extern int notNeededObjHook(objNum num);
extern int continueContextExitHook(int code);

#endif
