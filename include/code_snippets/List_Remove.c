/*
 * A code snippet used in:
 * Books_Remove()
 * Users_Remove()
 *
 * to remove node from list
 */

if(selected->next)
    selected->next->prev = selected->prev;
else if(selected->prev)
    selected->prev->next=NULL;

if(selected->prev)
    selected->prev->next = selected->next;
else if(selected->next)
{
    selected->next->prev=NULL;
    *first=selected->next;
}

if(!selected->prev && !selected->next)
    *first=NULL;
