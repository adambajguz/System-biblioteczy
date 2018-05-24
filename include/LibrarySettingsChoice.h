#ifndef LIBRARYSETTINGSCHOICE_H_INCLUDED
#define LIBRARYSETTINGSCHOICE_H_INCLUDED

#include <conio.h>
#include <windows.h>
#include "./LibraryManageFunct.h"

struct ChoiceItem
{
    char str[32]; // settings choice item label
    unsigned int what, val; // setting number & value
};

struct ChoiceLevel
{
    struct ChoiceItem * MItems; // pointer to the first item in current level
    void (*funct)(const int, const int);  // pointer to function to be executed while action
    char MName[80]; // setting name
    short MSize; // number of items
};

void ChoicePrint(const struct ChoiceLevel * menu[], const unsigned int menu_size, const unsigned int selection[], const unsigned int settingsel); // Function that prints settings choice menu
void ChoiceAction(const struct ChoiceLevel * menu, const int pos); // Function that handles choice action (SAVEING config)

#endif // LIBRARYSETTINGSCHOICE_H_INCLUDEDs
