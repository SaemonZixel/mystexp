/***************************************************************************
 *   Copyright (C) 2006 by Saemon Zixel                                    *
 *   saemon@pochta.ru                                                      *
 *                                                                         *
 ***************************************************************************/

#include "memmng.h"
#include "imagemng.h"

/* ------------------------- MemMng.c --------------------------------------*/

void retObjects(obj **objs, unsigned long count, int silent) {
    unsigned long i;

    if(!silent)
        puts("Returnig used objects ...\n");
    for(i = 0; i < count; i++) {
        returnDirtyObj(objs[i]);
        if(!silent)
            printf("returned %li object\n",i);
    }
    if(!silent)
        puts("All objects was successfully returned! \n");
}

void retNNObjects(objNum *objs, unsigned long count, int silent) {
    unsigned long i;

    if(!silent)
        puts("Returnig not needed objects ...\n");
    for(i = 0; i < count; i++) {
        notNeededObj(objs[i]);
        if(!silent)
            printf("returned %li object\n",i);
    }
    if(!silent)
        puts("All objects was successfully returned! \n");
}

void test_memmng_getEmptyObj(void) {
    obj *tmpobj[8];

    puts("----- test_memmng_getEmptyObj -----");

    tmpobj[0] = getEmptyObj(4);
    if(tmpobj[0] != 0) {
        tmpobj[0]->size = 4;
        puts("getEmptyObj(4)... ok!");
    } else
        puts("getEmptyObj(4)... FAILD!");

    tmpobj[1] = getEmptyObj(1);
    if(tmpobj[1] != 0) {
        tmpobj[1]->size = 1;
        puts("getEmptyObj(1)... ok!");
    } else
        puts("getEmptyObj(1)... FAILD!");

    tmpobj[2] = getEmptyObj(0);
    if(tmpobj[2] != 0) {
        tmpobj[2]->size = 0;
        puts("getEmptyObj(0)... ok!");
    } else
        puts("getEmptyObj(0)... FAILD!");

    tmpobj[3] = getEmptyObj(100);
    if(tmpobj[3] != 0) {
        tmpobj[3]->size = 100;
            puts("getEmptyObj(100)... ok!");
        } else
            puts("getEmptyObj(100)... FAILD!");

    tmpobj[4] = getEmptyObj(64*1024);
    if(tmpobj[4] != 0) {
        tmpobj[4]->size = 65536;
        puts("getEmptyObj(64k)... ok!");
    } else
        puts("getEmptyObj(64k)... FAILD!");

    tmpobj[5] = getEmptyObj(65537);
    if(tmpobj[5] != 0) {
        tmpobj[5]->size = 65537;
        puts("getEmptyObj(64k+1)... ok!");
    } else
        puts("getEmptyObj(64k+1)... FAILD!");

    tmpobj[6] = getEmptyObj(32*1024*1024);
    if(tmpobj[6] != 0) {
        tmpobj[6]->size = (32*1024*1024);
        puts("getEmptyObj(32M)... ok!");
    } else
        puts("getEmptyObj(32M)... FAILD!");

    tmpobj[7] = getEmptyObj(32*1024*1024+1);
    if(tmpobj[7] != 0) {
        tmpobj[7]->size = (32*1024*1024+1);
        puts("getEmptyObj(32M+1)... ok!");
    } else puts("getEmptyObj(32M+1)... FAILD!");

    retObjects(tmpobj,8,0);

}

void dyrting(objNum item) {
unsigned long i;
	for(i = 0; i < Image[item]->size; i++) ((char *) &Image[item]->data)[i] = i;
}

int CheckOne(objNum item, unsigned long size) {
int c;

	for(c = 0; c < size; c++)
	  if(((char *) &Image[item]->data)[c] != (char) c) return c;
	return -1;
}

