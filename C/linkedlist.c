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

void list_add_at(List* list, void* value, int index, Copy copy_value)
{
  if(index == 0)
  {
    list_add(list, value, copy_value);
    return;
  }
  else if(index == list->size)
  {
    list_add_last(list, value, copy_value);
    return;
  }

  Node* current_node = list->first;

  while(index-- != 1)
   current_node = current_node->next; 

  current_node->next = node_init(current_node->next, copy_value(value));
  list->size = list->size + 1;
}

void list_add_cmp(List* list, void* value, Compare cmp, Copy copy_value)
{
  Node* current_node = list->first;
  
  while(current_node->next != NULL && !cmp(current_node->next->value, value))
    current_node = current_node->next;

  if(current_node == list->first)
    list_add(list, value, copy_value);
  else if(current_node == NULL)
    list_add_last(list, value, copy_value);
  else 
  {
    current_node->next = node_init(current_node->next, copy_value(value));
    list->size = list->size + 1;
  }

}

void list_remove_first(List* list)
{
    Node* temp_node = list->first;
    list->first = list->first->next;
    list->free_value(temp_node->value);
    free(temp_node);

    list->size = list->size - 1;
}

void list_remove_next_node(List* list, Node* node)
{
    Node* temp_node = node->next;
    node->next = node->next->next;
    list->free_value(temp_node->value);
    free(temp_node);

    list->size = list->size - 1;
}

void list_remove(List* list, int index) 
{
    if(index == 0 || list->size == 1)
      list_remove_first(list);
      
    
    Node* current_node = list->first;
    while(index-- > 1)
        current_node = current_node->next;

    list_remove_next_node(list, current_node);

}

void list_remove_all_value(List* list, void* value, Compare cmp)
{
    Node* current_node = list->first;

    while(current_node != NULL && cmp(current_node->value, value))
    {
        current_node = current_node->next;    
        list_remove_first(list);
    }

    while(current_node != NULL && current_node->next != NULL) 
    {
        if(cmp(current_node->next->value, value))
            list_remove_next_node(list, current_node);
        else 
          current_node = current_node->next;
    }
}

void* list_get_first(List* list, Copy copy_value)
{
  return copy_value(list->first->value);
}

void* list_get_last(List* list, Copy copy_value)
{
  return copy_value(list->last->value);
}

void* list_get_at(List* list, int index, Copy copy_value)
{
  if(index == 0)
    return list_get_first(list, copy_value);
  else if(index == list->size - 1)
    return list_get_last(list, copy_value);

  Node* current_node = list->first;

  while(index-- != 0)
    current_node = current_node->next;

  return copy_value(current_node->value);
    
}

int list_contains_value(List* list, void* value, Compare cmp)
{
  int result = 0;
  Node* current_node = list->first;

  while(current_node != NULL)
  {
    if(cmp(current_node->value, value))
    {
      result = 1;
      break;
    }
    
    current_node = current_node->next;
  }

  return result;
}

void swap_node_values(Node* node1, Node* node2)
{
  void* value = node1->value;
  node1->value = node2->value;
  node2->value = value;
}

void list_insertion_sort(List* list, Compare cmp)
{
  Node* current_node_i = list->first;
  Node* current_node_j = list->first->next;

  for(int i = 0; i < list->size - 1; i++)
  {
    for(int j = i+1; j < list->size; j++)
    {
      if(cmp(current_node_i->value, current_node_j->value)) 
        swap_node_values(current_node_i, current_node_j);

      current_node_j = current_node_j->next;
    }

    current_node_i = current_node_i->next;
    current_node_j = current_node_i->next;
  }
}

int list_to_array(List* list, void** array, Copy copy_value)
{
  int result = 0;
  Node* current_node = list->first;

  for(int i = 0; i < list->size; i++)
  {
    array[result++] = copy_value(current_node->value);
    current_node = current_node->next;
  }

  return result;
}

List* list_array_to_list(void** array, int array_size, Free free, Copy copy_value) 
{
  List* result = list_init(free);

  for(int i = 0; i < array_size; i++)
    list_add_last(result, array[i], copy_value);

  return result;
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
