/***************************************************************************
 *   Copyright (C) 2006 by Saemon Zixel                                    *
 *   saemon@pochta.ru                                                      *
 *                                                                         *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "memmng.h"
#include "imagemng.h"
#include "vm.h"
#include "primitivemng.h"

int testOutFile = 0;

objNum searchInCompactDictionary(objNum dict, int SymbolSize, char *Symbol) {
objNum *collection;
int i, i2;

	collection = &Image[dict]->data;
	for(i = 0; i < Image[dict]->size/4; i += 2) {
		if(Image[collection[i]]->size == SymbolSize) {

			for(i2 = 0 ; i2 < Image[collection[i]]->size-1; i2++)
				if((&Image[collection[i]]->dataAsChar)[i2] != Symbol[i2]) break;

			if((i2 == Image[collection[i]]->size - 1) & ((&Image[collection[i]]->dataAsChar)[i2] == Symbol[i2]))
				return collection[i+1];
		}
	}
	return 0;
}

void compareTestFile(char *string, int size) {
char buffer[500];
char onechar;
int result = 1;
int i, eof;

	// считываем строку
	for(i = 0; i < 500; i++) {
		result = read(testOutFile, &onechar, 1);
		if(result) { buffer[i] = onechar; buffer[i+1] = '\n'; }
		else break;
		
		if(onechar == '\n') break; // считали строчку - выходим
	}

	// если удалось считать строку из файла то начинаем сравнение строк
	if(result == 1) {
		for(i = 0; i < size; i++){
			if(string[i] != buffer[i]){
				if((string[i] == '\0') && (buffer[i] == '\n')) result = 1;
				else result = 0;
				break;
			}
		}
	} else result = -1;

	if(result > 0)  printf("ok     %s\n", string);
	if(result == 0) printf("FAILD! %s\n", string);
	if(result < 0)  printf("       %s\n", string);

}

int main(int argc, char *argv[]) {
objNum startMethodState;

  testOutFile = open("/home/saemon/mystexp/tests.out", 0);

  initImage();
  SmalltalkDictionary = LoadImage("/home/saemon/mystexp/baseimage3");
//  printf(" Max Object number in Image: %li\n", ImageTop);
  startMethodState = searchInCompactDictionary(SmalltalkDictionary, 16, "startMethodState");
  continueContext(startMethodState);
//  primitiveZero();
  printf("Exit Main Program\n");
  return EXIT_SUCCESS;

  if(testOutFile) close(testOutFile);
}
