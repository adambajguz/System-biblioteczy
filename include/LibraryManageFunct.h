#ifndef LIBRARYMANAGEFUNCT_H_INCLUDED
#define LIBRARYMANAGEFUNCT_H_INCLUDED

// File with Library Manage Functions

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./LibraryAuxFunct.h"
#include "./LibraryUsers.h"

#define SLEEP_PAUSE 1 // if 0 - sleep after action messaage, if 1 - pause after action message

#if SLEEP_PAUSE == 0
#define ACTION_MESSAGE_TIME 3000
#endif // SLEEP_PAUSE

#define MAIN_CONFIG_FILE "settings.cfg"
typedef struct tMainConfig
{
    unsigned int AutoLoad;
    unsigned int MaxDays;
    unsigned int Books;
    unsigned int Users;
    unsigned int Borrowed;
} MainConfig;

MainConfig GetConfig(void); // Function that gets config from MAIN_CONFIG_FILE

enum FILTRE
{
    CANCEL = 1000,
    ALL = 1,
    BORROWED = 2,
    NOT_BORROWED = 3,
    BORROWED_LONG = 4,
    RETURNED = 5,

    ID = 20,
    TITLE = 30,
    NAME = 40,
    SURNAME = 50,
    PESEL = 60
};

//---Structere which is returned by all functions connected to MainMenu---
typedef struct t_libret
{
    union
    {
        BookData book;
        UserData user;

        BooksNode * book_node;
        UsersNode * user_node;
    };
    enum
    {
        DEFAULT=-2,
        NO_JUMP=-1
    } menucmd;
} _lib_ret;
//------------------------------------------------------------------------^^

//---Structere which contains pointers to Books & Users Lists and Config of loaded library---
struct _lib_data
{
    BooksNode * book;
    UsersNode * user;
    ConfigData cfg;
};
//-------------------------------------------------------------------------------------------^^

_lib_ret Books(int arg, FILE ** libfile, struct _lib_data * data); // Function responsible for Books Window TUI (Text User Interface)
_lib_ret Users(int arg, FILE ** libfile, struct _lib_data * data); // Function responsible for Users Window TUI

bool BookDetails(const FILE ** libfile, const struct _lib_data * data, BooksNode ** selectedB); // Function responsible for Book Details Window TUI
bool UserDetails(const FILE ** libfile, const struct _lib_data * data, UsersNode ** selectedU); // Function responsible for User Details Window TUI
bool FiltreBorrowed(const enum FILTRE method, const BorrowedNode * selected2, const unsigned int max_borrow_days); // Function responsible for filtering Borrowed List

void AddBook(struct _lib_data * data); // Function responsible for adding books to the list
int RemoveBook(struct _lib_data * data, BooksNode * selected); // Function responsible for removing books to the list
bool SearchBook(const enum FILTRE method, BooksNode * selected2, const char str[1024]); // Function responsible for searching books to the list
bool FiltreBook(const enum FILTRE method, const BooksNode * selected2, const UsersNode * users, const unsigned int max_borrow_days); // Function responsible for filtering books to the list

void AddUser(struct _lib_data * data); // Function responsible for adding users to the list
int RemoveUser(struct _lib_data * data, UsersNode * selected); // Function responsible for removing users to the list
bool SearchUser(const enum FILTRE method, UsersNode * selected2, const char str[1024]); // Function responsible for searching users to the list
bool FiltreUser(const enum FILTRE method, const BorrowedNode * selected2, const unsigned int max_borrow_days); // Function responsible for filtering users to the list

_lib_ret BookBorrow(int arg, FILE ** libfile, struct _lib_data * data); // Function responsible for Book Borroww Window TUI
_lib_ret BookReturn(int arg, FILE ** libfile, struct _lib_data * data); // Function responsible for Book Return Window TUI

void SaveLib(const FILE * libfile, const struct _lib_data * data); // Function responsible for saving whole library
int LoadLib(const FILE * libfile, struct _lib_data * data); // Function responsible for loading whole library (returns error code or code 6 - success)

_lib_ret LibSettings(int arg, FILE ** libfile, struct _lib_data * data); // Function responsible for Library Settings Window TUI

#endif // LIBRARYMANAGEFUNCT_H_INCLUDED
