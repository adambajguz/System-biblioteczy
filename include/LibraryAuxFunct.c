#include "./LibraryAuxFunct.h"

bool StringCompare(const char * str1, const char * str2)
{
    int comparelen;

    const int s1=strlen(str1);
    const int s2=strlen(str2);
    if(s1>s2)
        comparelen=s2;
    else
        comparelen=s1;

    /* char lookout[] = {" !\"#$%&'()*+,-./0123456789:;<=>?@aπbcÊdeÍfghijkl≥mnÒoÛpqrsútuwyxzüøA•BC∆DE FGHIJKL£MN—O”PQRSåTUWXYZèØ[\\]^_`{|}~"}; */
    const char lookout[] = {" !\"#$%&'()*+,-./0123456789:;<=>?@a\xA5\x62\x63\x86\x64\x65\xA9\x66ghijkl\x88mn\xE4o\xA2pqrs\x98tuwxyz\xAB\xBE\x41\xA4\x42\x43\x8F\x44\x45\xA8\x46GHIJKL\x9DMN\xE3O\xE0PQRS\x97TUWXYZ\x8D\xBD[\\]^_`{|}~ "};

    for(int i=0; i<comparelen; ++i)
    {
        if(str1[i]!=str2[i])
        {
            int c1v=-1, c2v=-1, j;

            for(j=0; j<111; ++j)
            {
                if(lookout[j]==str2[i])
                {
                    c2v=j;
                    if(c1v!=-1)
                        break;
                }
                else if(lookout[j]==str1[i])
                {
                    c1v=j;
                    if(c2v!=-1)
                        break;
                }
            }

            if(c1v<c2v)
                return false;
            else if(c1v>c2v)
                return true;
        }
    }

    if(s1>s2)
        return true;
    return false;
}

char buffer[16];
void fget16static(const FILE * file, const char * dest)
{
    while(!fgets(buffer, 16, file))
        ;
    endlDel(&buffer);
    strcpy(dest, buffer);
}

void fget256static(const FILE * file, char ** dest)
{
    char buffer[256];
    while(!fgets(buffer, 256, file))
        ;
    endlDel(&buffer);
    strcpy(dest, buffer);
}

void fget1024(const FILE * file, char ** dest)
{
    char buffer[1024];
    while(!fgets(buffer, 1024, file))
        ;
    endlDel(&buffer);
    *dest = (char *)malloc(sizeof(char)*(strlen(buffer)+1));
    strcpy(*dest, buffer);
}

void get(const char * dest, int i)
{
    cCURSOR(true, 20);
    char buffer[16];
    fgets(buffer, i, stdin);
    endlDel(&buffer);
    strcpy(dest, buffer);
    cCURSOR(false, 20);
}

void get1024(char ** dest)
{
    cCURSOR(true, 20);
    char buffer[1024];
    fgets(buffer, 1024, stdin);
    endlDel(&buffer);
    *dest = (char *)malloc(sizeof(char)*(strlen(buffer)+1));
    strcpy(*dest, buffer);
    cCURSOR(false, 20);
}

void sget1024(const char * str)
{
    cCURSOR(true, 20);
    fgets(str, 256, stdin);
    endlDel(str); //removing '\n' from fname
    cCURSOR(false, 20);
}

void get256(const char * fname)
{
    cCURSOR(true, 20);
    fgets(fname, 256, stdin);
    endlDel(fname); //removing '\n' from fname
    cCURSOR(false, 20);
}

void endlDel(char * str)
{
    //removing '\n' from str
    unsigned int len = strlen(str);
    if (len > 0 && str[len-1] == '\n')
        str[--len] = '\0';
}

void PrintUMenuPos(const char * str)
{
    printf("   %s /\n  ", str);
    for(int i=0; i<strlen(str)+3; ++i)
        printf("%c", 0xF1);
    printf("\n");
}

void PrintU2MenuPos(const char * str)
{
    printf(" %s\n  ", str);
    for(int i=0; i<strlen(str); ++i)
        printf("%c", 0xF9);
    printf("\n");
}

