/*
 * A code snippet [part 4] used in:
 *
 * Books_ScrollListPrint()
 * Users_ScrollListPrint()
 * Borrowed_ScrollListPrint()
 */

            if(after!=num-2)
                printf("\n\n");
        } //#1-2 end
        else
        {
            for(unsigned int nli=0; nli<h; ++nli)
                printf("\n");
            if(after!=num-2)
                printf("\n\n");
        }
    }//#1-1 end

   // if(selected->next)
   //     selected=selected->next;
    ListBorder(selected->next, false, NULL); // printing list border with arrow down
} //#1-0 end
