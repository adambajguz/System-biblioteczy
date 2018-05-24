/*
 *  (C) Adam Bajguz - 2017y.
 *
 *  A library management program that allows the registration of
 *  new books and readers, and borrowing books.
 */

#include "./LibraryApp.h"

void LibraryApp(void)
{
    _cinit(852);
    cDEFAULT_FONT();
    cBUFFER(80, 60);
    cSIZE(80, 60, 0, 0);
    clrscr();
    cCURSOR(false, 20);
    cTITLE("Program biblioteczny");

    struct MenuLevel * CurrentMenu;
    _initMenu(&CurrentMenu);

    FILE * file_out = NULL;
    struct _lib_data data = {NULL, NULL, NULL};

    if(GetConfig().AutoLoad)
        MenuAction(&CurrentMenu, file_out, &data, 1); // file auto open

    unsigned int pos=0;
    unsigned char key;
    bool redraw = true;
    while(1)
    {
        if(redraw)
        {
            MenuPrint(&CurrentMenu, pos, &data);
            redraw=false;
        }

        key=getch();
        if(key==224)
        {
            key=getch();
            if(key==72) // <arrow up> action
            {
                if(pos!=0 && pos < (CurrentMenu)->MSize)
                {
                    redraw = true;
                    --pos;
                }
            }
            else if(key==80) // <arrow down> action
            {
                if(pos>=0 && pos < (CurrentMenu)->MSize-1)
                {
                    redraw = true;
                    ++pos;
                }
            }
        }
        else if (key==13) // <enter> action
        {
            redraw = true;

            _lib_ret tmp;
            tmp = MenuAction(&CurrentMenu, file_out, &data, pos);

            if(tmp.menucmd == DEFAULT)
                pos = 0;
            else
                pos = tmp.menucmd;
        }
    }

    Books_Free(data.book);
    Users_Free(data.user);
    fclose(file_out);
}

void _initMenu(struct MenuLevel ** CurrentMenu)
{
    static struct MenuItem MainM_i[6] = {NULL, NULL, NULL, 0, NULL}; //MainM_i == MainMenu_items
    static struct MenuLevel MainM = {MainM_i, "Menu g\x88\xA2wne", 6}; // MainM == MainMenu
    *CurrentMenu = &MainM;

    strcpy(MainM_i[0].str, "Nowa biblioteka");
    MainM_i[0].funct = NewFile; // farg = 0

    strcpy(MainM_i[1].str, "Otw\xA2rz ostatni\xA5 bibliotek\xA9");
    MainM_i[1].funct = LoadFile;
    MainM_i[1].farg = 1;
    MainM_i[1].custom_print = MPrintLastFile;

    strcpy(MainM_i[2].str, "Otw\xA2rz bibliotek\xA9");
    MainM_i[2].funct = LoadFile; // farg = 0
    {
        static struct MenuItem ManageM_i[6] = {NULL, NULL, NULL, 0, NULL}; // ManageM_i == ManageMenu_items
        static struct MenuLevel ManageM = {&ManageM_i, "Zarz\xA5\x64zanie bibliotek\xA5", 6}; // ManageM == ManageMenu
        MainM_i[0].jump = &ManageM;
        MainM_i[1].jump = &ManageM;
        MainM_i[2].jump = &ManageM;

        strcpy(ManageM_i[0].str, "Ksi\xA5\xBEki");
        ManageM_i[0].funct = Books; // farg = 0

        strcpy(ManageM_i[1].str, "Czytelnicy");
        ManageM_i[1].funct = Users; // farg = 0

        strcpy(ManageM_i[2].str, "Wypo\xBEyczenia");
        {
            static struct MenuItem BorrowM_i[3] = {NULL, NULL, NULL, 0, NULL}; // BorrowM_i == BorrowMenu_items
            static struct MenuLevel BorrowM = {&BorrowM_i, "Zarz\xA5\x64zanie bibliotek\xA5 / Wypo\xBEyczenia", 3}; // BorrowM == BorrowMenu
            ManageM_i[2].jump = &BorrowM;

            strcpy(BorrowM_i[0].str, "Wypo\xBEycz ksia\xBEk\xA9");
            BorrowM_i[0].funct = BookBorrow; // farg = 0

            strcpy(BorrowM_i[1].str, "Zdaj ksia\xBEk\xA9");
            BorrowM_i[1].funct = BookReturn; // farg = 0

            strcpy(BorrowM_i[2].str, "<< Powr\xA2t");
            BorrowM_i[2].jump = &ManageM;
        }

        strcpy(ManageM_i[3].str, "(\x0F) Ustawienia biblioteki");
        {
            static struct MenuItem ManageSettingsM_i[2] = {NULL, NULL, NULL, 0, NULL}; // ManageSettingsM_i == ManageSettingsMenu_items
            static struct MenuLevel ManageSettingsM = {&ManageSettingsM_i, "Zarz\xA5\x64zanie bibliotek\xA5 / Ustawienia biblioteki", 2}; // ManageSettingsM == ManageSettingsMenu
            ManageM_i[3].jump = &ManageSettingsM;

            strcpy(ManageSettingsM_i[0].str, "Termin zwrotu ksi\xA5\xBE\x65k");
            ManageSettingsM_i[0].funct = LibSettings;
            strcpy(ManageSettingsM_i[1].str, "<< Powr\xA2t");
            ManageSettingsM_i[1].jump = &ManageM;
        }
        strcpy(ManageM_i[4].str, "<\x9E> Zamknij bibliotek\xA9");
        ManageM_i[4].funct = CloseLib; // farg = 0
        ManageM_i[4].jump = &MainM;


        strcpy(ManageM_i[5].str, "<\x9E> Zamknij bibliotek\xA9 i zako\xE4\x63z");
        ManageM_i[5].funct = CloseApp; // farg = 0
    }

    strcpy(MainM_i[3].str, "(\x0F) Ustawienia");
    MainM_i[3].funct = Settings;

    strcpy(MainM_i[4].str, "(?) O programie");
    MainM_i[4].funct = About; // farg = 0

    strcpy(MainM_i[5].str, "<\x9E> Zako\xE4\x63z");
    MainM_i[5].funct=CloseApp;
}
