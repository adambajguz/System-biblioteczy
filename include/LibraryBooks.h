#ifndef LIBRARYBOOKS_H_INCLUDED
#define LIBRARYBOOKS_H_INCLUDED

// File with Library Books List Functions

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./eCW/eCW_graphics.h"

enum SORT
{
    sID = 0,
    sTITLE = 2,
    sNAME = 4,
    sSURNAME = 6,

    sYEAR = 15, // to edit only

    sADDRESS = 16, // to edit only
    sEMAIL = 17, // to edit only
    sPHONE = 18, // to edit only

    sBORROW_TIME = 21,
    sRETURN_TIME = 22,

    sPESEL = 10,
    sBORROWED = 8
};

enum SORT_WAY
{
    //CANCEL = 0,
    LOWER = 1,
    UPPER = 2
};

//---Users Node---
typedef struct tUsersNode UsersNode;
//----------------^^

//---Library Book Data Struct---
typedef struct tBookData
{
    unsigned int UID; //unique book id
    char * id;
    char * title;
    char * authorsName;
    char * authorsSurname;
    int year;
} BookData;
//------------------------------^^


//---Books Node---
typedef struct tBooksNode
{
    BookData data;
    struct tBooksNode * prev, * next;
} BooksNode;
//----------------^^

//---BooksCP Node---
//Used for ScrollList
//as auxiliary list
typedef struct tBooksCPNode
{
    BooksNode * node;
    struct tBooksCPNode * prev, * next;
} BooksCPNode;
//----------------^^


void BooksCP_AddBegin(BooksCPNode ** first, const BooksNode * node); //Function that adds an element to BooksCP list (auxiliary list)
void BooksCP_Sort(const BooksCPNode * first, const UsersNode * users, const enum SORT method, const enum SORT_WAY sw); //Function that sorts BooksCP list (auxiliary list)
void BooksCP_Free(BooksCPNode ** first); //Function that destroys BooksCP list (auxiliary list) and frees memeory
void BooksCP_ScrollListPrint(BooksCPNode * selected, const UsersNode * first, const unsigned int num, const bool down, const int h); //Function that prints BooksCP ScrollList (auxiliary list)

//---Books list control functions---
BooksNode * Books_SearchByUID(BooksNode * first, const unsigned int sBUID); //Function that returns book with given BUID

void Books_AddBegin(BooksNode ** first, const BookData data); //Function that adds an element to Books list
void Books_Remove(BooksNode ** first, BooksNode * selected); //Function that removes an element to Books list

void Books_Save(BooksNode * first, const FILE * libfile); //Function that saves Books list to file
int Books_Load(BooksNode * first, const FILE * libfile); //Function that loads Books list from file

void Books_PrintDetails(const BooksNode * element, const UsersNode * first, const unsigned int max_borrow_days); //Function that prints all data from single element of Books list
void Books_ListPrintSingle(const BooksNode * element, const UsersNode * first, const bool selected, const bool disp_borrowed, const bool from_borrowed); //Function that prints short data from element of Books list for ScrollList purpose
void Books_Free(BooksNode ** first); //Function that destroys Books list (auxiliary list) and frees memeory

#endif // LIBRARYBOOKS_H_INCLUDED
