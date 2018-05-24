/*
 * A code snippet used in:
 * Users()
 *
 * to print current list view mode
 */

//START
{
    setcolor(bfcolor(BLACK, WHITE));
    printf("\n   ");
    switch(filtered)
    {
    case ALL:
        printf("Wy\x98wietlani s\xA5 wszyscy czytelnicy");
        break;

    case BORROWED_LONG:
        printf("Wy\x98wietlani s\xA5 tylko czytelnicy z ksi\xA5\xBEkami wypo\xBEyczonymi,\n   kt\xA2re s\xA5 po terminie zdania (%d-dniowym)", data->cfg.maxBorrowDays);
        break;

    case NAME:
        printf("Wyniki wyszukiwania po imieniu czytelnika - \"%s\"", search_str);
        break;

    case SURNAME:
        printf("Wyniki wyszukiwania po nazwisku czytelnika - \"%s\"", search_str);
        break;

    case PESEL:
        printf("Wyniki wyszukiwania po numerze PESEL - \"%s\"", search_str);
        break;
    };

    printf(";\n\n   posortowani po polu '");

    switch(sorted)
    {
    case sNAME:
        printf("IMI\xA8");
        break;

    case sSURNAME:
        printf("NAZWISKO");
        break;

    case sPESEL:
        printf("PESEL");
        break;
    };

#include "Manage_SortDirr_View.c"
