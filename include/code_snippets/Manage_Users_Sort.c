/*
 * A code snippet used in:
 * Users()
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
        printf("Sortowanie czytelnik\xA2w po polu:                                            ");
        gotoxy(3, 3);
        printf("[F5] imi\xA9  [F6] nazwisko  [F7] PESEL                                       ");
        setDcolor();

        key=getch();
        if(key==0)
        {
            key=getch();
            if(key==63)  // <F5> - name
            {
                smethod=sNAME;
                break;
            }
            else if(key==64) // <F6> - surname
            {
                smethod=sSURNAME;
                break;
            }
            else if(key==65) // <F7> - PESEL
            {
                smethod=sPESEL;
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
            UsersCP_Sort(selected, smethod, sw);
        }
    }
}
//END
