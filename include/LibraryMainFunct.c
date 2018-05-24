#include "./LibraryMainFunct.h"

void SetConfig(const MainConfig cfg)
{
    FILE * config = fopen(MAIN_CONFIG_FILE, "wt");
    if(config)
    {
        fprintf(config, "%u ", cfg.AutoLoad);
        fprintf(config, "%u ", cfg.MaxDays);
        fprintf(config, "%u ", cfg.Books);
        fprintf(config, "%u ", cfg.Users);
        fprintf(config, "%u ", cfg.Borrowed);
        fclose(config);
    }
}

_lib_ret Settings(int arg, FILE ** out, struct _lib_data * data)
{
    _lib_ret ret;
    ret.menucmd=DEFAULT;

    MainConfig tmp=GetConfig();

    struct ChoiceLevel * CurrentChoice[CCHOICE_SIZE]= {NULL};
    if(arg!=4)
    {
        static struct ChoiceItem Set_Auto_i[2] = {NULL, 0};
        static struct ChoiceLevel Set_Auto = {Set_Auto_i, SetConfig, "Automatyczne wczytywanie ostatniego pliku", 2};
        CurrentChoice[0] = &Set_Auto;

        strcpy(Set_Auto_i[0].str, "Nieaktywne");
        Set_Auto_i[0].val = 0;

        strcpy(Set_Auto_i[1].str, "Aktywne");
        Set_Auto_i[1].val = 1;

        static struct ChoiceItem Set_Book_i[10] = {NULL, 0};
        static struct ChoiceLevel Set_Book = {Set_Book_i, SetConfig, "Domy\x98lne sortowanie ksi\xA5\xBE\x65k              ", 10};
        CurrentChoice[1] = &Set_Book;

        strcpy(Set_Book_i[0].str, "ID rosn\xA5\x63o");
        Set_Book_i[0].val = 1000+sID;

        strcpy(Set_Book_i[1].str, "ID malej\xA5\x63o");
        Set_Book_i[1].val = sID;

        strcpy(Set_Book_i[2].str, "TYTU\x9D rosn\xA5\x63o");
        Set_Book_i[2].val = 1000+sTITLE;

        strcpy(Set_Book_i[3].str, "TYTU\x9D malej\xA5\x63o");
        Set_Book_i[3].val = sTITLE;

        strcpy(Set_Book_i[4].str, "IMI\xA8 AUTORA rosn\xA5\x63o");
        Set_Book_i[4].val = 1000+sNAME;

        strcpy(Set_Book_i[5].str, "IMI\xA8 AUTORA malej\xA5\x63o");
        Set_Book_i[5].val = sNAME;

        strcpy(Set_Book_i[6].str, "NAZWISKO AUTORA rosn\xA5\x63o");
        Set_Book_i[6].val = 1000+sSURNAME;

        strcpy(Set_Book_i[7].str, "NAZWISKO AUTORA malej\xA5\x63o");
        Set_Book_i[7].val = sSURNAME;

        strcpy(Set_Book_i[8].str, "STAN rosn\xA5\x63o");
        Set_Book_i[8].val = 1000+sBORROWED;

        strcpy(Set_Book_i[9].str, "STAN malej\xA5\x63o");
        Set_Book_i[9].val = sBORROWED;


        static struct ChoiceItem Set_Borrowed_i[10] = {NULL, 0};
        static struct ChoiceLevel Set_Borrowed = {Set_Borrowed_i, SetConfig, "Domy\x98lne sortowanie wypo\xBEyczonych ksi\xA5\xBE\x65k", 10};
        CurrentChoice[2] = &Set_Borrowed;

        strcpy(Set_Borrowed_i[0].str, "ID rosn\xA5\x63o");
        Set_Borrowed_i[0].val = 1000+sID;

        strcpy(Set_Borrowed_i[1].str, "ID malej\xA5\x63o");
        Set_Borrowed_i[1].val = sID;

        strcpy(Set_Borrowed_i[2].str, "TYTU\x9D rosn\xA5\x63o");
        Set_Borrowed_i[2].val = 1000+sTITLE;

        strcpy(Set_Borrowed_i[3].str, "TYTU\x9D malej\xA5\x63o");
        Set_Borrowed_i[3].val = sTITLE;

        strcpy(Set_Borrowed_i[4].str, "IMI\xA8 AUTORA rosn\xA5\x63o");
        Set_Borrowed_i[4].val = 1000+sNAME;

        strcpy(Set_Borrowed_i[5].str, "IMI\xA8 AUTORA malej\xA5\x63o");
        Set_Borrowed_i[5].val = sNAME;

        strcpy(Set_Borrowed_i[6].str, "NAZWISKO AUTORA rosn\xA5\x63o");
        Set_Borrowed_i[6].val = 1000+sSURNAME;

        strcpy(Set_Borrowed_i[7].str, "NAZWISKO AUTORA malej\xA5\x63o");
        Set_Borrowed_i[7].val = sSURNAME;

        strcpy(Set_Borrowed_i[8].str, "TERMIN ZDANIA od zdanych");
        Set_Borrowed_i[8].val = 1000+sBORROWED;

        strcpy(Set_Borrowed_i[9].str, "TERMIN ZDANIA od wyp.");
        Set_Borrowed_i[9].val = sBORROWED;


        static struct ChoiceItem Set_Users_i[6] = {NULL, 0};
        static struct ChoiceLevel Set_Users = {Set_Users_i, SetConfig, "Domy\x98lne sortowanie czytelnik\xA2w          ", 6};
        CurrentChoice[3] = &Set_Users;

        strcpy(Set_Users_i[0].str, "IMI\xA8 rosn\xA5\x63o");
        Set_Users_i[0].val = 1000+sNAME; // what = 4

        strcpy(Set_Users_i[1].str, "IMI\xA8 malej\xA5\x63o");
        Set_Users_i[1].val = sNAME; // what = 4

        strcpy(Set_Users_i[2].str, "NAZWISKO rosn\xA5\x63o");
        Set_Users_i[2].val = 1000+sSURNAME; // what = 4

        strcpy(Set_Users_i[3].str, "NAZWISKO malej\xA5\x63o");
        Set_Users_i[3].val = sSURNAME; // what = 4

        strcpy(Set_Users_i[4].str, "PESEL rosn\xA5\x63o");
        Set_Users_i[4].val = 1000+sPESEL; // what = 4

        strcpy(Set_Users_i[5].str, "PESEL malej\xA5\x63o");
        Set_Users_i[5].val = sPESEL; // what = 4


        static struct ChoiceItem Set_Days_i[365] = {NULL, 0};
        static struct ChoiceLevel Set_Days = {Set_Days_i, SetConfig, "Domy\x98lny termin zwrotu                   ", 365};
        CurrentChoice[4] = &Set_Days;

        strcpy(Set_Days_i[0].str, "1 dzie\xE4");
        Set_Days_i[0].val = 1;

        for (int i=1; i<365; ++i)
        {
            itoa(i+1, Set_Days_i[i].str, 10);
            strcat(Set_Days_i[i].str, " dni");
            Set_Days_i[i].val = i+1;
        }
    }


    unsigned int setting = 0;
    unsigned int pos[CCHOICE_SIZE]= {0};
    pos[0]=tmp.AutoLoad;
    pos[1]=tmp.Books>1000?tmp.Books-1000:tmp.Books+1;
    pos[2]=tmp.Borrowed>1000?tmp.Borrowed-1000:tmp.Borrowed+1;
    pos[3]=tmp.Users>1000?tmp.Users-1000:tmp.Users+1;
    if(pos[3]==sPESEL)
        pos[3]-=6;
    else
        pos[3]-=4;
    pos[4]=tmp.MaxDays-1;

    unsigned char key;
    bool redraw = true;
    while(1)
    {
        if(redraw)
        {
            ChoicePrint(CurrentChoice, CCHOICE_SIZE, pos, setting);
            redraw=false;
        }

        key=getch();

        if(key==224)
        {
            key=getch();
            if(key==72) // <arrow up> action
            {
                if(setting!=0 && setting < CCHOICE_SIZE)
                {
                    redraw = true;
                    --setting;
                }
            }
            else if(key==80) // <arrow down> action
            {
                if(setting>=0 && setting < CCHOICE_SIZE-1)
                {
                    redraw = true;
                    ++setting;
                }
            }
        }
        else if(key==45) // <-> action
        {
//                if(pos[setting] == 0)
//                    pos[setting]=(CurrentChoice[setting])->MSize-1;
//                else
//                    --pos[setting];
            if(pos[setting]!=0 && pos[setting] < (CurrentChoice[setting])->MSize)
            {
                redraw = true;
                --pos[setting];
            }
        }
        else if(key==61||key==43) // <+or=> action
        {
//                if(pos[setting] == (CurrentChoice[setting])->MSize-1)
//                    pos[setting]=0;
//                else
//                    ++pos[setting];
            if(pos[setting]>=0 && pos[setting] < (CurrentChoice[setting])->MSize-1)
            {
                redraw = true;
                ++pos[setting];
            }
        }
        else if (key==13) // <enter> action
        {
            redraw = true;

            YN_option(Czy na pewno chcesz zapisac ustawienia biblioteki,
            {
                for(int i=0; i<CCHOICE_SIZE; ++i)
                {
                    switch(i)
                    {
                    case 0:
                        tmp.AutoLoad=CurrentChoice[i]->MItems[pos[i]].val;
                        break;

                    case 1:
                        tmp.Books=CurrentChoice[i]->MItems[pos[i]].val;
                        break;

                    case 2:
                        tmp.Borrowed=CurrentChoice[i]->MItems[pos[i]].val;
                        break;

                    case 3:
                        tmp.Users=CurrentChoice[i]->MItems[pos[i]].val;
                        break;

                    case 4:
                        tmp.MaxDays=CurrentChoice[i]->MItems[pos[i]].val;
                        break;
                    };
                }
                SetConfig(tmp);
                setcolor(bfcolor(BLACK, LIGHTGREEN));
                printf("\n\n Pomy\x98lnie zapisano ustawienia!");
                setDcolor();
                ContinuePause();
            },
            {
                setcolor(bfcolor(BLACK, LIGHTRED));
                printf("\n\n Nie zapisano ustawie\xE4!");
                setDcolor();
                ContinuePause();
            })

        }
        else if (key==27) // <ESC> key
        {
            break;
        }
    }

    return ret;
}

