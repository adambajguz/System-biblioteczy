#include "./LibrarySettingsChoice.h"

void ChoicePrint(const struct ChoiceLevel * menu[], const unsigned int menu_size, const unsigned int selection[], const unsigned int settingsel)
{
    clrscr();
    setcolor(bfcolor(BLACK, WHITE));
    PrintHelp(SETTINGS2);
    setcolor(bfcolor(BLACK, GRAY));
    printf("\n");
    PrintUMenuPos("Menu g\x88\xA2wne / Ustawienia");
    printf("\n");
    setDcolor();

    for(int i=0; i<menu_size; ++i)
    {
        printf(" ");
        if(i == settingsel)
            setcolor(bfcolor(LIGHTGRAY, BLACK));
        printf(" ");

        printf("%s  [ %s ] ", (menu[i])->MName, menu[i]->MItems[selection[i]].str );

        if(i == settingsel)
            setDcolor();
        printf("\n\n");
    }
}

void ChoiceAction(const struct ChoiceLevel * menu, const int pos)
{
    if( (menu)->funct )
        (menu)->funct( (menu)->MItems[pos].what, (menu)->MItems[pos].val);
}
