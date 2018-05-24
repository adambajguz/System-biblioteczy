#ifndef LIBRARYUSERS_H_INCLUDED
#define LIBRARYUSERS_H_INCLUDED

// File with Library Users List Functions

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./LibraryBorrowed.h"
#include "./eCW/eCW_graphics.h"

//---Library Config Data Struct---
typedef struct tConfigData
{
    unsigned int maxBorrowDays;

    char * libname;

    unsigned int BUIDnext; //Books Unique ID
    unsigned int UUIDnext; //Users Unique ID

} ConfigData;
//-----------------------------------^^


//---Library User Data Struct---
typedef struct tUserData
{
    unsigned int UID; //unique user id
    char * name;
    char * surname;
    char * address;
    char pesel[12]; //eg. 00123456789/0
    char * email;
    char telephone[13]; // eg. +48123456789/0

    BorrowedNode * borrowed;
} UserData;
//------------------------------^^


//---Users Node---
struct tUsersNode
{
    UserData data;
    struct tUsersNode * prev, * next;
};
//----------------^^

//---UsersCP Node---
//Used for ScrollList
//as auxiliary list
typedef struct tUsersCPNode
{
    UsersNode * node;
    struct tUsersCPNode * prev, * next;
} UsersCPNode;
//------------------^^


void UsersCP_AddBegin(UsersCPNode ** first, const UsersNode * node); //Function that adds an element to UsersCP list (auxiliary list)
void UsersCP_Sort(const UsersCPNode * first, const enum SORT method, const enum SORT_WAY sw); //Function that sorts UsersCP list (auxiliary list)
void UsersCP_Free(UsersCPNode ** first); //Function that destroys UsersCP list (auxiliary list) and frees memeory
void UsersCP_ScrollListPrint(UsersCPNode * selected, const unsigned int num, const bool down, const unsigned int max_borrow_days, const int h); //Function that prints UsersCP ScrollList (auxiliary list)

//---Users list control functions---
UsersNode * Users_SearchWhoBorrowedByBUID(UsersNode * first, const unsigned int sBUID); //Function that returns user who has a book with given BUID

void Users_AddBegin(UsersNode ** first, const UserData data); //Function that adds an element to Users list
void Users_Remove(UsersNode ** first, UsersNode * selected); //Function that removes an element to Users list

void Users_Save(UsersNode * first, const FILE * libfile); //Function that saves Users list to file
int Users_Load(UsersNode ** first, const FILE * libfile); //Function that loads Users list from file

void Users_PrintDetails(const UsersNode * element, const unsigned int max_borrow_day); //Function that prints all data from single element of Users list
void Users_ListPrintSingle(const UsersNode * element, const bool selected, const unsigned int max_borrow_days); //Function that prints short data from element of Users list for ScrollList purpose
void Users_Free(UsersNode ** first); //Function that destroys Users list (auxiliary list) and frees memeory

#endif // LIBRARYUSERS_H_INCLUDED
