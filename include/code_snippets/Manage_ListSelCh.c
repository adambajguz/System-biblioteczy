/*
 * A code snippet used in:
 * Books()
 * Users()
 * UserDetails()
 *
 * to change selected element of the list using keyboard arrows.
 */

key=getch();
if(key==224)
{
    key=getch();
    if(key==72 && selected) // <arrow up> action
    {
        if(selected->prev) // if selected->prev != NULL
        {
            selected=selected->prev;
            down = false;
        }
    }
    else if(key==80 && selected) // <arrow down> action
    {
        if(selected->next) // if selected->next != NULL
        {
            selected=selected->next;
            down = true;
        }
    }
}