void test_memmng_resizeObj(void) {
    objNum tmpobj;

    puts("----- test_memmng_resizeObj start... ");

    tmpobj = newObj(0,1,0);
    if((signed)tmpobj == -1)
        puts("newObj(1) ... FAILD!");
    else {
    	dyrting(tmpobj);
        if(Image[tmpobj]->size == 1)
            puts("newObj(1) ... ok");
        else
            puts("newObj(1) ... FAILD");

        resizeObj(tmpobj,2);
	if(CheckOne(tmpobj,1) != -1) puts("Internal data damaged!");
	dyrting(tmpobj);
        if(Image[tmpobj]->size == 2)
            puts("resize 1 -> 2 ... ok");
        else
            puts("resize 1 -> 2 ... FAILD");

        resizeObj(tmpobj,4);
	if(CheckOne(tmpobj,2) != -1) puts("Internal data damaged!");
	dyrting(tmpobj);
	if(Image[tmpobj]->size == 4)
            puts("resize 2 -> 4 ... ok");
        else
            puts("resize 2 -> 4 ... FAILD");

        resizeObj(tmpobj,5);
	if(CheckOne(tmpobj,4) != -1) puts("Internal data damaged!");
	dyrting(tmpobj);
        if(Image[tmpobj]->size == 5)
            puts("resize 4 -> 5 ... ok");
        else
            puts("resize 4 -> 5 ... FAILD");

        resizeObj(tmpobj,100);
	if(CheckOne(tmpobj,5) != -1) puts("Internal data damaged!");
	dyrting(tmpobj);
        if(Image[tmpobj]->size == 100)
            puts("resize 5 -> 100 ... ok");
        else
            puts("resize 5 -> 100 ... FAILD");

        resizeObj(tmpobj,65536);
	if(CheckOne(tmpobj,100) != -1) puts("Internal data damaged!");
	dyrting(tmpobj);
        if(Image[tmpobj]->size == 65536)
            puts("resize 100 -> 64k ... ok");
        else
            puts("resize 100 -> 64k ... FAILD");

        resizeObj(tmpobj,65537);
	if(CheckOne(tmpobj,65536) != -1) puts("Internal data damaged!");
	dyrting(tmpobj);
        if(Image[tmpobj]->size == 65537)
            puts("resize 64k -> 64k+1 ... ok");
        else
            puts("resize 64k -> 64k+1 ... FAILD");

        resizeObj(tmpobj,32*1024*1024);
	if(CheckOne(tmpobj,65537) != -1) puts("Internal data damaged!");
	dyrting(tmpobj);
        if(Image[tmpobj]->size == 32*1024*1024)
            puts("resize 64k+1 -> 32M ... ok");
        else
            puts("resize 64k+1 -> 32M ... FAILD");

        resizeObj(tmpobj,32*1024*1024+1);
	if(CheckOne(tmpobj,32*1024*1024) != -1) puts("Internal data damaged!");
	dyrting(tmpobj);
        if(Image[tmpobj]->size == 32*1024*1024+1)
            puts("resize 32M -> 32M+1 ... ok");
        else
            puts("resize 32M -> 32M+1 ... FAILD");

        resizeObj(tmpobj,8*1024*1024);
	if(CheckOne(tmpobj,8*1024*1024) != -1) puts("Internal data damaged!");
	dyrting(tmpobj);
        if(Image[tmpobj]->size == 8*1024*1024)
            puts("resize 32M+1 -> 8M ... ok");
        else
            puts("resize 32M+1 -> 8M ... FAILD");

        resizeObj(tmpobj,8*1024);
	if(CheckOne(tmpobj,8*1024) != -1) puts("Internal data damaged!");
	dyrting(tmpobj);
        if(Image[tmpobj]->size == 8*1024)
            puts("resize 8M -> 8k ... ok");
        else
            puts("resize 8M -> 8k ... FAILD");

	resizeObj(tmpobj,128);
	if(CheckOne(tmpobj,128) != -1) puts("Internal data damaged!");
	dyrting(tmpobj);
        if(Image[tmpobj]->size == 128)
            puts("resize 8k -> 128 ... ok");
        else
            puts("resize 8k -> 128 ... FAILD");

        resizeObj(tmpobj,128);
	if(CheckOne(tmpobj,128) != -1) puts("Internal data damaged!");
	dyrting(tmpobj);
        if(Image[tmpobj]->size == 128)
            puts("resize 128 -> 128 ... ok");
        else
            puts("resize 128 -> 128 ... FAILD");

        resizeObj(tmpobj,1);
	if(CheckOne(tmpobj,1) != -1) puts("Internal data damaged!");
	dyrting(tmpobj);
        if(Image[tmpobj]->size == 1)
            puts("resize 128 -> 1 ... ok");
        else
            puts("resize 128 -> 1 ... FAILD");

        resizeObj(tmpobj,0);
        if(Image[tmpobj]->size == 0)
            puts("resize 1 -> 0 ... ok");
        else
            puts("resize 1 -> 0 ... FAILD");
        notNeededObj(tmpobj);
    }
    puts(" ... test_memmng_resizeObj end ----- ");
}

