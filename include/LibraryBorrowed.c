#include "./LibraryUsers.h"

void BorrowedCP_AddBegin(BorrowedCPNode ** first, const UsersNode * node)
{
    BorrowedCPNode * new_node = (BorrowedCPNode *)malloc(sizeof(BorrowedCPNode));
    new_node->node = node;
    new_node->next = *first;
    new_node->prev = NULL; // new node will not have previous element

    if(*first) // if there are more than zero elements in list
        (*first)->prev = new_node; // previous (old) first node will have a pointer to new (added) node

    *first = new_node;
}

void BorrowedCP_Sort(const BorrowedCPNode * first, const BooksNode * book, const enum SORT method, const enum SORT_WAY sw)
{
    if (first==NULL || first->next==NULL)
        return;

    BorrowedCPNode * limit = NULL;
    do
    {
        BorrowedCPNode * prev, * curr;
        for (prev = first, curr = prev->next; curr!=limit; prev = curr, curr=curr->next)
        {
            const BooksNode * prevbook = Books_SearchByBUID(book, prev->node->data.UID);
            const BooksNode * currbook = Books_SearchByBUID(book, curr->node->data.UID);
            bool swap_nodes=false;

            if(method==sID)
                swap_nodes=StringCompare(prevbook->data.id, currbook->data.id);
            else if(method==sNAME)
                swap_nodes=StringCompare(prevbook->data.authorsName, currbook->data.authorsName);
            else if(method==sSURNAME)
                swap_nodes=StringCompare(prevbook->data.authorsSurname, currbook->data.authorsSurname);
            else if(method==sTITLE)
                swap_nodes=StringCompare(prevbook->data.title, currbook->data.title);
            else if(method==sBORROWED)
            {
                if(prev->node->data.returnTime < curr->node->data.returnTime)
                    swap_nodes=true;
            }

            if(sw==LOWER)
                swap_nodes=!swap_nodes;

            if(swap_nodes)
            {
                BorrowedNode * tmp = prev->node;
                prev->node = curr->node;
                curr->node = tmp;
            }
        }
        limit = prev;
    }
    while (limit!=first->next);
}

void BorrowedCP_Free(BorrowedCPNode ** first)
{
    BorrowedCPNode * nextnode = *first;
    while(nextnode)
    {
        BorrowedCPNode * tmp = nextnode;
        nextnode = nextnode->next;

        free(tmp);
    }
    *first = NULL;
}

void BorrowedCP_ScrollListPrint(BorrowedCPNode * selected, BooksNode * users, const unsigned int num, const bool down, const int h)
{
    BorrowedCPNode * tmp = selected;
#include "code_snippets/List_ScrollListPrint_part1.c"
    Borrowed_ListPrintSingle(selected->node, users, false); // printing element before selected without position sign
#include "code_snippets/List_ScrollListPrint_part2.c"
    Borrowed_ListPrintSingle(selected->node, users, true); // printing selected element with position sign
#include "code_snippets/List_ScrollListPrint_part3.c"
    Borrowed_ListPrintSingle(selected->node, users, false); // printing element after selected without position sign
#include "code_snippets/List_ScrollListPrint_part4.c"
}

//---Borrowed Books---

BorrowedNode * Borrowed_SearchByBUID(BorrowedNode * first, const unsigned int sBUID)
{
    while (first && (first->data.UID != sBUID || first->data.returnTime!=0))
        first=first->next;
    return first;
}

void Borrowed_AddBegin(BorrowedNode ** first, const BorrowedData data)
{
    BorrowedNode * new_node = (BorrowedNode *)malloc(sizeof(BorrowedNode));
#include "code_snippets/List_AddBegin.c"
}

unsigned int Borrowed_BSize(BorrowedNode * first)
{
    unsigned int i=0;
    while(first)
    {
        if(!first->data.returnTime)
            ++i;
        first=first->next;
    }
    return i;
}

unsigned int Borrowed_BAfterSize(BorrowedNode * first, const unsigned int max_borrow_days)
{
    unsigned int i=0;
    while(first)
    {
        if( !first->data.returnTime && (time(NULL) - first->data.borrowTime) > (max_borrow_days*3600*24) )
            ++i;
        first=first->next;
    }
    return i;
}

void Borrowed_Save(BorrowedNode * first, const FILE * libfile)
{
    fprintf(libfile, ".BORROWED >\n");
    while (first)
    {
        fprintf(libfile, ".I\n");
        fprintf(libfile, "%u\n", first->data.UID);
        fprintf(libfile, "%u\n", first->data.borrowTime);
        fprintf(libfile, "%u\n", first->data.returnTime);
        fflush(libfile);
        first = first->next;
    }
    fprintf(libfile, ".BORROWED <\n");
}

int Borrowed_Load(BorrowedNode ** first, const FILE * libfile)
{
    char buf[1024], * er;
    unsigned short fchk=0; // variable only for simple file integrity verification process

    while(!feof(libfile))
    {
        if(er=fgets(buf, 1024, libfile))
        {
            if (!strcmp(buf, ".BORROWED <\n"))
            {
                ++fchk;
                break;
            }
            else if (!strcmp(buf, ".I\n"))
            {
                BorrowedData tmp;

                //UID loading
                fgets(buf, 32, libfile);
                tmp.UID=atoi(buf);

                //borrowTime loading
                fgets(buf, 32, libfile);
                tmp.borrowTime=atoi(buf);

                //returnTime loading
                fgets(buf, 32, libfile);
                tmp.returnTime=atoi(buf);

                // adding new element into the list
                Borrowed_AddBegin(first, tmp);
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

void Borrowed_ListPrintSingle(const BorrowedNode * element, BooksNode * books, const bool selected)
{
    char buf[80];
    //PrintSelectionMark(selected);
    //printf("                 UID: %u\n", element->data.UID);

    Books_ListPrintSingle(Books_SearchByBUID(books, element->data.UID), NULL, selected, false, true);

    PrintSelectionMark(selected);
    strftime(buf, 80, "%d.%m.%Y godz. %H:%M", localtime(&element->data.borrowTime));
    printf("TERMIN WYPO\xBDYCZENIA: %s\n", buf);

    PrintSelectionMark(selected);
    if(element->data.returnTime) // if returned time is not null
    {
        strftime(buf, 80, "%d.%m.%Y godz. %H:%M", localtime(&element->data.returnTime));
        printf("      TERMIN ZDANIA: %s\n", buf);
    }
    else
    {
        //printf("\n");
        //PrintSelectionMark(selected);
        setcolor(bfcolor(BLACK, LIGHTRED));
        printf("  Ksi\xA5\xBEka nie zosta\x88\x61 zdana do biblioteki.\n");
        setDcolor();
    }
}

void Borrowed_Free(BorrowedNode ** first)
{
    BorrowedNode * nextnode = *first;
    while(nextnode)
    {
        BorrowedNode * tmp = nextnode;
        nextnode = nextnode->next;
        free(tmp);
    }
    *first = NULL;
}

//--------------------
