/*
 * A code snippet used in:
 * Books()
 *
 * to provide F4 key action - add
 */

//START
{
    AddBook(data);
    SaveLib(libfile, data);

    BooksCP_Free(&selected);
    selected2=data->book;
    if(selected2)
        while(selected2->next)
        {
            selected2=selected2->next;
        }
    while(selected2)
    {
        BooksCP_AddBegin(&selected, selected2);
        selected2=selected2->prev;
    }

#if SLEEP_PAUSE == 0
    Sleep(ACTION_MESSAGE_TIME);
#else
    ContinuePause();
#endif // SLEEP_PAUSE
}
//END
