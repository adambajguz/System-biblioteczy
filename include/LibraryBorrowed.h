#ifndef LIBRARYBORROWED_H_INCLUDED
#define LIBRARYBORROWED_H_INCLUDED

// File with Library Borrowed Books List Functions

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./LibraryBooks.h"
#include "./eCW/eCW_graphics.h"

//---Library Borrowed Book Data Struct---
typedef struct tBorrowedData
{
    unsigned int UID;
    time_t borrowTime, returnTime;
} BorrowedData;
//---------------------------------------^^


//---Borrowed Books Node---
typedef struct tBorrowedNode
{
    BorrowedData data;
    struct tBorrowedNode * prev, * next;
} BorrowedNode;
//-------------------------^^


//---BorrowedCP Books Node---
//Used for ScrollList
//as auxiliary list
typedef struct tBorrowedCPNode
{
    BorrowedNode * node;
    struct tBorrowedCPNode * prev, * next;
} BorrowedCPNode;
//---------------------------^^

void BorrowedCP_AddBegin(BorrowedCPNode ** first, const UsersNode * node); //Function that adds an element to BorrowedCP list (auxiliary list)
void BorrowedCP_Sort(const BorrowedCPNode * first, const BooksNode * book, const enum SORT method, const enum SORT_WAY sw); //Function that sorts BorrowedCP list (auxiliary list)
void BorrowedCP_Free(BorrowedCPNode ** first); //Function that destroys BorrowedCP list (auxiliary list) and frees memeory
void BorrowedCP_ScrollListPrint(BorrowedCPNode * selected, BooksNode * users, const unsigned int num, const bool down, const int h); //Function that prints BorrowedCP ScrollList (auxiliary list)


//---Borrowed Books list control functions---
BorrowedNode * Borrowed_SearchByBUID(BorrowedNode * first, const unsigned int sBUID); //Function that returns BorrowedBook with given BUID

void Borrowed_AddBegin(BorrowedNode ** first, const BorrowedData data); //Function that adds an element to Borrowed list

unsigned int Borrowed_BSize(BorrowedNode * first); // Function that returns number of borrowed books on Borrowed List
unsigned int Borrowed_BAfterSize(BorrowedNode * first, const unsigned int max_borrow_days); // Funtion that returns number of borrowed books that are after max return time on Borrowed List

void Borrowed_Save(BorrowedNode * first, const FILE * libfile); //Function that saves Borrowed list to file
int Borrowed_Load(BorrowedNode ** first, const FILE * libfile); //Function that loads Borrowed list from file

void Borrowed_ListPrintSingle(const BorrowedNode * element, BooksNode * users, const bool selected);  //Function that prints all data from single element of Borrowed list
void Borrowed_Free(BorrowedNode ** first); //Function that destroys Borrowed list (auxiliary list) and frees memeory

#endif // LIBRARYBORROWED_H_INCLUDED
