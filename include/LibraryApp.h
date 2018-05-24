#ifndef LIBRARYAPP_H_INCLUDED
#define LIBRARYAPP_H_INCLUDED

/*
 *  (C) Adam Bajguz - 2017y.
 *
 *  A library management program that allows the registration of
 *  new books and readers, and borrowing books.
 */

// Main library program init functions

#include "./LibraryMenu.h"
#include <windows.h>

void LibraryApp(void); // Main Library Application Function
void _initMenu(struct MenuLevel ** CurrentMenu); // Function that creates main menu

#endif // LIBRARYAPP_H_INCLUDED
