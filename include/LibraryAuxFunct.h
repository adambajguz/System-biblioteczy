// File with Library Auxiliary Functions

#ifndef LIBRARYAUXFUNCT_H_INCLUDED
#define LIBRARYAUXFUNCT_H_INCLUDED

#include <stdbool.h>
#include <stdio.h>
#include "./eCW/eCW_graphics.h"


//Macro used to create Yes or No question
#define YN_option(str, ifyes, ifno)\
cCURSOR(true, 20);\
printf("\n %s (T / N)? ", #str);\
unsigned char opt;\
while(1){\
    opt=getch();\
    if(opt=='t'||opt=='T'){\
    ifyes\
    break;}\
    else if(opt=='n'||opt=='N'){\
    ifno\
    break;}\
}\
cCURSOR(false, 20);

enum HelpText
{
    MENU=0,
    BOOKS=1,
    BOOKS_SINGLE=10,
    BOOKS_SELECT=11,
    USERS=2,
    USERS_SINGLE=20,
    USERS_SELECT=21,
    FILENAME_LOAD=3,
    SETTINGS=4,
    SETTINGS2=5
};

bool StringCompare(const char * str1, const char * str2); // compares to strings to check which is 'lower'

void fget16static(const FILE * file, const char * dest); // a fuction that gets up to 16 chars from file to static char arrary and removes '\n'
void fget256static(const FILE * file, char ** dest); // a fuction that gets up to 256 chars from file and removes '\n'
void fget1024(const FILE * file, char ** dest); // a fuction that gets up to 1024 chars from file and allocates memory and assigns a pointer value to dest and removes '\n'

void get(const char * dest, int i);

void get1024(char ** dest); // a fuction that gets up to 1024 chars from stdin  and allocates memory and assigns a pointer value to dest and removes '\n'
void sget1024(const char * str); // a fuction that gets 256 static from stdin as a name of file and removes '\n'
void get256(const char * fname); // a fuction that gets 256 chars from stdin as a name of file and removes '\n'

void endlDel(char * str); // a function that removes '/n' from string

void PrintUMenuPos(const char * str); // a fuction that writes strong/italic underlined string
void PrintU2MenuPos(const char * str); // a fuction that writes underlined string

void PrintDoubleLine(short xdim);

void Draw_BoxUPart(void); // a function that draws upper part of the box
void Draw_BoxDPart(void); // a function that draws lower part of the box

void ListBorder(const bool arrow, const bool up); // a function that draws books, users etc. list borders with more intems indicator arrows
void PrintSelectionMark(const bool selected); // a fucntion that prints selection mark (used in ListView)

void MMenuBackPause(void);  // a function that pauses program with meessage go back to menu and waits for any key tobe pressed
void ContinuePause(void); // a function that pauses program and waits for any key tobe pressed

void PrintErrorInfo(unsigned short err); // a funciton that prints multiple types of file load errors
void PrintHelp(const enum HelpText v); // a function that prints multiple types of help used in app

void PrintLastFile(void); // Function that prints last file name
void MPrintLastFile(void); // Function that prints last file name for menu purpose

#endif // LIBRARYAUXFUNCT_H_INCLUDED
