/***************************************************************************
 *   Copyright (C) 2006 by Saemon Zixel                                    *
 *   saemon@pochta.ru                                                      *
 *                                                                         *
 ***************************************************************************/

#ifndef TESTS_DATA_H
#define TESTS_DATA_H

unsigned long forRefresh_lits[1] = {0};
#define forRefresh_lits_count 1
unsigned long forRefresh_tmps[6] = {5,4,3,2,1,0};
#define forRefresh_tmps_count 5
unsigned long forRefresh_args[6] = {10,9,8,7,6,0};
#define forRefresh_args_count 5
unsigned long forRefresh_inst[3] = {7302,72,0};
#define forRefresh_inst_count 3
unsigned long forRefresh_context[12] = {0,0,0,0,0,0,73,71,99,0,0,103};
unsigned char forRefresh_bytecode[103] = {191,1,1,190,1,1,189,1,1,188,1,1,186,1,185,1,184,1,183,1,1,182,1,1,181,1,1,180,1,1,178,1,177,1,176,1,175,1,1,174,1,1,173,1,1,172,1,1,170,1,169,1,168,1,151,1,150,1,149,1,148,1,146,145,144,135,1,134,1,133,1,132,1,130,129,128,248,1,240,1,232,1,224,1,208,200,192,120,1,112,1,104,1,96,1,80,72,64,32,1,36,1,1};
#define forRefresh_bytecode_count 103

// #0 - #100
unsigned long nullObject[3] = {0,0,0};  //  #0
unsigned long integerClass1[3+3] = {0,1,3*4, 11,0,0}; //#10 - будет использоватся для хранения небольших чисел
unsigned char integerClass1_name[12+7] =  {0,0,0,0, 0,0,0,0, 7,0,0,0, 'I','n','t','e','g','e','r'}; //#11
unsigned long bytearrayClass[3+3] = {0,1,3*4, 21,0,0}; //#20 - будет использоватся для объектов с байткодом
unsigned char bytearrayClass_name[12+9] =  {0,0,0,0, 0,0,0,0, 9,0,0,0, 'B','y','t','e','A','r','r','a','y'}; //#21
unsigned long arrayClass[3+3] = {0,1,3*4, 31,0,0}; //#30 - будет использоватся для списков lits, tmps, args...
unsigned char arrayClass_name[12+5] =  {0,0,0,0, 0,0,0,0, 5,0,0,0, 'A','r','r','a','y'}; //#31
unsigned long SymbolClass[3+3] = {0,1,3*4, 31,0,0}; // #40 - будет использоватся для объектов сообщений, строк...
unsigned char SymbolClass_name[12+6] =  {0,0,0,0, 0,0,0,0, 5,0,0,0, 'S','y','m','b','o','l'}; // #41

unsigned char testMS_Symbol32[12+12] = {0,0,0,0, 0,0,0,0, 12,0,0,0, 't','e','s','t','3','m','e','t','h','o','d','2'}; // #80
unsigned char testMS_Symbol24[12+12] = {0,0,0,0, 0,0,0,0, 12,0,0,0, 't','e','s','t','2','m','e','t','h','o','d','4'}; // #81
unsigned char testMS_Symbol13[12+12] = {0,0,0,0, 0,0,0,0, 12,0,0,0, 't','e','s','t','1','m','e','t','h','o','d','3'}; // #82
unsigned char testMS_Symbol41[12+12] = {0,0,0,0, 0,0,0,0, 12,0,0,0, 't','e','s','t','4','m','e','t','h','o','d','1'}; // #83
unsigned char testMS_Symbol_5[12+12] = {0,0,0,0, 0,0,0,0, 12,0,0,0, 't','e','s','t','_','m','e','t','h','o','d','5'}; // #84
unsigned char testMS_Symbol[12+1] = {0,0,0,0, 0,0,0,0, 1,0,0,0, '\\'}; // #85

// Стартовый объект
unsigned long startObject[3+1] = {400,1,0, 0}; // #99

