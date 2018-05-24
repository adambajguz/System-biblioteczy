#include "./LibraryManageFunct.h"

MainConfig GetConfig(void)
{
    MainConfig tmp;
    FILE * config = fopen(MAIN_CONFIG_FILE, "rt");
    if(config)
    {
        fscanf(config, "%u", &tmp.AutoLoad);
        fscanf(config, "%u", &tmp.MaxDays);
        fscanf(config, "%u", &tmp.Books);
        fscanf(config, "%u", &tmp.Users);
        fscanf(config, "%u", &tmp.Borrowed);
        fclose(config);
    }
    else
    {
        tmp.AutoLoad=0;
        tmp.MaxDays=7;
        tmp.Books=1002;
        tmp.Users=1006;
        tmp.Borrowed=8;
    }

    return tmp;
}

_lib_ret Books(int arg, FILE ** libfile, struct _lib_data * data)
{
    _lib_ret ret;
    ret.menucmd=DEFAULT;

    BooksNode * selected2 = data->book;
    BooksCPNode * selected = NULL;

    enum FILTRE filtered=ALL;
    //books list init and filtering if access from BookBorrow or BookReturn function
    {
        enum FILTRE method = ALL;
        if(arg==1) // only when access to Books function from BookBorrow function
        {
            method=NOT_BORROWED;
            filtered=method;
        }
        else if (arg==2) // only when access to Books function from BookReturn function
        {
            method=BORROWED;
            filtered=method;
        }
#include "./code_snippets/Manage_Books_Filtre_engine.c"
    }

    enum SORT sorted = GetConfig().Books;
    enum SORT sortedway = sorted>1000?UPPER:LOWER;
    sorted-=sorted>1000?1000:0;
    BooksCP_Sort(selected, data->user, sorted, sortedway);

    char search_str[1024];
    unsigned char key;
    bool down=false;
    while(1)
    {
        clrscr();

        switch(arg)
        {
        case 1: // only when access to Books function from BookBorrow function
            setcolor(bfcolor(BLACK, WHITE));
            PrintHelp(BOOKS_SELECT);
            setcolor(bfcolor(BLACK, GRAY));
            printf("\n");
            PrintUMenuPos(".. / Wypo\xBEyczenia / Wypo\xBEycz ksi\xA5\xBEk\xA9 / Wybierz ksi\xA5\xBEk\xA9");
            break;
        case 2: // only when access to Books function from BookReturn function
            setcolor(bfcolor(BLACK, WHITE));
            PrintHelp(BOOKS_SELECT);
            setcolor(bfcolor(BLACK, GRAY));
            printf("\n");
            PrintUMenuPos(".. / Wypo\xBEyczenia / Zdaj ksi\xA5\xBEk\xA9 / Wybierz ksi\xA5\xBEk\xA9");
            break;

        default:
            setcolor(bfcolor(BLACK, WHITE));
            PrintHelp(BOOKS);
            setcolor(bfcolor(BLACK, GRAY));
            printf("\n");
            PrintUMenuPos("Zarz\xA5\x64zanie bibliotek\xA5 / Ksi\xA5\xBEki");
            break;
        };

#include "./code_snippets/Manage_Books_View.c"

        if(selected)
            BooksCP_ScrollListPrint(selected, data->user, 7, down, 4);
        else
        {
            ListBorder(false, true);
            printf("  Brak ksi\xA5\xBE\x65k.\n");
            ListBorder(false, false);
        }

#include "./code_snippets/Manage_ListSelCh.c"
        else if(key==13 && selected) // <enter> action - user details
        {
            switch(arg)
            {
            case 1: // only when access to Books function from BookBorrow or BookReturn function
            case 2:
                ret.book_node=selected->node;
                BooksCP_Free(&selected);
                return ret;
                break;

            default:
                if(BookDetails(libfile, data, &selected->node)) //if book deleted
                {
                    SaveLib(libfile, data);
                    BooksCP_Free(&selected);
                    enum FILTRE method = filtered;
#include "./code_snippets/Manage_Books_Filtre_engine.c"
                }
                break;
            };
        }
        else if(key==0)
        {
            key=getch();
            if(key==59 && selected) // <F1> action - sort
            {
#include "./code_snippets/Manage_Books_Sort.c"
            }
            else if(key==60) // <F2> action - filtre
            {
#include "./code_snippets/Manage_Books_Filtre.c"
            }
            else if(key==61) // <F3> action - search
            {
#include "./code_snippets/Manage_Books_Search.c"
            }
            else if(key==62) // <F4> action - add book
            {
#include "./code_snippets/Manage_Books_Add.c"
            }
        }

#include "./code_snippets/Manage_ESC.c"
    }

    BooksCP_Free(&selected);

    return ret;
}

