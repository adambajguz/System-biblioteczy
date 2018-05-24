/*
 * A code snippet used in:
 * Users()
 *
 * to filtre users and add them to the display list
 */

selected2=data->user;
if(selected2)
    while(selected2->next)
    {
        selected2=selected2->next;
    }
while(selected2)
{
    if(FiltreUser(method, selected2->data.borrowed, data->cfg.maxBorrowDays))
        UsersCP_AddBegin(&selected, selected2);
    selected2=selected2->prev;
}