// класс 1 (#100-#200)
unsigned long testMS_1class[3+3] = {0,1,12, 101,100,102}; //#100
unsigned char testMS_1name[12+5] = {0,0,0,0, 0,0,0,0, 5,0,0,0, 'T','e','s','t','1'}; //#101
unsigned long testMS_1methoddict1[3+12] = {0,1,12*4, 110,0,111,0,112,3,113,0,114,5,115,6}; //#102
unsigned char testMS_1method1name[12+12] = {0,0,0,0, 0,0,0,0, 12,0,0,0, 't','e','s','t','1','m','e','t','h','o','d','1'}; //#110
unsigned char testMS_1method2name[12+12] = {0,0,0,0, 0,0,0,0, 12,0,0,0, 't','e','s','t','1','m','e','t','h','o','d','2'}; //#111
unsigned char testMS_1method3name[12+12] = {0,0,0,0, 0,0,0,0, 12,0,0,0, 't','e','s','t','1','m','e','t','h','o','d','3'}; //#112
unsigned char testMS_1method4name[12+12] = {0,0,0,0, 0,0,0,0, 12,0,0,0, 't','e','s','t','1','m','e','t','h','o','d','4'}; //#113
unsigned char testMS_1method5name[12+12] = {0,0,0,0, 0,0,0,0, 12,0,0,0, 't','e','s','t','_','m','e','t','h','o','d','5'}; //#114
unsigned char testMS_1method6name[12+1] = {0,0,0,0, 0,0,0,0, 1,0,0,0, '\\'}; // #115

// класс 2 (#200-#300)
unsigned long testMS_2class[3+3] = {0,1,12, 201,100,202}; // #200
unsigned char testMS_2name[12+5] = {0,0,0,0, 0,0,0,0, 5,0,0,0, 'T','e','s','t','2'}; // #201
unsigned long testMS_2methoddict[3+12] = {0,1,12*4, 210,0,211,0,212,0,213,0,214,500,215,50}; // #202
unsigned char testMS_2method1name[12+5] = {0,0,0,0, 0,0,0,0, 5,0,0,0, 't','e','s','t','2'}; // #210
unsigned char testMS_2method2name[12+12] = {0,0,0,0, 0,0,0,0, 12,0,0,0, 't','e','s','t','2','m','e','t','h','o','d','1'}; //#211
unsigned char testMS_2method3name[12+12] = {0,0,0,0, 0,0,0,0, 12,0,0,0, 't','e','s','t','2','m','e','t','h','o','d','2'}; //#212
unsigned char testMS_2method4name[12+12] = {0,0,0,0, 0,0,0,0, 12,0,0,0, 't','e','s','t','2','m','e','t','h','o','d','3'}; //#213
unsigned char testMS_2method5name[12+12] = {0,0,0,0, 0,0,0,0, 12,0,0,0, 't','e','s','t','2','m','e','t','h','o','d','4'}; //#214
unsigned char testMS_2method6name[12+12] = {0,0,0,0, 0,0,0,0, 12,0,0,0, 't','e','s','t','_','m','e','t','h','o','d','5'}; //#215

// класс 3 (#300-#400)
unsigned long testMS_3class[3+3] = {0,1,12, 301,200,302}; // #300
unsigned char testMS_3name[12+5] = {0,0,0,0, 0,0,0,0, 5,0,0,0, 'T','e','s','t','3'}; // #301
unsigned long testMS_3methoddict[3+10] = {0,1,10*4, 310,0,311,0,312,200,313,0,314,550}; // #302
unsigned char testMS_3method1name[12+5] = {0,0,0,0, 0,0,0,0, 5,0,0,0, 't','e','s','t','3'}; //#310
unsigned char testMS_3method2name[12+12] = {0,0,0,0, 0,0,0,0, 12,0,0,0, 't','e','s','t','3','m','e','t','h','o','d','1'}; //#311
unsigned char testMS_3method3name[12+12] = {0,0,0,0, 0,0,0,0, 12,0,0,0, 't','e','s','t','3','m','e','t','h','o','d','2'}; //#312
unsigned char testMS_3method4name[12+12] = {0,0,0,0, 0,0,0,0, 12,0,0,0, 't','e','s','t','3','m','e','t','h','o','d','3'}; //#313
unsigned char testMS_3method5name[12+12] = {0,0,0,0, 0,0,0,0, 12,0,0,0, 't','e','s','t','3','m','e','t','h','o','d','4'}; //#314