_lib_ret Users(int arg, FILE ** libfile, struct _lib_data * data)
{
    _lib_ret ret;
    ret.menucmd=DEFAULT;

    UsersNode * selected2 = data->user;
    UsersCPNode * selected = NULL;

    //users list init
    {
        enum FILTRE method = ALL;
#include "./code_snippets/Manage_Users_Filtre_engine.c"
    }

    enum SORT sorted = GetConfig().Users;
    enum SORT sortedway = sorted>1000?UPPER:LOWER;
    sorted-=sorted>1000?1000:0;
    UsersCP_Sort(selected, sorted, sortedway);

    char search_str[1024];
    enum FILTRE filtered=ALL;
    unsigned char key;
    bool down=false;
    while(1)
    {
        clrscr();

        switch(arg)
        {
        case 1: // only when access to Books function from BookBorrow function
            setcolor(bfcolor(BLACK, WHITE));
            PrintHelp(USERS_SELECT);
            setcolor(bfcolor(BLACK, GRAY));
            printf("\n");
            PrintUMenuPos(".. / Wypo\xBEyczenia / Wypo\xBEycz ksi\xA5\xBEk\xA9 / Wybierz czytelnika");
            setDcolor();
            break;

        default:
            setcolor(bfcolor(BLACK, WHITE));
            PrintHelp(USERS);
            setcolor(bfcolor(BLACK, GRAY));
            printf("\n");
            PrintUMenuPos("Zarz\xA5\x64zanie bibliotek\xA5 / Czytelnicy");
            setDcolor();
            break;
        };

#include "./code_snippets/Manage_Users_View.c"

        if(selected)
            UsersCP_ScrollListPrint(selected, 8, down, data->cfg.maxBorrowDays, 3);
        else
        {
            ListBorder(false, true);
            printf("  Brak czytelnik\xA2w.\n");
            ListBorder(false, false);
        }

#include "./code_snippets/Manage_ListSelCh.c"
        else if(key==13 && selected) // <enter> action - user details
        {
            switch(arg)
            {
            case 1: // only when access to Books function from BookBorrow function
                ret.user_node=selected->node;

                UsersCP_Free(&selected);
                return ret;
                break;

            default:
                if(UserDetails(libfile, data, &selected->node)) // if user deleted
                {
                    UsersCP_Free(&selected);
                    enum FILTRE method = filtered;
#include "./code_snippets/Manage_Users_Filtre_engine.c"
                }
                break;
            };
        }
        else if(key==0)
        {
            key=getch();
            if(key==59 && selected) // <F1> action - sort
            {
#include "./code_snippets/Manage_Users_Sort.c"
            }
            else if(key==60) // <F2> action - filtre
            {
#include "./code_snippets/Manage_Users_Filtre.c"
            }
            else if(key==61) // <F3> action - search
            {
#include "./code_snippets/Manage_Users_Search.c"
            }
            else if(key==62) // <F4> action - add user
            {
#include "./code_snippets/Manage_Users_Add.c"
            }

        }
#include "./code_snippets/Manage_ESC.c"
    }

    UsersCP_Free(&selected);

    return ret;
}

