/*
 * A code snippet used in:
 * UserDetails()
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
        printf("Edycja czytelnika po polu:                                             ");
        gotoxy(3, 3);
        printf("[F5] imi\xA9  [F6] nazwisko  [F7] adres  [F8] PESEL  [F9] e-mail  [F10] tel.");
        gotoxy(3, 4);
        printf("                                                                       ");
        setDcolor();

        key=getch();
        if(key==0)
        {
            key=getch();
            if(key==63)  // <F5> - name
            {
                emethod=sNAME;
                break;
            }
            else if(key==64) // <F6> - surname
            {
                emethod=sSURNAME;
                break;
            }
            else if(key==65) // <F7> - address
            {
                emethod=sADDRESS;
                break;
            }
            else if(key==66) // <F8> - PESEL
            {
                emethod=sPESEL;
                break;
            }
            else if(key==67) // <F9> - e-mail
            {
                emethod=sEMAIL;
                break;
            }
            else if(key==68) // <F10> - phone
            {
                emethod=sPHONE;
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
        PrintUMenuPos(".. / Szczeg\xA2\x88y / Edytuj czytelnika");
        printf("\n");
        setDcolor();
        Users_PrintDetails(*selectedU, data->cfg.maxBorrowDays);

        printf("\n\n");

        char * tmp;
        char tmp2[13];
        if(emethod==sNAME)
        {
            printf("Podaj nowe imi\xA9: ");
            get1024(&tmp);
        }
        else if(emethod==sSURNAME)
        {
            printf("Podaj nowe nazwisko: ");
            get1024(&tmp);
        }
        else if(emethod==sADDRESS)
        {
            printf("Podaj nowy adres: ");
            get1024(&tmp);
        }
        else if(emethod==sPESEL)
        {
            printf("Podaj nowy PESEL (np. 00123456789): ");
            get(tmp2, 14);
        }
        else if(emethod==sEMAIL)
        {
            printf("Podaj nowy e-mail: ");
            get1024(&tmp);
        }
        else if(emethod==sPHONE)
        {
            printf("Podaj nowy numer telefonu (np. +48123456789): ");
            get(tmp2, 14);
        }

        printf("\n ");
        PrintDoubleLine(10);

        YN_option(Czy na pewno chcesz zedytowa\x86 tego czytelnika,
        {
            //clrscr();

            if(emethod==sNAME)
            {
                free((*selectedU)->data.name);
                (*selectedU)->data.name = tmp;
            }
            else if(emethod==sSURNAME)
            {
                free((*selectedU)->data.surname);
                (*selectedU)->data.surname = tmp;
            }
            else if(emethod==sADDRESS)
            {
                free((*selectedU)->data.address);
                (*selectedU)->data.address = tmp;
            }
            else if(emethod==sPESEL)
            {
                strcpy((*selectedU)->data.pesel, tmp2);
            }
            else if(emethod==sEMAIL)
            {
                free((*selectedU)->data.email);
                (*selectedU)->data.email = tmp;
            }
            else if(emethod==sPHONE)
            {
                strcpy((*selectedU)->data.telephone, tmp2);
            }

            SaveLib(libfile, data);

            setcolor(bfcolor(BLACK, LIGHTGREEN));
            printf("\n\n Pomy\x98lnie zedytowano czytelnika!");
            setDcolor();
        },
        {
            //clrscr();
            setcolor(bfcolor(BLACK, LIGHTRED));
            printf("\n\n Nie zedytowano czytelnika!");
            setDcolor();
        })
    }
}
//END