// класс 4  (#400-#500)
unsigned long testMS_4class[3+3] = {0,1,12, 401,300,402}; // #400
unsigned char testMS_4name[12+5] = {0,0,0,0, 0,0,0,0, 5,0,0,0, 'T','e','s','t','4'}; // #401
unsigned long testMS_4methoddict[3+4] = {0,1,4*4, 410,600,411,2000}; // #402
unsigned char testMS_4method1name[12+5] = {0,0,0,0, 0,0,0,0, 5,0,0,0, 't','e','s','t','4'}; //#410
unsigned char testMS_4method2name[12+12] = {0,0,0,0, 0,0,0,0, 12,0,0,0, 't','e','s','t','4','m','e','t','h','o','d','1'}; //#411

// 1 метод (#500-#550) test2method4
unsigned long testMS_method1[3+6] = {0,1,24, 503,504,501,502,200,214}; // #500 - Method(test2method4)
unsigned long testMS_method1argCount[3+1] = {0,0,4, 2}; // #501
unsigned long testMS_method1tmpCount[3+1] = {0,0,4, 2}; // #502
unsigned char testMS_method1bytecode[12+103] = {0,0,0,0, 0,0,0,0, 102,0,0,0, 191, 1, 1, 190, 1, 1, 189, 1, 1, 188, 1, 1, 186, 1, 185, 1, 184, 1, 183, 1, 1, 182, 1, 1, 181, 1, 1, 180, 1, 1, 178, 1, 177, 1, 176, 1, 175, 1, 1, 174, 1, 1, 173, 1, 1, 172, 1, 1, 170, 1, 169, 1, 168, 1, 151, 1, 150, 1, 149, 1, 148, 1, 146, 145, 144, 135, 1, 134, 1, 133, 1, 132, 1, 130, 129, 128, 248, 1, 240, 1, 232, 1, 224, 1, 208, 200, 192, 120, 1, 112, 1, 104, 1, 96, 1, 80, 72, 64, 32, 1, 36, 1, 1}; // #503
unsigned long testMS_method1literals[3+0] = {0,1,0 }; // #504
// 1 блок
unsigned long testMS_block1[3+6] = {0,1,24, 513,514,511,512,0,0}; // #510
unsigned long testMS_block1argCount[3+1] = {0,0,4, 1}; // #511
unsigned long testMS_block1tmpCount[3+1] = {0,0,4, 4}; // #512 - tmpcount наследуются из радителя метода method(argcount+tmpcount)
unsigned char testMS_block1bytecode[12+0*4] = {0,0,0,0, 0,0,0,0, 0,0,0,0 }; // #513
unsigned long testMS_block1literals[3+0] = {0,1,0 }; // #514

// 2 метод (#550-#600) test3method4
unsigned long testMS_method2[3+6] = {0,1,24, 553,554,551,552,300,314}; // #550 - Method(test3method4)
unsigned long testMS_method2argCount[3+1] = {0,0,4, 4}; // #551
unsigned long testMS_method2tmpCount[3+1] = {0,0,4, 3}; // #552
unsigned char testMS_method2bytecode[12+0] = {0,0,0,0, 0,0,0,0, 0,0,0,0 }; // #553
unsigned long testMS_method2literals[3+2] = {0,1,2*4, 560,570}; // #554
// 2 блок он же literal0
unsigned long testMS_block2[3+6] = {0,1,24, 563,564,561,562,0,0}; // #560
unsigned long testMS_block2argCount[3+1] = {0,0,4, 2}; // #561
unsigned long testMS_block2tmpCount[3+1] = {0,0,4, 2}; // #562 - tmpcount наследуются из радителя метода method(argcount+tmpcount)
unsigned char testMS_block2bytecode[12+0*4] = {0,0,0,0, 0,0,0,0, 0,0,0,0}; // #563
unsigned long testMS_block2literals[3+1] = {0,1,4, 570}; // #564
//
unsigned char testMS_method2literal1[12+12] = {0,0,0,0, 0,0,0,0, 12,0,0,0, 't','e','s','t','2','m','e','t','h','o','d','4'}; // #570

