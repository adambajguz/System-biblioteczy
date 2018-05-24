/*
 * A code snippet used in:
 * Books()
 * Users()
 *
 * to provide sort direction selection using F11 and F12 key
 */

setcolor(bfcolor(BLACK, WHITE));
gotoxy(3, 1);
printf("                                                              [ESC] anuluj ");
gotoxy(3, 2);
printf("Tryb sortowania:                                                           ");
gotoxy(3, 3);
printf("[F11] rosn\xA5\x63o  [F12] malej\xA5\x63o                                              ");
setDcolor();

while(key!=27)
{
    key=getch();
    if(key==224)
    {
        key=getch();
        if(key==133)  // <F11> - lower
        {
            sw=LOWER;
            break;
        }
        else if(key==134) // <F12> - upper
        {
            sw=UPPER;
            break;
        }
    }
}