bool BookDetails(const FILE ** libfile, const struct _lib_data * data, BooksNode ** selectedB)
{
    unsigned char key;
    while(1)
    {
        clrscr();

        setcolor(bfcolor(BLACK, WHITE));
        PrintHelp(BOOKS_SINGLE);
        setcolor(bfcolor(BLACK, GRAY));
        printf("\n");
        PrintUMenuPos(".. / Ksi\xA5\xBEki / Szczeg\xA2\x88y");
        printf("\n ");
        setDcolor();

        Books_PrintDetails(*selectedB, data->user, data->cfg.maxBorrowDays);

        key=getch();
        if(key==0)
        {
            key=getch();
            if(key==59) // <F1> action - edit book
            {
#include "./code_snippets/Manage_Books_Edit.c"
            }
            else if(key==60) // <F2> action - remove book
            {
                if(RemoveBook(data, *selectedB))
                {
                    *selectedB=data->book;
#if SLEEP_PAUSE == 0
                    Sleep(ACTION_MESSAGE_TIME);
#else
                    ContinuePause();
#endif // SLEEP_PAUSE
                    return true;
                }
                else
#if SLEEP_PAUSE == 0
                    Sleep(ACTION_MESSAGE_TIME);
#else
                    ContinuePause();
#endif // SLEEP_PAUSE
            }
        }
        else if(key==27) // <ESC> action
            return false;
    }
}

bool UserDetails(const FILE ** libfile, const struct _lib_data * data, UsersNode ** selectedU)
{
    BorrowedNode * selected2 = (*selectedU)->data.borrowed;
    BorrowedCPNode * selected = NULL;

    //borrowed list init
    {
        enum FILTRE method = ALL;
#include "./code_snippets/Manage_Borrowed_Filtre_engine.c"
    }

    enum SORT sorted = GetConfig().Borrowed;
    enum SORT sortedway = sorted>1000?UPPER:LOWER;
    sorted-=sorted>1000?1000:0;
    BorrowedCP_Sort(selected, data->book, sorted, sortedway);

    enum FILTRE filtered=ALL;
    bool down=false;
    unsigned char key;
    while(1)
    {
        clrscr();

        setcolor(bfcolor(BLACK, WHITE));
        PrintHelp(USERS_SINGLE);
        setcolor(bfcolor(BLACK, GRAY));
        printf("\n");
        PrintUMenuPos(".. / Czytelnicy / Szczeg\xA2\x88y");
        printf("\n ");
        setDcolor();

        PrintU2MenuPos("Dane czytelnika:");
        Users_PrintDetails(*selectedU, data->cfg.maxBorrowDays);
        printf("\n ");
        PrintU2MenuPos("Historia wypo\xBEyczonych ksi\xA5\xBE\x65k:");

#include "./code_snippets/Manage_Borrowed_View.c"

        if(selected)
            BorrowedCP_ScrollListPrint(selected, data->book, 4, down, 5);
        else
        {
            ListBorder(false, true);
            printf("  Brak wypo\xBEyczonych ksi\xA5\xBE\x65k.\n");
            ListBorder(false, false);
        }
#include "./code_snippets/Manage_ListSelCh.c"
        else if(key==0)
        {
            key=getch();
            if(key==59) // <F1> action - edit user
            {
#include "./code_snippets/Manage_Users_Edit.c"
            }
            else if(key==60) // <F2> action - remove user
            {
                if(RemoveUser(data, *selectedU))
                {
                    SaveLib(libfile, data);
                    *selectedU=data->user;
#if SLEEP_PAUSE == 0
                    Sleep(ACTION_MESSAGE_TIME);
#else
                    ContinuePause();
#endif // SLEEP_PAUSE

                    BorrowedCP_Free(&selected);
                    return true;
                }
                else
#if SLEEP_PAUSE == 0
                    Sleep(ACTION_MESSAGE_TIME);
#else
                    ContinuePause();
#endif // SLEEP_PAUSE
            }
            else if(key==61) // <F3> action - sort borrowed book
            {
#include "./code_snippets/Manage_Borrowed_Sort.c"
            }
            else if(key==62) // <F4> action - filtre borrowed book
            {
#include "./code_snippets/Manage_Borrowed_Filtre.c"
            }
            else if(key==63 && selected) // <F5> action - return borrowed book
            {
                printf("\n ");
                PrintDoubleLine(10);
                const BorrowedNode * bt = selected->node;
                if(!bt->data.returnTime)
                {
#include "./code_snippets/Manage_BookReturn.c"
                }
                else
                {
                    setcolor(bfcolor(BLACK, LIGHTRED));
                    printf("\n Ksi\xA5\xBEka jest ju\xBE zdana!");
                    setDcolor();
                }
#if SLEEP_PAUSE == 0
                Sleep(ACTION_MESSAGE_TIME);
#else
                ContinuePause();
#endif // SLEEP_PAUSE
            }
        }
        else if(key==27) // <ESC> action
        {
            break;
        }
    }

    BorrowedCP_Free(&selected);
    return false;
}

