/***************************************************************************
 *   Copyright (C) 2006 by Saemon Zixel                                    *
 *   saemon@pochta.ru                                                      *
 *                                                                         *
 ***************************************************************************/
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include "memmng.h"

#define O_RDONLY 00
#define O_WRONLY 01
#define O_RDWR	02
#define O_CREATE 0100

// Максимальное количество объектов в Image
#define ImageLimit 10000000

obj* fullImage[ImageLimit];
obj** Image = &fullImage[0];
unsigned long ImageTop;

// обнуляем Image для чистоты
void initImage(void){
unsigned long i;

	for(i = 0; i < ImageLimit; i++) Image[i]=NULL;
}

// загружаем все объекты в Image из файла filename
objNum LoadImage(char *filename){
    int fp;
    unsigned long index, class, flags, size;

    fp = open(filename,O_RDONLY);
    if(fp == -1){
        return 0;
    }else{
        ImageTop = 0;
        while(read(fp,&index,4) != 0){
            if(read(fp,&class,4) == 0) break;
	    if(index > ImageTop) ImageTop = index;
            read(fp, &flags, 4);
            read(fp, &size, 4);
            if(Image[index] == NULL)
	      Image[index] = getEmptyObj(sizeof(obj) + size - 4);
            Image[index]->class = class;
            Image[index]->flags = flags;
            Image[index]->size = size;
            if(Image[index]->size > 0)
                read(fp, &Image[index]->data, Image[index]->size);
#ifdef debug
 //           printf("objNum: %i size: %i\n",index,Image[index]->size);
#endif
        }
    }
    ImageTop++;
    close(fp);
#ifdef debug
    printf(" end4bytes: %i \n", index);
#endif
    return index;
}

int SaveImage(char *filepath, objNum inTheEnd){
    int fp;
    unsigned long i;

    fp = open(filepath,O_WRONLY | O_CREATE,S_IREAD | S_IWRITE);
    if(fp < 0){
        fp = open(filepath, O_WRONLY);
        if(fp < 0)
            return 1;
    }
    for(i = 0; i < ImageLimit; i++)
      if(Image[i] != NULL){
        write(fp, &i, sizeof(objNum));
        write(fp, Image[i], sizeof(obj) + Image[i]->size - 4);
#ifdef debug
//        printf(" %i object saved\n",i);
#endif
    }
    write(fp, &inTheEnd, sizeof(objNum));
    close(fp);
    return 0;
}

objNum ImageSize(int type) { // type: 1 - размер текущего имеджа в байтах; 0 - количество объектов
objNum i, result;

	result = 0;
	for(i = 0; i < ImageLimit; i++)
	 if(type == 0){
	  if(Image[i] != NULL) result++;
	 } else {
	  result += Image[i]->size + sizeof(obj) - 4;
	 }
	 return result;
}

