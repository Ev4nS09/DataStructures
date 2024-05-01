#ifndef linkedlist_h
#define linkedlist_h

#include "generic_type_functions.h"

/*
    A node is a struct that holds a value and a pointer to another node
*/
typedef struct Node
{
    struct Node* next;
    void* value;
}Node;

/*
    A List is a struct that holds a the pointer to the first node of the list, and the last, it's size and a pointer to a function to free
    the value that a node holds. 
*/
typedef struct List
{
    Node* first;
    Node* last;
    int size;
    Free free_value;
}List;

/*
    Initializes a list, the first and last node are NULL, and the size is 0
*/
List* list_init(Free free_value);

/*
    It removes all elements from the list and frees them
*/
void list_clear(List* list);

/*
    It clear's the list and then frees the pointer to the list
*/
void list_free(List* list);

/*
    Adds a value to the beggining of the list, copying the value and allocating it in memory
*/
void list_add(List* list, void* value, Copy copy_value);

/*
    Adds a value to the end of the list, copying the value and allocating it in memory
*/
void list_add_last(List* list, void* value, Copy copy_value);

void list_remove_first(List* list);

void list_remove(List* list, int index);


/*
    Prints a list
*/
void list_print(List* list, Print print_value);


#endif