bool FiltreBorrowed(const enum FILTRE method, const BorrowedNode * selected2, const unsigned int max_borrow_days)
{
    if(method==ALL)
        return 1;
    else if(method==BORROWED && !selected2->data.returnTime)
        return 1;
    else if(method==RETURNED && selected2->data.returnTime)
        return 1;
    else if (method==BORROWED_LONG && !selected2->data.returnTime)
        if( (time(NULL) - selected2->data.borrowTime) > (max_borrow_days*3600*24) )
            return 1;

    return 0;
}

void AddBook(struct _lib_data * data)
{
    clrscr();
    //PrintHelp(FILENAME_LOAD);
    setcolor(bfcolor(BLACK, GRAY));
    printf("\n");
    PrintUMenuPos(".. / Ksi\xA5\xBEki / Nowa ksi\xA5\xBEka");
    printf("\n");
    setDcolor();

    BooksNode tmp;
    tmp.data.UID=data->cfg.BUIDnext;

    printf("Podaj identyfikator ksi\xA5\xBEki: ");
    get1024(&tmp.data.id);

    printf("Podaj tytu\x88 ksi\xA5\xBEki: ");
    get1024(&tmp.data.title);

    printf("Podaj imie autora ksi\xA5\xBEki: ");
    get1024(&tmp.data.authorsName);

    printf("Podaj nazwisko autora ksi\xA5\xBEki: ");
    get1024(&tmp.data.authorsSurname);

    char buf[6];
    printf("Podaj rok wydania ksi\xA5\xBEki (liczb\xA9): ");
    fgets(buf, 6, stdin);
    tmp.data.year=atoi(buf);

    clrscr();
    setcolor(bfcolor(BLACK, GRAY));
    printf("\n");
    PrintUMenuPos(".. / Ksi\xA5\xBEki / Nowa ksi\xA5\xBEka");
    printf("\n");
    setDcolor();

    Books_PrintDetails(&tmp, NULL, data->cfg.maxBorrowDays);

    printf("\n ");
    PrintDoubleLine(10);

    YN_option(Czy na pewno chcesz doda\x86 t\xA9 ksi\xA5\xBEk\xA9 do biblioteki,
    {
        Books_AddBegin(&data->book, tmp.data);
        ++data->cfg.BUIDnext;
        //clrscr();
        setcolor(bfcolor(BLACK, LIGHTGREEN));
        printf("\n\n Pomy\x98lnie dodano now\xA5 ksi\xA5\xBEk\xA9 do biblioteki!");
        setDcolor();
    },
    {
        //clrscr();
        setcolor(bfcolor(BLACK, LIGHTRED));
        printf("\n\n Nie dodano ksi\xA5\xBEki do biblioteki!");
        setDcolor();
    })
}

int RemoveBook(struct _lib_data * data, BooksNode * selected)
{
    clrscr();
    //PrintHelp(FILENAME_LOAD);
    setcolor(bfcolor(BLACK, GRAY));
    printf("\n");
    PrintUMenuPos(".. / Czytelnicy / Usu\xE4 ksi\xA5\xBEk\xA9");
    printf("\n");
    setDcolor();

    Books_PrintDetails(selected, data->user, data->cfg.maxBorrowDays);

    printf("\n ");
    PrintDoubleLine(10);

    YN_option(Czy na pewno chcesz usun\xA5\x86 t\xA9 ksi\xA5\xBEk\xA9 z biblioteki,
    {
        Books_Remove(&data->book, selected);
        //clrscr();
        setcolor(bfcolor(BLACK, LIGHTGREEN));
        printf("\n\n Pomy\x98lnie usuni\xA9to ksi\xA5\xBEk\xA9 z biblioteki!");
        setDcolor();
        return 1;
    },
    {
        //clrscr();
        setcolor(bfcolor(BLACK, LIGHTRED));
        printf("\n\n Nie usuni\xA9to ksi\xA5\xBEki z biblioteki!");
        setDcolor();
        return 0;
    })
}

