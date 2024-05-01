#include <stdio.h>
#include <stdlib.h>

#include "linkedlist.h"

Node* node_init(Node* next, void* value)
{
    Node* result = malloc(sizeof(Node));
    result->next = next;
    result->value = value;

    return result;
}

List* list_init(Free free_value)
{
    List* result = malloc(sizeof(List));
    result->first = NULL;
    result->last = NULL;
    result->size = 0;
    result->free_value = free_value;

    return result;
}

void list_clear(List* list)
{
    if(list == NULL)
        return;
    
    while(list->first != NULL)
    {
        Node* temp_node = list->first;
        list->first = list->first->next;

        list->free_value(temp_node->value);
        free(temp_node);
    }
    list->size = 0;
}

void list_free(List* list)
{
    list_clear(list);
    free(list);
}

void list_add(List* list, void* value, Copy copy_value)
{
    list->first = node_init(list->first, copy_value(value));
    list->size = list->size + 1;

    if(list->size == 1)
        list->last = list->first;
}

void list_add_last(List* list, void* value, Copy copy_value)
{
    if(list->first == NULL)
    {
        list_add(list, value, copy_value);
        return;
    }

    Node* node = node_init(NULL, copy_value(value));
    list->last->next = node;
    list->last = node;
    list->size = list->size + 1;
}

void list_remove_first(List* list)
{
    Node* temp_node = list->first;
    list->first = list->first->next;
    list->free_value(temp_node->value);
    free(temp_node);

    list->size = list->size - 1;
}

void list_remove(List* list, int index) 
{
    if(index == 0)
    {
        list_remove_first(list);
        return;
    }

    Node* current_node = list->first;
    while(index-- != 1)
        current_node = current_node->next;

    Node* temp_node = current_node->next;
    current_node->next = current_node->next->next;
    list->free_value(temp_node->value);
    free(temp_node);

    list->size = list->size - 1;
}


void list_print(List* list, Print print_value)
{
    if(list->size == 0)
        return;

    Node* current_node = list->first;

    for(int i = 0; i < list->size - 1; i++)
    {
        print_value(current_node->value);
        printf("->");
        current_node = current_node->next;
    }

    print_value(current_node->value);
    printf("\n");
}
