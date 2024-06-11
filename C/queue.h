#ifndef queue_h 
#define queue_h 

#include "generic_type_functions.h"
#include "linkedlist.h"

typedef struct Queue
{
  List* list;
  int size;
}Queue;

/*
  Initializes a queue and returns it
*/
Queue* queue_init(Free free_value);

/*
  Adds a value to the end of the queue
*/
void queue_enqueue(Queue* queue, void* value, Copy copy_value);

/*
  Returns a copy of the first value of the queue and removes it
*/
void* queue_dequeue(Queue* queue, Copy copy_value);

/*
  Returns a copy of the first value of the queue without removing it
*/
void* queue_peek(Queue* queue, Copy copy_value);

/*
  Prints the queue to the console
*/
void queue_print(Queue* queue, Print print_value);

/*
  Frees a queue
*/
void queue_free(Queue* queue);

#endif
