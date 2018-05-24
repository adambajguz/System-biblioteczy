/*
 * A code snippet [part 1] used in:
 *
 * Books_ScrollListPrint()
 * Users_ScrollListPrint()
 * Borrowed_ScrollListPrint()
 */

static int prevn=0; // static variable which will contain: previous number elements before! selected element modulo num
int before, after; // variables which will contain: number of elements before! and after! selected element
int n=prevn; // variable which will contain: number of elements before! selected element modulo num
int bmn=0; // variable which will contain: number of elements before! selected element modulo num
{
    {//#0-0
        if(n<=num)
        {
            while(tmp->prev)
            {
                ++bmn;
                tmp=tmp->prev;
            }

            if(down)
                prevn=num;
            n=bmn;
            bmn=bmn%num;
        }

        if(n>num)
        {
            if (down)
            {
                if(prevn<num)
                    ++prevn;
            }
            else if(!down)
            {
                if(prevn>0)
                    --prevn;
            }
        }
    }

    {//#0-1

        for(before=0; before<bmn; ++before) //going back by up to num-1 elements after selected element to print them (if they exist) in proper order
            if(selected->prev)
                selected=selected->prev;
            else
                break;

        if(selected->prev)
            ListBorder(selected->prev->prev, true); // printing list border with arrow up
        else
            ListBorder(selected->prev, true); // printing list border with arrow up

        after = before;
        for(; before>0; --before) //returning to the original function execution element and printing previous elements
        {//#0-2

