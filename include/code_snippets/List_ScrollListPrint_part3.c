/*
 * A code snippet [part 3] used in:
 *
 * Books_ScrollListPrint()
 * Users_ScrollListPrint()
 * Borrowed_ScrollListPrint()
 */

{ // #1-0
    if(after!=num-1)
        printf("\n\n");

    for(; after<num-1; ++after) // printing up to num-1 elements after selected element
    { // #1-1
        if(selected->next)
        { //#1-2
            selected=selected->next;
