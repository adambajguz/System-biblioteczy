#ifndef LIBRARYMENU_H_INCLUDED
#define LIBRARYMENU_H_INCLUDED

#include <conio.h>
#include <windows.h>
#include "./LibraryMainFunct.h"

struct MenuItem
{
    char str[80]; // menu item label
    struct MenuLevel * jump; // pointer to next level of menu
    _lib_ret (*funct)(int, FILE **, struct _lib_data *); // pointer to function to be executed while menu action
    int farg; // executed function argument
    void (*custom_print)(void); // custom label print function
};

struct MenuLevel
{
    struct MenuItem * MItems; // pointer to the first item in current level
    char MName[80]; // menu level name
    short MSize; // menu level item arrary size
};

void MenuPrint(const struct MenuLevel ** menu, const unsigned int selection, const struct _lib_data * data); // Function that prints Menu
_lib_ret MenuAction(const struct MenuLevel ** menu, FILE ** out, const struct _lib_data * data, const int pos); // Function that handles menu action (Enter anction) and returns _lib_ret.menucmd=DEFAULT or _lib_ret.menucmd=pos

#endif // LIBRARYMENU_H_INCLUDED
