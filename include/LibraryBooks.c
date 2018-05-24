#include "./LibraryBooks.h"

void BooksCP_AddBegin(BooksCPNode ** first, const BooksNode * node)
{
    BooksCPNode * new_node = (BooksCPNode *)malloc(sizeof(BooksCPNode));
    new_node->node = node;
    new_node->next = *first;
    new_node->prev = NULL; // new node will not have previous element

    if(*first) // if there are more than zero elements in list
        (*first)->prev = new_node; // previous (old) first node will have a pointer to new (added) node

    *first = new_node;
}

void BooksCP_Sort(const BooksCPNode * first, const UsersNode * users, const enum SORT method, const enum SORT_WAY sw)
{
    if (first==NULL || first->next==NULL)
        return;

    BooksCPNode * limit = NULL;
    do
    {
        BooksCPNode * prev, * curr;
        for (prev = first, curr = prev->next; curr!=limit; prev = curr, curr=curr->next)
        {
            bool swap_nodes=false;

            if(method==sID)
                swap_nodes=StringCompare(prev->node->data.id, curr->node->data.id);
            else if(method==sTITLE)
                swap_nodes=StringCompare(prev->node->data.title, curr->node->data.title);
            else if(method==sNAME)
                swap_nodes=StringCompare(prev->node->data.authorsName, curr->node->data.authorsName);
            else if(method==sSURNAME)
                swap_nodes=StringCompare(prev->node->data.authorsSurname, curr->node->data.authorsSurname);
            else if(method==sBORROWED)
            {
                const UsersNode * u = Users_SearchWhoBorrowedByBUID(users, curr->node->data.UID);
                if(!u)
                    swap_nodes=true;
            }

            if(sw==LOWER)
                swap_nodes=!swap_nodes;

            if(swap_nodes)
            {
                BooksNode * tmp = prev->node;
                prev->node = curr->node;
                curr->node = tmp;
            }
        }
        limit = prev;
    }
    while (limit!=first->next);
}

void BooksCP_Free(BooksCPNode ** first)
{
    BooksCPNode * nextnode = *first;
    while(nextnode)
    {
        BooksCPNode * tmp = nextnode;
        nextnode = nextnode->next;

        free(tmp);
    }
    *first = NULL;
}

void BooksCP_ScrollListPrint(BooksCPNode * selected, const UsersNode * first, const unsigned int num, const bool down, const int h)
{
    BooksCPNode * tmp = selected;
#include "code_snippets/List_ScrollListPrint_part1.c"
    Books_ListPrintSingle(selected->node, first, false, true, false); // printing element before selected without position sign
#include "code_snippets/List_ScrollListPrint_part2.c"
    Books_ListPrintSingle(selected->node, first, true, true, false); // printing selected element with position sign
#include "code_snippets/List_ScrollListPrint_part3.c"
    Books_ListPrintSingle(selected->node, first, false, true, false); // printing element after selected without position sign
#include "code_snippets/List_ScrollListPrint_part4.c"
}

BooksNode * Books_SearchByBUID(BooksNode * first, const unsigned int sBUID)
{
    while (first && first->data.UID != sBUID)
        first=first->next;
    return first;
}

void Books_AddBegin(BooksNode ** first, const BookData data)
{
    BooksNode * new_node = (BooksNode *)malloc(sizeof(BooksNode));
#include "code_snippets/List_AddBegin.c"
}

void Books_Remove(BooksNode ** first, BooksNode * selected)
{
#include "code_snippets/List_Remove.c"
    free(selected);
}

void Books_Save(BooksNode * first, const FILE * libfile)
{
    while (first)
    {
        fprintf(libfile, ".B\n");
        fprintf(libfile, "%u\n", first->data.UID);
        fprintf(libfile, "%s\n", first->data.id);
        fprintf(libfile, "%s\n", first->data.title);
        fprintf(libfile, "%s\n", first->data.authorsName);
        fprintf(libfile, "%s\n", first->data.authorsSurname);
        fprintf(libfile, "%d\n", first->data.year);
        fflush(libfile);
        first = first->next;
    }
}