bool SearchBook(const enum FILTRE method, BooksNode * selected2, const char str[1024])
{
    if(method==ALL)
        return 1;
    else if(method==ID)
    {
        if(!strcmp(selected2->data.id, str))
            return 1;
    }
    else if(method==TITLE)
    {
        if(!strcmp(selected2->data.title, str))
            return 1;
    }
    else if(method==NAME)
    {
        if(!strcmp(selected2->data.authorsName, str))
            return 1;
    }
    else if(method==SURNAME)
    {
        if(!strcmp(selected2->data.authorsSurname, str))
            return 1;
    }
    return 0;
}

bool FiltreBook(const enum FILTRE method, const BooksNode * selected2, const UsersNode * users, const unsigned int max_borrow_days)
{
    if(method==ALL)
        return 1;
    else if(method==BORROWED || method==BORROWED_LONG)
    {
        UsersNode * usr = Users_SearchWhoBorrowedByBUID(users, selected2->data.UID);
        if(usr && method==BORROWED_LONG)
        {
            BorrowedNode * b = Borrowed_SearchByBUID(usr->data.borrowed, selected2->data.UID);
            if( !b->data.returnTime && (time(NULL) - b->data.borrowTime) > (max_borrow_days*3600*24) )
                return 1;
        }
        else if(usr && method==BORROWED)
            return 1;
    }
    else if(method==NOT_BORROWED && !Users_SearchWhoBorrowedByBUID(users, selected2->data.UID))
        return 1;

    return 0;
}

void AddUser(struct _lib_data * data)
{
    clrscr();
    //PrintHelp(FILENAME_LOAD);
    setcolor(bfcolor(BLACK, GRAY));
    printf("\n");
    PrintUMenuPos(".. / Czytelnicy / Nowy czytelnik");
    printf("\n");
    setDcolor();

    UsersNode tmp;
    tmp.data.borrowed=NULL;
    tmp.data.UID=data->cfg.UUIDnext;

    printf("Podaj imie: ");
    get1024(&tmp.data.name);

    printf("Podaj nazwisko: ");
    get1024(&tmp.data.surname);

    printf("Podaj adres: ");
    get1024(&tmp.data.address);

    printf("Podaj PESEL (np. 00123456789): ");
    get(tmp.data.pesel, 14);

    printf("Podaj e-mail: ");
    get1024(&tmp.data.email);

    printf("Podaj numer telefonu (np. +48123456789): ");
    get(tmp.data.telephone, 14);

    clrscr();
    printf("\n");
    PrintUMenuPos(".. / Czytelnicy / Nowy czytelnik");
    printf("\n");
    Users_PrintDetails(&tmp, data->cfg.maxBorrowDays);

    printf("\n ");
    PrintDoubleLine(10);

    YN_option(Czy na pewno chcesz doda\x86 tego czytelnika do biblioteki,
    {
        Users_AddBegin(&data->user, tmp.data);
        ++data->cfg.UUIDnext;
        //clrscr();
        setcolor(bfcolor(BLACK, LIGHTGREEN));
        printf("\n\n Pomy\x98lnie dodano nowego czytelnika do biblioteki!");
        setDcolor();
    },
    {
        //clrscr();
        setcolor(bfcolor(BLACK, LIGHTRED));
        printf("\n\n Nie dodano nowego czytelnika do biblioteki!");
        setDcolor();
    })
}

