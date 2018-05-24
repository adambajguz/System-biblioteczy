#include "./LibraryUsers.h"

void UsersCP_AddBegin(UsersCPNode ** first, const UsersNode * node)
{
    UsersCPNode * new_node = (UsersCPNode *)malloc(sizeof(UsersCPNode));
    new_node->node = node;
    new_node->next = *first;
    new_node->prev = NULL; // new node will not have previous element

    if(*first) // if there are more than zero elements in list
        (*first)->prev = new_node; // previous (old) first node will have a pointer to new (added) node

    *first = new_node;
}

void UsersCP_Sort(const UsersCPNode * first, const enum SORT method, const enum SORT_WAY sw)
{
    if (first==NULL || first->next==NULL)
        return;

    UsersCPNode * limit = NULL;
    do
    {
        UsersCPNode * prev, * curr;
        for (prev = first, curr = prev->next; curr!=limit; prev = curr, curr=curr->next)
        {
            bool swap_nodes=false;

            if(method==sNAME)
                swap_nodes=StringCompare(prev->node->data.name, curr->node->data.name);
            else if(method==sSURNAME)
                swap_nodes=StringCompare(prev->node->data.surname, curr->node->data.surname);
            else if(method==sPESEL)
                swap_nodes=StringCompare(prev->node->data.pesel, curr->node->data.pesel);


            if(sw==LOWER)
                swap_nodes=!swap_nodes;

            if(swap_nodes)
            {
                UsersNode * tmp = prev->node;
                prev->node = curr->node;
                curr->node = tmp;
            }
        }
        limit = prev;
    }
    while (limit!=first->next);
}

void UsersCP_Free(UsersCPNode ** first)
{
    UsersCPNode * nextnode = *first;
    while(nextnode)
    {
        UsersCPNode * tmp = nextnode;
        nextnode = nextnode->next;

        free(tmp);
    }
    *first = NULL;
}

void UsersCP_ScrollListPrint(UsersCPNode * selected, const unsigned int num, const bool down, const unsigned int max_borrow_days, const int h)
{
    UsersCPNode * tmp = selected;
#include "code_snippets/List_ScrollListPrint_part1.c"
    Users_ListPrintSingle(selected->node, false, max_borrow_days); // printing element before selected without position sign
#include "code_snippets/List_ScrollListPrint_part2.c"
    Users_ListPrintSingle(selected->node, true, max_borrow_days); // printing selected element with position sign
#include "code_snippets/List_ScrollListPrint_part3.c"
    Users_ListPrintSingle(selected->node, false, max_borrow_days); // printing element after selected without position sign
#include "code_snippets/List_ScrollListPrint_part4.c"
}

//---Library Users---

UsersNode * Users_SearchWhoBorrowedByBUID(UsersNode * first, const unsigned int sBUID)
{
    while (first && Borrowed_SearchByBUID(first->data.borrowed, sBUID)==NULL)
        first=first->next;
    return first;
}

void Users_AddBegin(UsersNode ** first, const UserData data)
{
    UsersNode * new_node = (UsersNode *)malloc(sizeof(UsersNode));
#include "code_snippets/List_AddBegin.c""
}

void Users_Remove(UsersNode ** first, UsersNode * selected)
{
#include "code_snippets/List_Remove.c""
    Borrowed_Free(&selected->data.borrowed);
    free(selected);
}

void Users_Save(UsersNode * first, const FILE * libfile)
{
    while (first)
    {
        fprintf(libfile, ".U\n");
        fprintf(libfile, "%u\n", first->data.UID);
        fprintf(libfile, "%s\n", first->data.name);
        fprintf(libfile, "%s\n", first->data.surname);
        fprintf(libfile, "%s\n", first->data.address);
        fprintf(libfile, "%s\n", first->data.pesel);
        fprintf(libfile, "%s\n", first->data.email);
        fprintf(libfile, "%s\n", first->data.telephone);
        fflush(libfile);

        Borrowed_Save(first->data.borrowed, libfile);

        fflush(libfile);
        first = first->next;
    }
}

int Users_Load(UsersNode ** first, const FILE * libfile)
{
    char buf[1024], * er;
    unsigned short fchk=0; // variable only for simple file integrity verification process
    UserData tmp;

    while(!feof(libfile))
    {
        if(er=fgets(buf, 1024, libfile))
        {
            if (!strcmp(buf, ".BORROWED >\n"))
            {
                unsigned short err;
                tmp.borrowed=NULL;
                err=Borrowed_Load(&tmp.borrowed, libfile);

                if(err==1) // OK
                    fchk=1;
                else if(err==2) // No .BORROWED <
                {
                    fchk=3;
                    break;
                }
                else // Borrowed read error
                {
                    fchk=4;
                    break;
                }

                // adding new element into the list
                Users_AddBegin(first, tmp);
            }
            else if (!strcmp(buf, ".U\n"))
            {
                //UID loading
                fgets(buf, 32, libfile);
                tmp.UID=atoi(buf);

                //name loading
                fget1024(libfile, &tmp.name);

                //surname loading
                fget1024(libfile, &tmp.surname);

                //address loading
                fget1024(libfile, &tmp.address);

                //PESEL loading
                fget16static(libfile, tmp.pesel);

                //email loading
                fget1024(libfile, &tmp.email);

                //telephone loading
                fget16static(libfile, tmp.telephone);
            }
            else if (!strcmp(buf, ".USERS <\n"))
            {
                fchk=2;
                break;
            }
            else
            {
                fchk=5; // protection against invalid file
                break;
            }
        }
        else
            break;
    }

    return fchk;
}

void Users_PrintDetails(const UsersNode * element, const unsigned int max_borrow_days)
{
    printf("               %s %s\n\n", element->data.name, element->data.surname);
    printf("        PESEL: %s\n", element->data.pesel);
    printf("        Adres: %s\n", element->data.address);
    printf("       e-mail: %s\n", element->data.email);
    printf("         tel.: %s\n", element->data.telephone);

    const unsigned int bsize = Borrowed_BSize(element->data.borrowed);
    printf("   Ilosc wyp.: ");
    if(bsize)
        printf("%u (w tym %u po terminie)\n", Borrowed_BSize(element->data.borrowed), Borrowed_BAfterSize(element->data.borrowed, max_borrow_days));
    else
        printf("0\n");

}

void Users_ListPrintSingle(const UsersNode * element, const bool selected, const unsigned int max_borrow_days)
{
    PrintSelectionMark(selected);
    printf("             %s %s\n", element->data.name, element->data.surname);

    PrintSelectionMark(selected);
    printf("      PESEL: %s\n", element->data.pesel);

    PrintSelectionMark(selected);
    const unsigned int bsize = Borrowed_BSize(element->data.borrowed);
    printf(" Ilosc wyp.: ");
    if(bsize)
        printf("%u (w tym %u po terminie)\n", Borrowed_BSize(element->data.borrowed), Borrowed_BAfterSize(element->data.borrowed, max_borrow_days));
    else
        printf("0\n");
}

void Users_Free(UsersNode ** first)
{
    UsersNode * nextnode = *first;
    while(nextnode)
    {
        UsersNode * tmp = nextnode;
        nextnode = nextnode->next;

        free(tmp->data.name);
        free(tmp->data.surname);
        free(tmp->data.address);
        free(tmp->data.email);
        Borrowed_Free(&tmp->data.borrowed);
        free(tmp);
    }
    *first = NULL;
}

//-------------------