_lib_ret About(int arg, FILE ** out, struct _lib_data * data)
{
    _lib_ret ret;
    ret.menucmd=DEFAULT;

    clrscr();

    printf("\n");
    setcolor(bfcolor(BLACK, GRAY));
    PrintUMenuPos("Menu g\x88\xA2wne / O programie");
    setDcolor();

    printf("\n                    Program biblioteczny");
    printf("\n   Wersja programu: %s\n", FULLVERSION_STRING);
    printf("\n    Autor programu: Adam Bajguz");
    printf("\n                    Numer indeksu: 101247");
    printf("\n                    Numer grupy Ps z przedmiotu 'Podstawy Programowania': 8");

//    for(int i=0; i<14; ++i)
//    {
//        printf("\n\n   KOD B\x9D\xA8\x44U [%.2d]: ",i);
//        PrintErrorInfo(i);
//    }

    MMenuBackPause();

    return ret;
}

_lib_ret CloseLib(int arg, FILE ** libfile, struct _lib_data * data)
{
    _lib_ret ret;
    ret.menucmd=DEFAULT;

    printf("\n ");
    PrintDoubleLine(10);
    YN_option(Czy na pewno chcesz zamkn\xA5\x86 aktualn\xA5 bibliotek\xA9,
    {
        Books_Free(&data->book);
        data->book=NULL;

        Users_Free(&data->user);
        data->user=NULL;

        data->cfg.libname=NULL;
        data->cfg.maxBorrowDays=GetConfig().MaxDays;
        data->cfg.BUIDnext=0;
        data->cfg.UUIDnext=0;

        ret.menucmd=DEFAULT;
        break;
    },
    {
        ret.menucmd=NO_JUMP;
        break;
    })

    return ret;
}