int RemoveUser(struct _lib_data * data, UsersNode * selected)
{
    clrscr();
    //PrintHelp(FILENAME_LOAD);
    setcolor(bfcolor(BLACK, GRAY));
    printf("\n");
    PrintUMenuPos(".. / Czytelnicy / Usu\xE4 czytelnika");
    printf("\n");
    setDcolor();

    Users_PrintDetails(selected, data->cfg.maxBorrowDays);

    printf("\n ");
    PrintDoubleLine(10);

    YN_option(Czy na pewno chcesz usun\xA5\x86 tego czytelnika z biblioteki,
    {
        Users_Remove(&data->user, selected);
        //clrscr();
        setcolor(bfcolor(BLACK, LIGHTGREEN));
        printf("\n\n Pomy\x98lnie usuni\xA9to czytelnika z biblioteki!");
        setDcolor();
        return 1;
    },
    {
        //clrscr();
        setcolor(bfcolor(BLACK, LIGHTRED));
        printf("\n\n Nie usuni\xA9to czytelnika z biblioteki!");
        setDcolor();
        return 0;
    })
}

bool SearchUser(const enum FILTRE method, UsersNode * selected2, const char str[1024])
{
    if(method==ALL)
        return 1;
    else if(method==NAME)
    {
        if(!strcmp(selected2->data.name, str))
            return 1;
    }
    else if(method==SURNAME)
    {
        if(!strcmp(selected2->data.surname, str))
            return 1;
    }
    else if(method==PESEL)
    {
        if(!strcmp(selected2->data.pesel, str))
            return 1;
    }
    return 0;
}

bool FiltreUser(const enum FILTRE method, const BorrowedNode * selected2, const unsigned int max_borrow_days)
{
    if(method==ALL)
        return 1;
    else if(method==BORROWED_LONG)
        if(Borrowed_BAfterSize(selected2, max_borrow_days))
            return 1;

    return 0;
}

_lib_ret BookBorrow(int arg, FILE ** libfile, struct _lib_data * data)
{
    _lib_ret ret;
    ret.menucmd=DEFAULT;

    _lib_ret book_ret = Books(1, libfile, data);
    if(book_ret.menucmd==DEFAULT)
    {
        UsersNode * st = Users_SearchWhoBorrowedByBUID(data->user, book_ret.book_node->data.UID);
        if(!st) // if book is not borrowed
        {
            _lib_ret user_ret = Users(1, libfile, data);
            if(user_ret.menucmd==DEFAULT)
            {
                clrscr();

                //setcolor(bfcolor(BLACK, WHITE));
                //PrintHelp(USERS_SELECT);
                //setcolor(bfcolor(BLACK, GRAY));
                printf("\n");
                PrintUMenuPos(".. / Wypo\xBEyczenia / Wypo\xBEycz ksi\xA5\xBEk\xA9");
                setDcolor();

                printf("\n ");
                PrintU2MenuPos("#1 Wybrana ksi\xA5\xBEka do wypo\xBEyczenia:");
                Books_ListPrintSingle(book_ret.book_node, NULL, false, false, true);


                printf("\n ");
                PrintU2MenuPos("#2 Wybrany czytelnik:");
                Users_ListPrintSingle(user_ret.user_node, false, data->cfg.maxBorrowDays);

                printf("\n ");
                PrintDoubleLine(10);

                YN_option(Czy na pewno chcesz wypo\xBEyczy\x86 ksi\xA5\xBEk\xA9 temu czytelnikowi,
                {
                    BorrowedData tmp;
                    tmp.UID = book_ret.book_node->data.UID;
                    time(&tmp.borrowTime);
                    tmp.returnTime = 0;
                    Borrowed_AddBegin(&(user_ret.user_node->data.borrowed), tmp);


                    //clrscr();
                    setcolor(bfcolor(BLACK, LIGHTGREEN));
                    printf("\n\n Pomy\x98lnie wypo\xBEyczono ksi\xA5\xBEk\xA9 z biblioteki!");
                    setDcolor();
                    SaveLib(libfile, data);
                },
                {
                    //clrscr();
                    setcolor(bfcolor(BLACK, LIGHTRED));
                    printf("\n\n Nie wypo\xBEyczono ksi\xA5\xBEki z biblioteki!");
                    setDcolor();
                })
#if SLEEP_PAUSE == 0
                Sleep(ACTION_MESSAGE_TIME);
#else
                ContinuePause();
#endif // SLEEP_PAUSE
            }
//            else
//            {
//                //clrscr();
//                setcolor(bfcolor(BLACK, LIGHTRED));
//                printf("\n\n Anulowano wypo\xBEyczanie ksi\xA5\xBEki z biblioteki!");
//                setDcolor();
//            }
        }
        else // if somehow user tried to borrow book that was already borrowed
        {
            //clrscr();
            setcolor(bfcolor(BLACK, LIGHTRED));
            printf("\n\n Ksi\xA5\xBEka jest ju\xBE wypo\xBEyczona z biblioteki!");
            setDcolor();
#if SLEEP_PAUSE == 0
            Sleep(ACTION_MESSAGE_TIME);
#else
            ContinuePause();
#endif // SLEEP_PAUSE
        }
    }
//    else
//    {
//        //clrscr();
//        setcolor(bfcolor(BLACK, LIGHTRED));
//        printf("\n\n Anulowano wypo\xBEyczanie ksi\xA5\xBEki z biblioteki!");
//        setDcolor();
//    }
//#if SLEEP_PAUSE == 0
//    Sleep(ACTION_MESSAGE_TIME);
//#else
//    ContinuePause();
//#endif // SLEEP_PAUSE
    return ret;
}

