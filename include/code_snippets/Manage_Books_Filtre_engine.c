/*
 * A code snippet used in:
 * Books()
 *
 * to filtre books and add them to the display list
 */

selected2=data->book;
if(selected2)
    while(selected2->next)
        selected2=selected2->next;

while(selected2)
{
    if(FiltreBook(method, selected2, data->user, data->cfg.maxBorrowDays))
        BooksCP_AddBegin(&selected, selected2);
    selected2=selected2->prev;
}
