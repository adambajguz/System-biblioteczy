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
        printf("Szukaj ksi\xA5\xBE\x65k po:                                                         ");
        gotoxy(3, 3);
        printf("[F6] ID  [F7] tytule  [F8] imieniu autora  [F9] nazwisku autora          ");
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
            else if(key==64) // <F6> - id
            {
                method=ID;
                filtered=method;
                break;
            }
            else if(key==65) // <F7> - title
            {
                method=TITLE;
                filtered=method;
                break;
            }
            else if(key==66) // <F8> - author's name
            {
                method=NAME;
                filtered=method;
                break;
            }
            else if(key==67) // <F9> - author's surname
            {
                method=SURNAME;
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
            case ID:
                printf("po ID:                                                             ");
                gotoxy(17, 2);
                break;

            case TITLE:
                printf("po tytule:                                                         ");
                gotoxy(21, 2);
                break;

            case NAME:
                printf("po imieniu autora:                                                 ");
                gotoxy(29, 2);
                break;

            case SURNAME:
                printf("po nazwisku autor:                                                 ");
                gotoxy(29, 2);
                break;
            };
            setDcolor();

            cCURSOR(true, 20);
            sget1024(search_str);
            cCURSOR(false, 20);
        }

        BooksCP_Free(&selected);

        selected2=data->book;
        if(selected2)
            while(selected2->next)
            {
                selected2=selected2->next;
            }
        while(selected2)
        {
            if(SearchBook(method, selected2, search_str))
                BooksCP_AddBegin(&selected, selected2);
            selected2=selected2->prev;
        }
    }
}
//END