int CheckWholeness(objNum *items, int count) {
int i, c;

	for(i = 0; i<count; i++)
	  for(c = 0; c < Image[items[i]]->size; c++)
	    if(((char *) &Image[items[i]]->data)[c] != c) return i;
	return -1;
}

void test_memmng_newObj(void) {
    objNum tmpobj[3];

    puts("----- test_memmng_newObj -----");

    puts(" Creating object (class=0, size=1, flags=0)... ");
    tmpobj[0] = newObj(0,1,0);
    dyrting(tmpobj[0]);
    if((Image[tmpobj[0]]->size == 1) && (Image[tmpobj[0]]->class == 0) && (Image[tmpobj[0]]->flags == 0))
        puts("ok!\n");
    else
        puts("FAILD!\n");

    puts(" Creating object (class=0, size=5, flags=0)... ");
    tmpobj[1] = newObj(0,5,0);
    dyrting(tmpobj[1]);
    if((Image[tmpobj[1]]->size == 5) && (Image[tmpobj[1]]->class == 0) && (Image[tmpobj[1]]->flags == 0))
        puts("ok!\n");
    else
        puts("FAILD!\n");
    if(CheckWholeness(&tmpobj[0],2) != -1) puts("Check FAILD!");
    else puts("Check ok!");

    puts(" Creating object (class=0, size=0, flags=0)... ");
    tmpobj[2] = newObj(0,0,0);
    dyrting(tmpobj[2]);
    if((Image[tmpobj[2]]->size == 0) && (Image[tmpobj[2]]->class == 0) && (Image[tmpobj[2]]->flags == 0))
        puts("ok!\n");
    else
        puts("FAILD!\n");
    if(CheckWholeness(&tmpobj[0],3) != -1) puts("Check FAILD!");
    else puts("Check ok!");

    retNNObjects(&tmpobj[0],3,0);

}


int testGC1(void) {
objNum tmp, tmp2;
	ImageTop = 0;

	newObj(0,0,0);
	tmp = newObj(1,8,1);
	Image[tmp]->data = newObj(1,4,1);
	newObj(1,5,1);
	newObj(1,0,1);
	newObj(1,20,0);
	tmp2 = newObj(1,4,1);
	Image[tmp2]->data = tmp2;
	tmp2 = newObj(1,4,1);
	(&Image[tmp]->data)[1] = tmp2;
	Image[tmp2]->data = tmp;
	// создали 8 объектов, теперь запускаем GC
	GC_markAndSweep(tmp);
	// теперь должно остатся 4 объекта: 0, 1, 2, 7
	if((Image[0] != 0) &&
	   (Image[1] != 0) &&
	   (Image[2] != 0) &&
	   (Image[7] != 0))
	   if((Image[3] == 0) &&
	      (Image[4] == 0) &&
	      (Image[5] == 0) &&
	      (Image[6] == 0)) return 0;
	return 1;
}

int testGC2(void) {
objNum tmp, tmp2;
	ImageTop = 0;

	newObj(0,0,0);
	tmp = newObj(1,8,1);
	Image[tmp]->data = newObj(1,0,0);
	tmp2 = newObj(1,12,1);
	(&Image[tmp]->data)[1] = tmp2;
	(&Image[tmp2]->data)[1] = tmp = newObj(1,8,1);
	tmp2 = Image[tmp2]->data = newObj(1,8,1);
	Image[tmp2]->data = newObj(1,34,0);
	(&Image[tmp2]->data)[1] = newObj(1,56,0);
	Image[tmp]->data = newObj(1,0,1);
	(&Image[tmp]->data)[1] = 1;
	// всего должно быть 9 объектов
	GC_markAndSweep(1);
	// должны остатся все объекты
	for(tmp = 0; tmp < ImageLimit; tmp++) {
	  if((tmp < 9) && (Image[tmp] == 0)) return 1;
	  if((tmp > 8) && (Image[tmp] != 0)) return 1;
	}
	return 0;
}

