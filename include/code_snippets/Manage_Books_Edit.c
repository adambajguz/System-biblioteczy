/*
 * A code snippet used in:
 * BookDetails()
 *
 * to provide F1 key action - add
 */

//START
{
    enum SORT emethod=CANCEL;

    while(key!=27)
    {
        setcolor(bfcolor(BLACK, WHITE));
        gotoxy(3, 1);
        printf("                                                              [ESC] anuluj ");
        gotoxy(3, 2);
        printf("Edytuj ksi\xA5\xBE\xA9 po polu:                                                     ");
        gotoxy(3, 3);
        printf("[F5] ID  [F6] tytu\x88  [F7] imi\xA9 autora  [F8] nazwisko aut.  [F9] rok wydania");
        setDcolor();

        key=getch();
        if(key==0)
        {
            key=getch();
            if(key==63)  // <F5> - ID
            {
                emethod=sID;
                break;
            }
            else if(key==64) // <F6> - title
            {
                emethod=sTITLE;
                break;
            }
            else if(key==65) // <F7> - author's name
            {
                emethod=sNAME;
                break;
            }
            else if(key==66) // <F8> - author's surname
            {
                emethod=sSURNAME;
                break;
            }
            else if(key==67) // <F9> - year
            {
                emethod=sYEAR;
                break;
            }
        }
    }

    if(emethod!=CANCEL)
    {
        clrscr();
        //PrintHelp(FILENAME_LOAD);
        setcolor(bfcolor(BLACK, GRAY));
        printf("\n");
        PrintUMenuPos(".. / Szczeg\xA2\x88y / Edytuj ksi\xA5\xBEk\xA9");
        printf("\n");
        setDcolor();
        Books_PrintDetails(*selectedB, NULL, data->cfg.maxBorrowDays);

        printf("\n\n");

        char * tmp;
        char tmp2[6];
        if(emethod==sID)
        {
            printf("Podaj nowy identyfikator ksi\xA5\xBEki: ");
            get1024(&tmp);
        }
        else if(emethod==sTITLE)
        {
            printf("Podaj nowy tytu\x88 ksi\xA5\xBEki: ");
            get1024(&tmp);
        }
        else if(emethod==sNAME)
        {
            printf("Podaj nowy imie autora ksi\xA5\xBEki: ");
            get1024(&tmp);
        }
        else if(emethod==sSURNAME)
        {
            printf("Podaj nowy nazwisko autora ksi\xA5\xBEki: ");
            get1024(&tmp);
        }
        else if(emethod==sYEAR)
        {
            printf("Podaj nowy rok wydania ksi\xA5\xBEki (liczb\xA9): ");
            fgets(tmp2, 6, stdin);
        }

        printf("\n ");
        PrintDoubleLine(10);

        YN_option(Czy na pewno chcesz zedytowac\x86 t\xA9 ksi\xA5\xBEk\xA9,
        {
            //clrscr();

            if(emethod==sID)
            {
                free((*selectedB)->data.id);
                (*selectedB)->data.id = tmp;
            }
            else if(emethod==sTITLE)
            {
                free((*selectedB)->data.title);
                (*selectedB)->data.title = tmp;
            }
            else if(emethod==sNAME)
            {
                free((*selectedB)->data.authorsName);
                (*selectedB)->data.authorsName = tmp;
            }
            else if(emethod==sSURNAME)
            {
                free((*selectedB)->data.authorsSurname);
                (*selectedB)->data.authorsSurname = tmp;
            }
            else if(emethod==sYEAR)
            {
                (*selectedB)->data.year=atoi(tmp2);
            }

            SaveLib(libfile, data);

            setcolor(bfcolor(BLACK, LIGHTGREEN));
            printf("\n\n Pomy\x98lnie zedytowno ksi\xA5\xBEk\xA9!");
            setDcolor();
        },
        {
            //clrscr();
            setcolor(bfcolor(BLACK, LIGHTRED));
            printf("\n\n Nie zedytowano ksi\xA5\xBEki!");
            setDcolor();
        })
    }
}
//END
