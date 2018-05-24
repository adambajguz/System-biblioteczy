/*
 * A code snippet used in:
 * Books_AddBegin()
 * Users_AddBegin()
 * Borrowed_AddBegin()
 *
 * to add new node to the list
 */

new_node->data = data;
new_node->next = *first;
new_node->prev = NULL; // new node will not have previous element

if(*first) // if there are more than zero elements in list
    (*first)->prev = new_node; // previous (old) first node will have a pointer to new (added) node

*first = new_node;
