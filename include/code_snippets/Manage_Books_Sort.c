/*
 * A code snippet used in:
 * Books()
 *
 * to provide F1 key action - sort
 */

//START
{
    enum SORT smethod = CANCEL;
    enum SORT_WAY sw = CANCEL;

    while(key!=27)
    {
        setcolor(bfcolor(BLACK, WHITE));
        gotoxy(3, 1);
        printf("                                                              [ESC] anuluj ");
        gotoxy(3, 2);
        printf("Sortowanie ksi\xA5\xBE\x65k po polu:                                                ");
        gotoxy(3, 3);
        printf("[F5] ID  [F6] tytu\x88  [F7] imi\xA9 autora  [F8] nazwisko autora  [F9] stan     ");
        setDcolor();

        key=getch();
        if(key==0)
        {
            key=getch();
            if(key==63)  // <F5> - ID
            {
                smethod=sID;
                break;
            }
            else if(key==64) // <F6> - title
            {
                smethod=sTITLE;
                break;
            }
            else if(key==65) // <F7> - author's name
            {
                smethod=sNAME;
                break;
            }
            else if(key==66) // <F8> - author's surname
            {
                smethod=sSURNAME;
                break;
            }
            else if(key==67) // <F9> - borrowed state
            {
                smethod=sBORROWED;
                break;
            }
        }
    }

    if(smethod!=CANCEL)
    {
#include "./Sort_Direction.c"
        if(sw!=CANCEL)
        {
            sorted=smethod;
            sortedway=sw;
            while(selected->prev)
                selected=selected->prev;
            BooksCP_Sort(selected, data->user, smethod, sw);
        }
    }
}
//END
