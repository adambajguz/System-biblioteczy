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
        printf("Opcje filtrowania czytelnik\xA2w:                                             ");
        gotoxy(3, 3);
        printf("[F5] wszyscy  [F6] z ksi\xA5\xBEkami wypo\xBEyczonymi, kt\xA2re s\xA5 po terminie zdania  ");
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
            else if(key==64) // <F6> - borrowed and after max return date
            {
                method=BORROWED_LONG;
                filtered=method;
                break;
            }
        }
    }

    if(method!=CANCEL)
    {
        UsersCP_Free(&selected);

#include "./Manage_Users_Filtre_engine.c"
    }
}
//END
