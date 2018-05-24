/*
 * A code snippet used in:
 * UserDetails()
 *
 * to filtre borrowed books and add them to the display list
 */

selected2=(*selectedU)->data.borrowed;
if(selected2)
    while(selected2->next)
    {
        selected2=selected2->next;
    }
while(selected2)
{
    if(FiltreBorrowed(method, selected2, data->cfg.maxBorrowDays))
        BorrowedCP_AddBegin(&selected, selected2);
    selected2=selected2->prev;
}
