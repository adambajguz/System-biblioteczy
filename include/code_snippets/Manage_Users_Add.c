/*
 * A code snippet used in:
 * Users()
 *
 * to provide F4 key action - add
 */

//START
{
    AddUser(data);
    selected2=data->user;

    SaveLib(libfile, data);

    UsersCP_Free(&selected);
    if(selected2)
        while(selected2->next)
        {
            selected2=selected2->next;
        }

    while(selected2)
    {
        UsersCP_AddBegin(&selected, selected2);
        selected2=selected2->prev;
    }
#if SLEEP_PAUSE == 0
    Sleep(ACTION_MESSAGE_TIME);
#else
    ContinuePause();
#endif // SLEEP_PAUSE
}
//END