int testGC3(void) {
objNum tmp, tmp2;
	ImageTop = 0;

	newObj(0,0,0);
	tmp = newObj(1,8,1);
	Image[tmp]->data = newObj(1,0,0);
	tmp2 = newObj(1,12,1);
	(&Image[tmp]->data)[1] = tmp2;
	(&Image[tmp2]->data)[1] = tmp = newObj(1,8,1);
	tmp2 = Image[tmp2]->data = newObj(1,8,1);
	Image[tmp2]->data = newObj(1,34,0);
	(&Image[tmp2]->data)[1] = newObj(1,56,0);
	Image[tmp]->data = newObj(1,0,1);
	(&Image[tmp]->data)[1] = 1;
	newObj(1,0,0);
	tmp = newObj(0,16,1);
	Image[tmp]->data = newObj(tmp,4,1);
	tmp2 = (&Image[tmp]->data)[1] = newObj(tmp,8,1);
	Image[Image[tmp]->data]->data = tmp2;
	Image[tmp2]->data = newObj(tmp,0,1);
	(&Image[tmp]->data)[2] = (&Image[(&Image[tmp]->data)[1]]->data)[1] = newObj(tmp,56,0);
	tmp2 = (&Image[tmp]->data)[3] = newObj(tmp,12,1);
	Image[tmp2]->data = newObj(tmp,0,1);
	(&Image[tmp2]->data)[1] = newObj(tmp,0,0);
	(&Image[tmp2]->data)[2] = newObj(tmp,4,1);
	// всего должно быть 19 объектов
	GC_markAndSweep(tmp);
	// должны остатся все объекты
	for(tmp = 0; tmp < ImageLimit; tmp++) {
	  if((tmp > 9) && (tmp < 19) && (Image[tmp] == 0)) return 1;
	  if((tmp < 10) && (tmp > 18) && (Image[tmp] != 0)) return 1;
	}
	return 0;
}

void test_memmng_GC(void) {
objNum i, savedTop;
obj **savedImage; // указатель на массив указателей типа obj


    puts("----- test_memmng_GC -----");
    // выделяем память в каторую сохраним текущий имедж
    savedImage = (obj **) getEmptyObj(sizeof(obj *) * ImageLimit); // умнажаем размер указателя на максимальное количество объектов в Image
    if(savedImage == 0){
     puts("cann`t save current Image (cann`t get memory for Image save)");
     return;
    }
    savedTop = ImageTop;
    // переносим все указатели на объекты из Image в savedImage
    for(i=0; i < ImageLimit; i++) {
      savedImage[i] = Image[i];
      Image[i] = 0;
    }
    puts("Curent Image sucessfuly saved!");
    // начинаем тесты
    if(testGC1()) puts("testGC1... FAILD!");
    else puts("testGC1... ok!");
    for(i=0; i < ImageLimit; i++) if(Image[i] != 0) notNeededObj(i);
    if(testGC2()) puts("testGC2... FAILD!");
    else puts("testGC2... ok!");
    for(i=0; i < ImageLimit; i++) if(Image[i] != 0) notNeededObj(i);
    if(testGC3()) puts("testGC3... FAILD!");
    else puts("testGC3... ok!");
    for(i=0; i < ImageLimit; i++) if(Image[i] != 0) notNeededObj(i);
    // переносим все указатели на объекты из savedImage в Image
    for(i=0; i < ImageLimit; i++) {
      savedImage[i] = Image[i];
      Image[i] = 0;
    }
    puts("Curent Image sucessfuly restored!");
    // освобаждаем занятую память
    returnDirtyObj((obj*) savedImage);
    ImageTop = savedTop;
}

void test_MemMngC(int testGC) {
    puts(" ###  Testing <memmng.c> ### \n");
    test_memmng_getEmptyObj();
    test_memmng_resizeObj();
    test_memmng_newObj();
    if(testGC) test_memmng_GC();
    puts(" ###  End Testing <memmng.c> ### \n");
}

/* --------------------------  End MemMng.c ------------------------------------------- */
