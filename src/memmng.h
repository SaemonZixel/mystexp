/***************************************************************************
 *   Copyright (C) 2006 by Saemon Zixel                                    *
 *   saemon@pochta.ru                                                      *
 *                                                                         *
 ***************************************************************************/

#include "types.h"

#define obj_node 1<<31

extern void initMemMng(void);
extern obj* getEmptyObj(unsigned long size);
extern void returnDirtyObj(obj* object);
extern void notNeededObj(objNum num);
extern void resizeObj(objNum dirtyObj, unsigned long size);
//extern obj* resizeObjAndZeroedEnd(obj* dirtyObj, unsigned long size);
extern objNum newObj(objNum class, unsigned long size, unsigned long formemmng);
extern objNum newObjWithData(objNum class, unsigned long size, unsigned long formemmng, unsigned long datasize, char* data);
