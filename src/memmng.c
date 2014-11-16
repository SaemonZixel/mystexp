/***************************************************************************
 *   Copyright (C) 2006 by Saemon Zixel                                    *
 *   saemon@pochta.ru                                                      *
 *                                                                         *
 ***************************************************************************/
#include <stdlib.h>
#include "types.h"
#include "imagemng.h"

obj* getEmptyObj(unsigned long size){
    return (obj*) malloc(size);
}

void returnDirtyObj(obj *object){
     free(object);
}

void notNeededObj(objNum num){ // (перевод: ненужен объект) вызывается когда объект перестаёт использоватся где-либо
#ifdef primZero
    if(notNeededObjHook(num)) return;
#endif

#ifdef debug
    printf(" Returned object: %i size: %i\n", num, Image[num]->size);
#endif
	returnDirtyObj(Image[num]);
	Image[num] = NULL;
}

obj* resizeObjAndZeroedEnd(obj *dirtyObj, unsigned long size){ // (перев: изменить размер и обнулить конец (прим. если размер увеличивается))
obj *result;
unsigned long i, minsize, fullsize;

	if(dirtyObj->flags & bitNotMoveableObj){
#ifdef debug
	printf(" memmng.c: resizeObjAndZeroedEnd: We can`t resize not moveable object (size: %i)\n", dirtyObj->size);
#endif
	 return 0;
	}
	fullsize = sizeof(obj) - sizeof(objNum) + size; // размер malloc выделяемой памяти куда будет памещён загаловок и данные
	result = getEmptyObj(fullsize);

	if(dirtyObj->size > size) minsize = fullsize; //  уменьшаем объект
	else minsize = sizeof(obj) - sizeof(objNum) + dirtyObj->size; // увеличиваем объект

	for(i=0; i < minsize; i++){
	  ((char *) result)[i] = ((char *) dirtyObj)[i];
	}

	for(i=minsize; i< fullsize; i++){
	  ((char *) result)[i]= 0;
	}

	returnDirtyObj(dirtyObj);
	result->size = size;
	return result;
}

int resizeObj(objNum targetObj, unsigned long size) {
	Image[targetObj] = resizeObjAndZeroedEnd(Image[targetObj], size);
	return 0;
}

objNum newObj(objNum class, unsigned long size, unsigned long flags){ // (перев: новый объект)
// если вызванно как newObj(... , ... , 1) - то будет создан объект в котором внутри находятся объекты (номера объектов)
// если вызванно как newObj(... , ... , 0) - то будет создан объект с "сырыми" данными
obj* resultObj;
objNum result;
unsigned long i;
int ImageCanBeFull = 0; //

	// ищем свободный номер объекта в Image
	while( Image[ImageTop] != NULL ){
	  if(ImageLimit <= ImageTop + 1) {
	    // если второй раз начинаем просматриваем весь Image, то Image полон...
	    if(ImageCanBeFull == 1) {
#ifdef debug
		puts("newObj: Cann`t create new object, ImageLimit reach!");
#endif
		return 0;
	    } else {
		ImageTop = 0;
		ImageCanBeFull = 1;
	    }
	  }
	  ImageTop++;
	}

	resultObj = getEmptyObj(sizeof(obj) - 4 + size);
	if(resultObj == 0){
#ifdef debug
	 puts("newObj: Error!");
#endif
	 return -1;
	}
	resultObj->class = class;
	resultObj->size = size;
	resultObj->flags = flags;
	for(i = 0; i < size; i++) ((char *) &resultObj->data)[i] = 0;
	result = ImageTop;
	Image[result] = resultObj;
	return result;
}

objNum newObjWithData(objNum class, unsigned long size, unsigned long flags, unsigned long datasize, char *data){
obj *resultObj;
objNum result;
unsigned long i;
int ImageCanBeFull = 0; //

	// ищем свободный номер объекта в Image
	while( Image[ImageTop] != NULL ){
	  if(ImageLimit <= ImageTop + 1) {
	    // если второй раз начинаем просматриваем весь Image, то Image полон...
	    if(ImageCanBeFull == 1) {
#ifdef debug
		puts("newObj: Cann`t create new object, ImageLimit reach!");
#endif
		return 0;
	    } else {
		ImageTop = 0;
		ImageCanBeFull = 1;
	    }
	  }
	  ImageTop++;
	}

	resultObj = getEmptyObj(sizeof(obj) - 4 + size);
	if(resultObj == 0){
#ifdef debug
	 puts("newObjWithData: Error!");
#endif
	 return -1;
	}
	resultObj->class = class;
	resultObj->size = size;
	resultObj->flags = flags;
	if(size > datasize){
	 for(i = 0; i < datasize; i++){
	  (&resultObj->dataAsChar)[i] = data[i];
	 }
	}else{
	 for(i=0; i < size; i++){
	  (&resultObj->dataAsChar)[i] = data[i];
	 }
	}
	result = ImageTop;
	Image[result] = resultObj;
	return result;
}

// ################################# Simple Garbage Collector #################################

unsigned long sweepCount; // количество высвобожденных объектов

void GC_unmarkAll(void) {
objNum i;

	for(i = 0; i < ImageLimit; i++)
	  if(Image[i] != NULL)
	   Image[i]->flags = Image[i]->flags & 0xfffffffdl;
	  // if(Image[i]->flags & 2) Image[i]->flags = Image[i]->flags ^ 2;

}

int GC_mark(objNum Root) {
unsigned long i;
	// если объект уже помечен то нам делать нечего... выходим
	if(Image[Root]->flags & 2) return 0;
	// сразу пометим его
	Image[Root]->flags = Image[Root]->flags | 2;
	GC_mark(Image[Root]->class);
	if(Image[Root]->flags & 1){ //если первый бит ненулевой то объект cодержит внутри себя номера объектов
	 if(Image[Root]->size != 0) // если размер не нулевой то они есть и их надо паметить...
	   for(i = 0; i < Image[Root]->size / sizeof(objNum); i++){
	     GC_mark((&Image[Root]->data)[i]);
	   }
	}
	// всё прошло успешно
	return 0;
}

void GC_sweep(void) {
objNum i;

	for(i = 1; i < ImageLimit; i++)
	  if(Image[i] != NULL)
	    // все кто 0 и 1 небыли помечены и поэтому ненужны
	    if((Image[i]->flags & 2) == 0){
	      notNeededObj(i);
	      sweepCount++;
	    }
}

int GC_markAndSweep(objNum startObject) {
//objNum i;

	sweepCount = 0;
#ifdef debug
	puts("GC Starting...");
	printf("Objects in image: %i\n",ImageSize(0));
	puts("  unmarkAll start...");
#endif

	// уберём все маркировки если таковые есть
	GC_unmarkAll();

#ifdef debug
	puts("  ...end");
	puts("  mark start...");
#endif
	// промаркируем объекти которые попадают в дерево образуемым корнем startObject
	GC_mark(startObject);

#ifdef debug
	puts("  ...end");
	puts("  sweep start...");
#endif
	// теперь спокойно уничтожаем непромаркированные (т.е. не попавшие в дерево) объекты
	GC_sweep();

#ifdef debug
	puts("  ...end");
	puts("...GC End");
	printf("sweeped %i objects\n",sweepCount);
	printf("Objects in image: %i\n",ImageSize(0));
#endif

	// чтоб удобнее было делать diff разкоментировать
	//GC_unmarkAll();

	return 0;
}
