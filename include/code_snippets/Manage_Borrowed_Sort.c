/*
 * A code snippet used in:
 * UserDetails()
 *
 * to provide F3 key action - sort
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
        printf("Sortowanie wypo\xBEyczonych ksi\xA5\xBE\x65k po polu:                                 ");
        gotoxy(3, 3);
        printf("[F5] ID  [F6] tytu\x88  [F7] imi\xA9 autora  [F8] nazwisko autora                ");
        gotoxy(3, 4);
        printf("[F9] terminie zdania ksi\xA5\xBEki                                               ");
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
            else if(key==67) // <F8> - book state (return time)
            {
                smethod=sBORROWED;
                break;
            }
        }
    }

    if(smethod!=CANCEL)
    {
        gotoxy(3, 4);
        printf("                                                                           ");
#include "./Sort_Direction_Borrowed.c"

        if(sw!=CANCEL)
        {
            sorted=smethod;
            sortedway=sw;
            while(selected->prev)
                selected=selected->prev;
            BorrowedCP_Sort(selected, data->book, smethod, sw);
        }
    }
}
//END