void Draw_BoxUPart(void)
{
    printf(" %c", 0xDA);
    for(int i=0; i<76; ++i)
        printf("%c", 0xC4);
}

void Draw_BoxDPart(void)
{
    for(int i=0; i<76; ++i)
        printf("%c", 0xC4);
    printf("%c\n",0xD9);
}

void PrintDoubleLine(short xdim)
{
    for(unsigned short i=0; i<xdim; ++i)
        printf("\xCD");
}

void ListBorder(const bool arrow, const bool up)
{
    int i;
    printf(" ", 0xC4);
    for(i=0; i<35; ++i)
        printf("%c", 0xC4);

    if(arrow)
    {
        if(up)
            printf("%c %c %c %c", 0xB4, 0x1E, 0x1E, 0xC3);
        else
            printf("%c %c %c %c", 0xB4, 0x1F, 0x1F, 0xC3);
        i=0;
    }
    else
        i=-7;

    for(; i<36; ++i)
        printf("%c", 0xC4);

    printf(" \n");
}

void PrintSelectionMark(const bool selected)
{
    if(selected)
        printf(" >   ");
    else
        printf("   ");
}

void MMenuBackPause(void)
{
    cCURSOR(true, 20);
    printf("\n\n ");
    PrintDoubleLine(10);
    printf("\n Naci\x98nij dowolny klawisz, aby powr\xA2\ci\x86 do menu g\x88\xA2wnego...");
    getch();
    cCURSOR(false, 20);

}

void ContinuePause(void)
{
    cCURSOR(true, 20);
    printf("\n\n ");
    PrintDoubleLine(10);
    printf("\n Naci\x98nij dowolny klawisz, aby kontynuowa\x86...");
    getch();
    cCURSOR(false, 20);
}

void PrintErrorInfo(unsigned short err)
{
    switch(err) // print error details
    {
    case 0:
        printf("Nieprawid\x88owy znacznik pocz\xA5tku pliku (brak \".LIBST\\n\").");
        break;

    case 1:
        printf("Nieprawid\x88owy znacznik pocz\xA5tku sekcji (brak \".CONFIG >\\n\").");
        break;

    case 2:
        printf("Nieprawid\x88owy znacznik ko\xE4\x63\x61 sekcji\n                   (brak \".CONFIG <\\n\").");
        break;

    case 3:
        printf("Nieprawid\x88owy znacznik pocz\xA5tku sekcji (brak \".BOOKS >\\n\").");
        break;

    case 4:
        printf("Nieprawid\x88owy znacznik pocz\xA5tku sekcji (brak \".USERS >\\n\").");
        break;

    case 5:
        printf("Nieprawid\x88owy znacznik ko\xE4\x63\x61 pliku (brak \".LIBEN\\n\").");
        break;

    //case 6: // - NO ERRORS
    //break;

    case 7:
        printf("Nieprawid\x88owy znacznik ko\xE4\x63\x61 sekcji (brak \".BOOKS <\\n\")\n");
        printf("                   lub brak znacznika podsekcji (brak \".B\\n\").");
        break;

    case 8:
        printf("B\x88\xA5\x64 podczas odczytu ksia\0xBEek.");
        break;

    case 9:
        printf("Nieprawid\x88owy znacznik ko\xE4\x63\x61 sekcji (brak \".USERS <\\n\")\n");
        printf("                   lub znacznik podsekcji (brak \".U\\n\")\n");
        printf("                   lub znacznik pocz\xA5tku sekcji (brak \".BORROWED >\\n\").");

        break;

    case 10:
        printf("B\x88\xA5\x64 podczas odczytu czytelnik\xA2w.");
        break;

    case 11:
        printf("Nieprawid\x88owy znacznik pocz\xA5tku sekcji\n                   (brak \".BORROWED >\\n\")");
        break;

    case 12:
        printf("Nieprawid\x88owy znacznik ko\xE4\x63\x61 sekcji (brak \".BORROWED <\\n\")\n");
        printf("                   lub brak znacznika podsekcji (brak \".I\\n\").");
        break;

    case 13:
        printf("Bb\x88\xA5\x64 podczas odczytu wypo\xBEycze\xE4.");
        break;

    default:
        printf("Nieznany b\x88\xA5\x64!");
        break;
    }
}