_lib_ret BookReturn(int arg, FILE ** libfile, struct _lib_data * data)
{
    _lib_ret ret;
    ret.menucmd=DEFAULT;

    _lib_ret book_ret = Books(2, libfile, data);
    if(book_ret.menucmd==DEFAULT)
    {
        clrscr();

        //setcolor(bfcolor(BLACK, WHITE));
        //PrintHelp(USERS_SELECT);
        //setcolor(bfcolor(BLACK, GRAY));
        printf("\n");
        PrintUMenuPos(".. / Wypo\xBEyczenia / Zdaj ksi\xA5\xBEk\xA9");
        setDcolor();

        printf("\n ");
        PrintU2MenuPos("#1 Wybrana ksi\xA5\xBEka do zdania:");
        Books_ListPrintSingle(book_ret.book_node, data->user, false, false, true);

        printf("\n ");
        PrintU2MenuPos("#2 wypo\xBEyczona przez:");

        const UsersNode * st = Users_SearchWhoBorrowedByBUID(data->user, book_ret.book_node->data.UID);
        if(st) // if book is borrowed
        {
            Users_ListPrintSingle(st, false, data->cfg.maxBorrowDays);

            printf("\n ");
            PrintDoubleLine(10);
            const BorrowedNode * bt = Borrowed_SearchByBUID(st->data.borrowed, book_ret.book_node->data.UID);
#include "./code_snippets/Manage_BookReturn.c"
#if SLEEP_PAUSE == 0
            Sleep(ACTION_MESSAGE_TIME);
#else
            ContinuePause();
#endif // PAUSE
        }
        else // if somehow user tried to return book that was not borrowed
        {
            //clrscr();
            setcolor(bfcolor(BLACK, LIGHTRED));
            printf("\n\n Ksi\xA5\xBEka nie jest wypo\xBEyczona z biblioteki!");
            setDcolor();
#if SLEEP_PAUSE == 0
            Sleep(ACTION_MESSAGE_TIME);
#else
            ContinuePause();
#endif // SLEEP_PAUSE
        }
    }
//    else
//    {
//        //clrscr();
//        setcolor(bfcolor(BLACK, LIGHTRED));
//        printf("\n\n Anulowano zdawanie ksi\xA5\xBEki do biblioteki!");
//        setDcolor();
//    }
//#if SLEEP_PAUSE == 0
//    Sleep(ACTION_MESSAGE_TIME);
//#else
//    ContinuePause();
//#endif // SLEEP_PAUSE
    return ret;
}

void SaveLib(const FILE * libfile, const struct _lib_data * data)
{
    libfile=fopen(data->cfg.libname, "wt");

    fprintf(libfile, ".LIBST\n");

    fprintf(libfile, ".CONFIG >\n");
    fprintf(libfile, "%u\n%u\n%u\n", data->cfg.maxBorrowDays, data->cfg.BUIDnext, data->cfg.UUIDnext);
    fprintf(libfile, ".CONFIG <\n");

    fprintf(libfile, ".BOOKS >\n");
    fflush(libfile);
    Books_Save(data->book, libfile);
    fprintf(libfile, ".BOOKS <\n");

    fprintf(libfile, ".USERS >\n");
    fflush(libfile);
    Users_Save(data->user, libfile);
    fprintf(libfile, ".USERS <\n");

    fprintf(libfile, ".LIBEN\n");
    fflush(libfile);
    fclose(libfile);
}

