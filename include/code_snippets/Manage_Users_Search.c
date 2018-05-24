/*
 * A code snippet used in:
 * Books()
 *
 * to provide F3 key action - search
 */

//START
{
    enum FILTRE method = CANCEL;

    while(key!=27)
    {
        setcolor(bfcolor(BLACK, WHITE));
        gotoxy(3, 1);
        printf("                                 [F5]  wyszy\x98\x86 wyszukiwanie  [ESC] anuluj  ");
        gotoxy(3, 2);
        printf("Szukaj czytelnik\xA2w po:                                                     ");
        gotoxy(3, 3);
        printf("[F6] imieniu  [F7] nazwisku  [F8] numerze PESEL                        ");
        setDcolor();

        key=getch();
        if(key==0)
        {
            key=getch();
            if(key==63)  // <F5> - all
            {
                method=ALL;
                filtered=method;
                break;
            }
            else if(key==64) // <F6> - name
            {
                method=NAME;
                filtered=method;
                break;
            }
            else if(key==65) // <F7> - surname
            {
                method=SURNAME;
                filtered=method;
                break;
            }
            else if(key==66) // <F8> - PESEL
            {
                method=PESEL;
                filtered=method;
                break;
            }
        }
    }

    if(method!=CANCEL)
    {
        if(method!=ALL)
        {
            setcolor(bfcolor(BLACK, WHITE));
            gotoxy(3, 1);
            printf("                                                                          ");
            gotoxy(3, 3);
            printf("                                                                          ");
            gotoxy(3, 2);
            printf("Szukaj ");
            switch(filtered)
            {
            case NAME:
                printf("po imieniu czytelnika:                                              ");
                gotoxy(33, 2);
                break;
            case SURNAME:
                printf("po nazwisku czytelnika:                                             ");
                gotoxy(34, 2);
                break;
            case PESEL:
                printf("po numerze PESEL:                                                   ");
                gotoxy(28, 2);
                break;
            };
            setDcolor();

            cCURSOR(true, 20);
            sget1024(search_str);
            cCURSOR(false, 20);
        }

        UsersCP_Free(&selected);

        selected2=data->user;
        if(selected2)
            while(selected2->next)
            {
                selected2=selected2->next;
            }
        while(selected2)
        {
            if(SearchUser(method, selected2, search_str))
                UsersCP_AddBegin(&selected, selected2);
            selected2=selected2->prev;
        }
    }
}
//END
