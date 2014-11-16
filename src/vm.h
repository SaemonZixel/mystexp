/***************************************************************************
 *   Copyright (C) 2006 by Saemon Zixel                                    *
 *   saemon@pochta.ru                                                      *
 *                                                                         *
 ***************************************************************************/

#include "types.h"

extern int getNextInstruction(objNum methodStateObj, unsigned char* type, char* trg_type, char* src_type, long* trg, long* src);
extern int returnInPreviousMethod(objNum *methodStateObj, int isMethodReturn);
extern void enterInBlock(objNum *methodStateObj, objNum targetBlock);
extern void enterInMethod(objNum *methodStateObj, objNum targetMethod, objNum self);
extern objNum SearchingForMethod(objNum TargetClass, objNum SymbolObj);
extern int executeInstruction(objNum *methodStateObj, unsigned char type, char trg_type, char src_type, long trg, long src);
extern int continueContext(objNum methodState);
extern int doMethod(objNum Method, objNum self, objNum *retObj);
extern int doBlock(objNum Block, objNum *retObj);