int LoadLib(const FILE * libfile, struct _lib_data * data)
{
    char buf[32], * er;
    unsigned short fchk=0; // variable only for simple file integrity verification process

    while(!feof(libfile))
    {
        if(er=fgets(buf, 32, libfile))
        {
            if(!strcmp(buf, ".LIBST\n") && fchk==0)
                ++fchk; //1
            else if (!strcmp(buf, ".CONFIG >\n") && fchk==1)
            {
                ++fchk; //2
                fgets(buf, 32, libfile);
                data->cfg.maxBorrowDays=atoi(buf);

                fgets(buf, 32, libfile);
                data->cfg.BUIDnext=atoi(buf);

                fgets(buf, 32, libfile);
                data->cfg.UUIDnext=atoi(buf);
            }
            else if (!strcmp(buf, ".CONFIG <\n") && fchk==2)
                ++fchk; //3
            else if (!strcmp(buf, ".BOOKS >\n") && fchk==3)
            {
                unsigned short err;
                err=Books_Load(&data->book, libfile);

                if(err==1) //OK
                    ++fchk; //4
                else if(err==2) // No .BOOKS <
                {
                    fchk=7;
                    break;
                }
                else // Books read error
                {
                    fchk=8;
                    break;
                }
            }
            else if (!strcmp(buf, ".USERS >\n") && fchk==4)
            {
                unsigned short err;
                err=Users_Load(&data->user, libfile);

                if(err==2) // OK
                {
                    ++fchk; //5
                }
                else if(err==3) // No .BORROWED
                {
                    fchk=12;
                    break;
                }
                else if(err==4) // Borrowed read error
                {
                    fchk=13;
                    break;
                }
                else if(err==5) // no Users <
                {
                    fchk=9;
                    break;
                }
                else // Users read error
                {
                    fchk=10;
                    break;
                }

            }
            else if (!strcmp(buf, ".LIBEN\n") && fchk==5)
                ++fchk; //6
            else
                break;
        }
        else
            break;
    }

    return fchk;
}

_lib_ret LibSettings(int arg, FILE ** libfile, struct _lib_data * data)
{
    _lib_ret ret;
    ret.menucmd=DEFAULT;

    unsigned int MaxDays = data->cfg.maxBorrowDays;
    char key;
    while(1)
    {
        clrscr();

        printf("\n");
        setcolor(bfcolor(BLACK, GRAY));
        PrintUMenuPos(".. / Ustawienia biblioteki / Termin zwrotu ksi\xA5\xBE\x65k");
        setDcolor();

        setcolor(bfcolor(BLACK, WHITE));
        PrintHelp(SETTINGS);
        setDcolor();

        printf("\n ");
        setcolor(bfcolor(LIGHTGRAY, BLACK));
        printf(" Termin zwrotu ksi\xA5\xBE\x65k  [ %d %s] \n", MaxDays, MaxDays==1?"dzie\xE4":"dni");
        setDcolor();

        key=getch();
        if(key==13)
        {
            YN_option(Czy na pewno chcesz zapisac ustawienia biblioteki,
            {
                //clrscr();
                data->cfg.maxBorrowDays=MaxDays;
                setcolor(bfcolor(BLACK, LIGHTGREEN));
                printf("\n\n Pomy\x98lnie zapisano ustawienia biblioteki!");
                setDcolor();
                ContinuePause();

            },
            {
                //clrscr();
                setcolor(bfcolor(BLACK, LIGHTRED));
                printf("\n\n Nie zapisano ustawie\xE4 biblioteki!");
                setDcolor();
                ContinuePause();
            })
        }
        else if(key==45) // <-> key
        {
            if(MaxDays>1)
                --MaxDays;
        }
        else if(key==61||key==43) // <+or=> action
        {
            if(MaxDays<365)
                ++MaxDays;
        }
        else if (key==27) // <ESC> key
        {
            break;
        }
    }
    SaveLib(libfile, data);

    return ret;
}
