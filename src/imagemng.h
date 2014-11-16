/***************************************************************************
 *   Copyright (C) 2006 by Saemon Zixel                                    *
 *   saemon@pochta.ru                                                      *
 *                                                                         *
 ***************************************************************************/

#define O_RDONLY 00
#define O_WRONLY 01
#define O_RDWR	02
#define O_CREATE 0100

#define ImageLimit 10000000

extern obj** Image;
extern unsigned long ImageTop;

extern void initImage(void);

extern int LoadImage(char *filepath);
extern int SaveImage(char *filepath, objNum inTheEnd);

extern objNum ImageSize(int type);
