#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "linkedlist.h"

Queue* queue_init(Free free_value)
{
  Queue* result = malloc(sizeof(Queue));

  result->list = list_init(free_value);
  result->size = 0;

  return result;
}

void queue_enqueue(Queue* queue, void* value, Copy copy_value)
{
  list_add_last(queue->list, value, copy_value);
  queue->size = queue->list->size;
}

void* queue_dequeue(Queue* queue, Copy copy_value)
{
  if(queue->size == 0)
    return NULL;

  void* result = list_get_first(queue->list, copy_value);
  list_remove_first(queue->list);
  queue->size = queue->list->size;

  return result;
}

void* queue_peek(Queue* queue, Copy copy_value)
{
  if(queue->size == 0)
    return NULL;

  return list_get_first(queue->list, copy_value);
}

void queue_enqueue_cmp(Queue* queue, void* value, Compare cmp, Copy copy_value)
{
  list_add_cmp(queue->list, value, cmp, copy_value);
  queue->size = queue->list->size;
}

void queue_print(Queue* queue, Print print_value)
{
  list_print(queue->list, print_value);
}

void queue_free(Queue* queue)
{
  list_free(queue->list);
  free(queue);
}
