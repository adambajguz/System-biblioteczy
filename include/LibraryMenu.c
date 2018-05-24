#include "./LibraryMenu.h"

void MenuPrint(const struct MenuLevel ** menu, const unsigned int selection, const struct _lib_data * data)
{
    clrscr();

    if(data->cfg.libname)
    {
        cPRINT_LINE_H(0, 0, ' ', 80, WHITE, BLACK);
        gotoxy(2,0);
        printf("Aktualna biblioteka: '%s'\n\n", data->cfg.libname);
        setDcolor();
    }

    setcolor(bfcolor(BLACK, WHITE));
    PrintHelp(MENU);
    setcolor(bfcolor(BLACK, GRAY));
    PrintUMenuPos((*menu)->MName);
    printf("\n");
    setDcolor();

    for(int i=0; i<(*menu)->MSize; ++i)
    {
        if(i == selection)
            printf("  %c ", 0x10);
        else
            printf("   ");

        printf(" %s", (*menu)->MItems[i].str );
        if( (*menu)->MItems[i].custom_print )
            (*menu)->MItems[i].custom_print();

        if(i == selection)
            printf("  %c", 0x11);

        printf("\n\n");
    }
}

_lib_ret MenuAction(const struct MenuLevel ** menu, FILE ** out, const struct _lib_data * data, const int pos)
{
    _lib_ret ret;
    ret.menucmd=DEFAULT;

    if( (*menu)->MItems[pos].funct )
        ret=(*menu)->MItems[pos].funct( (*menu)->MItems[pos].farg, out, data );

    if(ret.menucmd==DEFAULT)
    {
        if( (*menu)->MItems[pos].jump)
            (*menu) = (*menu)->MItems[pos].jump;
        else
            ret.menucmd=pos;
    }
    else if(ret.menucmd==NO_JUMP)
        ret.menucmd=pos;

    return ret;
}
