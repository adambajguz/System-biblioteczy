/*
 * A code snippet used in:
 * UserDetails()
 *
 * to print current list view mode
 */

//START
{
    setcolor(bfcolor(BLACK, WHITE));
    printf("  ");
    switch(filtered)
    {
    case ALL:
        printf("Wy\x98wietlane s\xA5 wszystkie wypo\xBEyczone ksi\xA5\xBEki");
        break;

    case BORROWED:
        printf("Wy\x98wietlane s\xA5 tylko wypo\xBEyczone ksi\xA5\xBEki, kt\xA2re nie zosta\x88y zdane");
        break;

    case RETURNED:
        printf("Wy\x98wietlane s\xA5 tylko wypo\xBEyczone ksi\xA5\xBEki, kt\xA2re zosta\x88y zdane");
        break;

    case BORROWED_LONG:
        printf("Wy\x98wietlane s\xA5 tylko wypo\xBEyczone ksi\xA5\xBEki, kt\xA2re s\xA5\n  po terminie zdania (%d-dniowym)", data->cfg.maxBorrowDays);
        break;
    };

    printf(";\n\n  posortowane po polu '");
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
        printf("TERMIN ZDANIA");
        break;
    };

#include "Manage_SortDirr_Borrowed.c"