void PrintHelp(const enum HelpText v)
{
    Draw_BoxUPart();
    printf("%c\n %c POMOC: ", 0xBF, 0xB3);
    if(v==MENU)
    {
        printf(" [%c%c] zmie\xE4 wyb\xA2r  [Enter] wybierz                                 ",  24, 25);
    }
    else if(v==BOOKS || v==USERS || v==BOOKS_SELECT || v==USERS_SELECT)
    {
        printf("[ESC] ");
        if(v==BOOKS_SELECT || v==USERS_SELECT)
            printf("anuluj");
        else
            printf("powr\xA2t");

        printf("  [%c%c] zmie\xE4 wyb\xA2r  [Enter] ", 24, 25, 0xB3);

        if(v==BOOKS_SELECT || v==USERS_SELECT)
            printf("wybierz  ");
        else
            printf("szczeg\xA2\x88y");

        printf("                   %c\n", 0xB3);

        printf(" %c                                                                            %c", 0xB3, 0xB3);
        printf("\n %c        [F1] sortuj   [F2] filtruj   [F3] szukaj   [F4] now", 0xB3);
        if(v==BOOKS || v==BOOKS_SELECT)
            printf("a ksi\xA5\xBEka       ");
        else if(v==USERS || v==USERS_SELECT)
            printf("y czytelnik     ");
    }
    else if (v==BOOKS_SINGLE || v==USERS_SINGLE)
    {
        printf("[ESC] powr\xA2t  [%c%c] zmie\xE4 wyb\xA2r                                      %c", 24, 25, 0xB3);
        printf("\n %c                                                                            %c", 0xB3, 0xB3);
        printf("\n %c        [F1] edytuj ", 0xB3);
        if(v==BOOKS_SINGLE)
            printf("ksi\xA5\xBEk\xA9 ");
        else if(v==USERS_SINGLE)
            printf("czytelnika");

        printf("  [F2] usu%c ", (unsigned char)0xE4);
        if(v==BOOKS_SINGLE)
            printf("ksi\xA5\xBEk\xA9   ");
        else if(v==USERS_SINGLE)
            printf("czytelnika");

        if(v==BOOKS_SINGLE)
            printf("                         ");
        else if(v==USERS_SINGLE)
            printf("                        %c", 0xB3);

        if(v==USERS_SINGLE)
            printf("\n %c        [F3] sortuj histori\xA9  [F4] filtruj histori\xA9  [F5] zdaj ksi\xA5\xBEk\xA9     ", 0xB3);
    }
    else if (v==FILENAME_LOAD)
    {
        printf("Wprowad\xAB pust\xA5 nazw\xA9 pliku, aby powr\xA2\x63i\x86 do menu g\x88\xA2wnego.         ");
    }
    else if (v==SETTINGS)
    {
        printf(" [ESC] anuluj  [ENTER] zapisz  [-] zmnijesz  [+] zwi\xA9ksz           ");
    }
     else if (v==SETTINGS2)
    {
        printf(" [ESC] anuluj  [ENTER] zapisz                                       %c\n", 0xB3);
        printf(" %c         [%c%c] zmie\xE4 pozycj\xA9  [-] lub [+] zmie\xE4 warto\x98\x86                     ", 0xB3, 24, 25);
    }
    printf(" %c\n %c", 0xB3, 0xC0);
    Draw_BoxDPart();
    if(v==MENU)
        printf("\n");
}

void PrintLastFile(void)
{
    printf("%s", GetLastFile());
}

void MPrintLastFile(void)
{
    if(strcmp(GetLastFile(),""))
    {
        printf(" - '");
        PrintLastFile();
        printf("'");
    }
    else
    {
        printf(" (opcja niedost\xA9pna)");

    }
}
