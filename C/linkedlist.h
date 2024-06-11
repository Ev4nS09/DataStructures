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

/*
  Adds a value at the position given, copying the value and allocating it in memory
*/
void list_add_at(List* list, void* value, int index, Copy copy_value);

/*
  Adds a value using a compare function. It will iterate throught the list until the compare function is false, 
  and then inserts the value on that position 
*/
void list_add_cmp(List* list, void* value, Compare cmp, Copy copy_value);

/*
  Removes the first element from the list and frees it
*/
void list_remove_first(List* list);

/*
  Removes an element from the list at a given position and frees it
*/
void list_remove(List* list, int index);

/*
  Removes all the elements that are equal to the value given and frees them.

  Note: The function cmp given can change the nature of the function, it is up to the programmer to determine
  how tto remeve an element
*/
void list_remove_all_value(List* list, void* value, Compare cmp);

/*
  Returns a copy of the first value of the list
*/  
void* list_get_first(List* list, Copy copy_value);

/*
  Return a copy of the last value of the list
*/
void* list_get_last(List* list, Copy copy_value);

/*
  Return a copy of the value at a given position of the list
*/
void* list_get_at(List* list, int index, Copy copy_value);

/*
  Returns true(1) if the list contains the value given, else it returns false (0)

  Note: The function cmp given can change the nature of the function, it is up to the programmer to determine
  how to compare the elements 
*/
int list_contains_value(List* list, void* value, Compare cmp);

/*
  Sorts the list using the sorting algorithm "insertion sort"

  Note: The function cmp given can change the nature of the function, it is up to the programmer to determine
  how to compare the elements 
*/
void list_insertion_sort(List* list, Compare cmp);

/*
  Copys the elemtens of the list to a given array, the array is expected to be empty since the code will overlap
  the content of the array if there is cotent in it
*/
int list_to_array(List* list, void** array, Copy copy_value);

/*
  Creates a list out of an array, the list is initialized in the function
*/
List* list_array_to_list(void** array, int array_size, Free free, Copy copy_value);

/*
    Prints a list
*/
void list_print(List* list, Print print_value);


#endif