_lib_ret CloseApp(int arg, FILE ** libfile, struct _lib_data * data)
{
    _lib_ret ret;
    ret.menucmd=DEFAULT;

    printf("\n ");
    PrintDoubleLine(10);
    YN_option(Czy na pewno chcesz zako\xE4\x63zyc program,
    {
        Books_Free(&data->book);
        data->book=NULL;
        Users_Free(&data->user);
        data->user=NULL;
        exit(0);
    },
    {
        ret.menucmd=NO_JUMP;
        break;
    })

    return ret;
}

_lib_ret NewFile(int arg, FILE ** libfile, struct _lib_data * data)
{
    _lib_ret ret;
    ret.menucmd=DEFAULT;

    clrscr();

    setcolor(bfcolor(BLACK, WHITE));
    PrintHelp(FILENAME_LOAD);
    setcolor(bfcolor(BLACK, GRAY));
    printf("\n");
    PrintUMenuPos("Menu g\x88\xA2wne / Nowa biblioteka");
    printf("\n ");
    setDcolor();

    PrintU2MenuPos("Istniej\xA5\x63\x65 pliki biblioteczne:");
    system("DIR *.lib /A-D /B");

    printf("\n\n  Wprowad\xAB nazw\xA9 nowego pliku biblioteki (*.lib): ");
    static char fname[256];
    get256(fname);
    if(strcmp(fname, ""))
    {
        libfile = fopen(fname, "rt");
        if(!libfile) // if file does not exists create it
        {
            libfile = fopen(fname, "wt");
            fclose(libfile);
            data->cfg.libname=fname;
            data->cfg.maxBorrowDays=GetConfig().MaxDays;
            data->cfg.BUIDnext=0;
            data->cfg.UUIDnext=0;
            SaveLib(libfile, data);
        }
        else
        {
            ret.menucmd=NO_JUMP;
            clrscr();

            setcolor(bfcolor(BLACK, GRAY));
            printf("\n");
            PrintUMenuPos("Menu g\x88\xA2wne / Nowa biblioteka");

            setcolor(bfcolor(BLACK, LIGHTRED));
            printf("\n   B\x9D\xA4\x44: Plik '%s' ju\xBE istnieje!\n         Nie utworzono pliku!", fname);
            setDcolor();

            MMenuBackPause();
        }
    }
    else
        ret.menucmd=NO_JUMP;

    return ret;
}

