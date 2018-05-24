/*
 * A code snippet used in:
 * Books()
 *
 * to provide F2 key action - filtre
 */

//START
{
    enum FILTRE method = CANCEL;

    while(key!=27)
    {
        setcolor(bfcolor(BLACK, WHITE));
        gotoxy(3, 1);
        printf("                                                              [ESC] anuluj ");
        gotoxy(3, 2);
        printf("Opcje filtrowania ksi\xA5\xBE\x65k:                                                 ");
        gotoxy(3, 3);
        printf("[F5] wszystkie  [F6] wypo\xBEyczone  [F7] dost\xA9pne  [F8] po terminie zdania   ");
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
            else if(key==64) // <F6> - borrowed
            {
                method=BORROWED;
                filtered=method;
                break;
            }
            else if(key==65) // <F7> - not borrowed
            {
                method=NOT_BORROWED;
                filtered=method;
                break;
            }
            else if(key==66) // <F8> - borrowed and after max return date
            {
                method=BORROWED_LONG;
                filtered=method;
                break;
            }
        }
    }

    if(method!=CANCEL)
    {
        BooksCP_Free(&selected);
#include "./Manage_Books_Filtre_engine.c"
    }
}
//END