// 3 метод (#600-#650) test4 - он же стартовый
unsigned long testMS_method3[3+6] = {0,1,24, 603,604,601,602,400,410}; // #600 - Method(test4)
unsigned long testMS_method3argCount[3+1] = {0,0,4, 3}; // #601
unsigned long testMS_method3tmpCount[3+1] = {0,0,4, 3}; // #602
unsigned char testMS_method3bytecode[12+0*4] = {0,0,0,0, 0,0,0,0, 0,0,0,0 }; // #603
unsigned long testMS_method3literals[3+4] = {0,1,4*4, 610,620,621,622}; // #604
// 3 блок он же literal0
unsigned long testMS_block3[3+6] = {0,1,24, 613,614,611,612,0,0}; // #610
unsigned long testMS_block3argCount[3+1] = {0,0,4, 1}; // #611
unsigned long testMS_block3tmpCount[3+1] = {0,0,4, 2}; // #612 - tmpcount наследуются из радителя метода method(argcount+tmpcount)
unsigned char testMS_block3bytecode[12+0] = {0,0,0,0, 0,0,0,0, 0,0,0,0 }; // #613
unsigned long testMS_block3literals[3+1] = {0,1,4, 570}; // #614
//
unsigned char testMS_method3literal1[12+12] = {0,0,0,0, 0,0,0,0, 12,0,0,0, 't','e','s','t','4'}; // #620
unsigned char testMS_method3literal2[12+12] = {0,0,0,0, 0,0,0,0, 12,0,0,0, 't','e','s','t','3','m','e','t','h','o','d','4'}; // #621
unsigned char testMS_method3literal3[12+12] = {0,0,0,0, 0,0,0,0, 12,0,0,0, 't','e','s','t','2','m','e','t','h','o','d','4'}; // #622


// 1 MS (#700 - #800)
unsigned long testMS_MS1[3+8] = {0,1,32, 99,600,704,702,703,1,0,0}; // #701 Стартовый MethodState, Method(test4), self - object.class = Test4.
unsigned long testMS_MS1tmps[3+6] = {0,1,6*4, 0,0,0,0,0,0}; // #702 - его будут resize !
unsigned long testMS_MS1args[3+7] = {0,1,7*4, 0,0,0,0,0,0,0}; // #703
unsigned long testMS_MS1bytecodeOffset[3+1] = {0,0,4, 0}; // #704
// 2 MS (#800 - #820) - для test_vm_getNextInstruction()
unsigned long testMS_MS2[3+8] = {0,1,32, 99,500,804,802,803,0,0,0}; // #801 Стартовый MethodState, Method(test2method4), self - object.class = Test4.
unsigned long testMS_MS2tmps[3+10] = {0,1,40, 0,0,0,0,0,0,0,0,0,0}; // #802
unsigned long testMS_MS2args[3+7] = {0,1,7*4, 0,0,0,0,0,0,0}; // #803
unsigned long testMS_MS2bytecodeOffset[3+1] = {0,0,4, 0}; // #804
// 3 MS (#820 - #830) - для test_vm_executeInstruction()
unsigned long testMS_MS3[3+8] = {0,1,32, 825,830,824,822,823,69,0,0}; // #821
unsigned long testMS_MS3tmps[3+4] = {0,1,16, 1,2,3,4}; // #822
unsigned long testMS_MS3args[3+4] = {0,1,16, 0,0,0,0}; // #823
unsigned long testMS_MS3bytecodeOffset[3+1] = {0,0,4, 0}; // #824
unsigned long testMS_MS3self[3+4] = {400,1,4*4, 100,200,300,400}; // #825
// метод для 3 MS (#830-#850) test4 - он же стартовый
unsigned long testMS_method4[3+6] = {0,1,24, 833,834,831,832,400,410}; // #830 - Method(test4)
unsigned long testMS_method4argCount[3+1] = {0,0,4, 4}; // #831
unsigned long testMS_method4tmpCount[3+1] = {0,0,4, 4}; // #832
unsigned char testMS_method4bytecode[12+0] = {0,0,0,0, 0,0,0,0, 0,0,0,0 }; // #833
unsigned long testMS_method4literals[3+4] = {0,1,4*4, 10,20,30,40}; // #834


unsigned long newImageLength = 705;

#endif
