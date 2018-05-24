/*
 * A code snippet used in:
 * BookReturn()
 * UserDetails()
 *
 * to provide book return question
 */

YN_option(Czy na pewno chcesz zda\x86 t\xA9 ksia\xBEk\xA9,
{
    time(&bt->data.returnTime);
    //clrscr();
    setcolor(bfcolor(BLACK, LIGHTGREEN));
    printf("\n\n Pomy\x98lnie zdano ksi\xA5\xBEk\xA9 do biblioteki!");
    setDcolor();
    SaveLib(libfile, data);
},
{
    //clrscr();
    setcolor(bfcolor(BLACK, LIGHTRED));
    printf("\n\n Nie zdano ksi\xA5\xBEki do biblioteki!");
    setDcolor();
})
