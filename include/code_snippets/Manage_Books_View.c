/*
 * A code snippet used in:
 * Books()
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
        printf("Wy\x98wietlane s\xA5 wszystkie ksi\xA5\xBEki");
        break;

    case BORROWED:
        printf("Wy\x98wietlane s\xA5 tylko wypo\xBEyczone ksi\xA5\xBEki");
        break;

    case NOT_BORROWED:
        printf("Wy\x98wietlane s\xA5 tylko dost\xA9pne ksi\xA5\xBEki");
        break;

    case BORROWED_LONG:
        printf("Wy\x98wietlane s\xA5 tylko ksi\xA5\xBEki wypo\xBEyczone, kt\xA2re s\xA5\n   po terminie zdania (%d-dniowym)", data->cfg.maxBorrowDays);
        break;

    case ID:
        printf("Wyniki wyszukiwania po ID - \"%s\"", search_str);
        break;

    case TITLE:
        printf("Wyniki wyszukiwania po tytule - \"%s\"", search_str);
        break;

    case NAME:
        printf("Wyniki wyszukiwania po imieniu autora - \"%s\"", search_str);
        break;

    case SURNAME:
        printf("Wyniki wyszukiwania po nazwisku autora - \"%s\"", search_str);
        break;
    };

    printf(";\n\n   posortowane po polu '");
    switch(sorted)
    {
    case sID:
        printf("ID");
        break;

    case sTITLE:
        printf("TYTU\x9D");
        break;

    case sNAME:
        printf("IMI\xA8 AUTORA");
        break;

    case sSURNAME:
        printf("NAZWISKO AUTORA");
        break;

    case sBORROWED:
        printf("STAN");
        break;
    };

#include "Manage_SortDirr_View.c"