int Books_Load(BooksNode * first, const FILE * libfile)
{
    char buf[1024], * er;
    unsigned short fchk=0; // variable only for simple file integrity verification process

    while(!feof(libfile))
    {
        if(er=fgets(buf, 1024, libfile))
        {
            if (!strcmp(buf, ".BOOKS <\n"))
            {
                ++fchk;
                break;
            }
            else if (!strcmp(buf, ".B\n"))
            {
                BookData tmp;

                //UID loading
                fgets(buf, 32, libfile);
                tmp.UID=atoi(buf);

                //id loading
                fget1024(libfile, &tmp.id);

                //title loading
                fget1024(libfile, &tmp.title);

                //authorsName loading
                fget1024(libfile, &tmp.authorsName);

                //authorsSurname loading
                fget1024(libfile, &tmp.authorsSurname);

                //year loading
                fgets(buf, 32, libfile);
                tmp.year=atoi(buf);

                // adding new element into the list
                Books_AddBegin(first, tmp);
            }
            else
            {
                fchk=2; // protection against invalid file
                break;
            }
        }
    }

    return fchk;
}

void Books_PrintDetails(const BooksNode * element, const UsersNode * first, const unsigned int max_borrow_days)
{
    PrintU2MenuPos("Dane ksi\xA5\xBEki:");
    printf("           ID: %s\n", element->data.id);
    printf("        TYTU\x88: %s\n", element->data.title);
    printf("        AUTOR: %s %s\n", element->data.authorsName, element->data.authorsSurname);
    printf("  ROK WYDANIA: %d\n", element->data.year);

    if(first)
    {
        const UsersNode * u = Users_SearchWhoBorrowedByBUID(first, element->data.UID);
        printf("         STAN: ");
        if(u)
        {
            setcolor(bfcolor(BLACK, RED));
            printf("wypo\xBEyczona\n\n\n ");
            setDcolor();
            PrintU2MenuPos("Dane czytelnika:");
            Users_PrintDetails(u, max_borrow_days);
        }
        else
        {
            setcolor(bfcolor(BLACK, GREEN));
            printf("dost\xA9pna\n");
            setDcolor();
        }
    }
}

void Books_ListPrintSingle(const BooksNode * element, const UsersNode * first, const bool selected, const bool disp_borrowed, const bool from_borrowed)
{
    Users_SearchWhoBorrowedByBUID(NULL, 0);
    PrintSelectionMark(selected);
    if(from_borrowed)
        printf("           ");
    printf("      ID: %s\n", element->data.id);

    PrintSelectionMark(selected);
    if(from_borrowed)
        printf("           ");
    printf("   TYTU\x88: %s\n", element->data.title);

    PrintSelectionMark(selected);
    if(from_borrowed)
        printf("           ");
    printf("   AUTOR: %s %s\n", element->data.authorsName, element->data.authorsSurname);

    if(!from_borrowed)
    {
        PrintSelectionMark(selected);
        printf("    STAN: ");
        if(Users_SearchWhoBorrowedByBUID(first, element->data.UID))
        {
            setcolor(bfcolor(BLACK, RED));
            printf("wypo\xBEyczona\n");
            setDcolor();
        }
        else
        {
            setcolor(bfcolor(BLACK, GREEN));
            printf("dost\xA9pna\n");
            setDcolor();
        }
    }
}

void Books_Free(BooksNode ** first)
{
    BooksNode * nextnode = *first;
    while(nextnode)
    {
        BooksNode * tmp = nextnode;
        nextnode = nextnode->next;

        free(tmp->data.title);
        free(tmp->data.authorsName);
        free(tmp->data.authorsSurname);
        free(tmp);
    }
    *first = NULL;
}
