/*
 * A code snippet used in:
 * UserDetails()
 *
 * to provide sort direction selection using F11 and F12 key
 */

setcolor(bfcolor(BLACK, WHITE));
gotoxy(3, 1);
printf("                                                              [ESC] anuluj ");
gotoxy(3, 2);
printf("Tryb sortowania:                                                           ");
gotoxy(3, 3);
printf("[F11] od zdanych ksi\xA5\xBE\x65k  [F12] od wypo\xBEyczonych ksi\xA5\xBE\x65k                      ");
setDcolor();

while(key!=27)
{
    key=getch();
    if(key==224)
    {
        key=getch();
        if(key==133)  // <F11> - lower
        {
            sw=UPPER;
            break;
        }
        else if(key==134) // <F12> - upper
        {
            sw=LOWER;
            break;
        }
    }
}