_lib_ret LoadFile(int arg, FILE ** libfile, struct _lib_data * data)
{
    _lib_ret ret;
    ret.menucmd=DEFAULT;

    clrscr();
    if(!arg) //arg==0
    {
        setcolor(bfcolor(BLACK, WHITE));
        PrintHelp(FILENAME_LOAD);
        setcolor(bfcolor(BLACK, GRAY));
        printf("\n");
        PrintUMenuPos("Menu g\x88\xA2wne / Otw\xA2rz bibliotek\xA9");
        printf("\n ");
        setDcolor();

        PrintU2MenuPos("Istniej\xA5\x63\x65 pliki biblioteczne:");
        system("DIR *.lib /A-D /B");

        printf("\n\n Wprowad\xAB nazw\xA9 pliku biblioteki (*.lib): ");
    }
    static char fname[256];
    if(arg) //arg==1
        strcpy(fname, GetLastFile());
    else //arg==0
        get256(fname);

    if(strcmp(fname, "")) //if fname equals "" strcmp will return 0, otherwise strcmp return 1 so file name is appropiate and file might be loaded
    {
        libfile = fopen(fname, "rt");
        if(!libfile)
        {
            ret.menucmd=NO_JUMP;
            clrscr();
            printf("\n");


            setcolor(bfcolor(BLACK, GRAY));
            if(arg) //arg==1
            {
                PrintUMenuPos("Menu g\x88\xA2wne / Otw\xA2rz ostatni\xA5 bibliotek\xA9");
                SetLastFile("");
            }
            else //arg==0
                PrintUMenuPos("Menu g\x88\xA2wne / Otw\xA2rz bibliotek\xA9");

            setcolor(bfcolor(BLACK, LIGHTRED));
            printf("\n   B\x9D\xA4\x44: Plik '%s' nie istnieje!", fname);
            setDcolor();

            MMenuBackPause();
        }
        else
        {
            unsigned short err_code = LoadLib(libfile, data);

            if(err_code==6) // if success loading
            {
                ret.menucmd=DEFAULT;
                data->cfg.libname=fname;
                SetLastFile(fname);
            }
            else // if error occuredd while loading
            {
                ret.menucmd=NO_JUMP;
                printf("\n  ");
                PrintDoubleLine(10);

                setcolor(bfcolor(BLACK, LIGHTRED));
                printf("\n   B\x9D\xA4\x44: Plik '%s' jest niepoprawny lub uszkodzony!", fname);
                setDcolor();
                printf("\n\n   KOD B\x9D\xA8\x44U [%.2d]: ", err_code);

                PrintErrorInfo(err_code);
                MMenuBackPause();
            }

            fclose(libfile);
        }
    }
    else // fname == ""
    {
        ret.menucmd=NO_JUMP;
//        if(arg==1)
//        {
//            setcolor(bfcolor(BLACK, LIGHTRED));
//            printf("\n\n Nie ma ostatniego pliku do otwarcia!");
//            setDcolor();
//
//#if SLEEP_PAUSE == 0
//            Sleep(ACTION_MESSAGE_TIME);
//#else
//            ContinuePause();
//#endif // PAUSE
//        }
    }

    return ret;
}

const char * GetLastFile(void)
{
    static char fname[256];
    FILE * config = fopen(LAST_FILE, "rt");
    if(config)
    {
        fget256static(config, fname);
        fclose(config);
    }
    else
        strcpy(fname, "");

    return fname;
}

void SetLastFile(const char fname[256])
{
    FILE * config = fopen(LAST_FILE, "wt");
    if(config)
    {
        fputs(fname, config);
        fprintf(config, "\n");
        fclose(config);
    }
}
