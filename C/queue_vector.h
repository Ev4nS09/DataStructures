#ifndef queue_vector_h
#define queue_vector_h

#include "generic_type_functions.h"
#include "vector.h"

#define MINIMUM_SIZE 16

typedef struct QueueVector 
{
    Vector* vector;
    int queue_start_pointer;
}QueueVector;

QueueVector* queue_vector_init(Free free_value);

void queue_vector_enqueue(QueueVector* queue_vector, void* value, Copy copy_value);

void* queue_vector_dequeue(QueueVector* queue_vector, Copy copy_value);

void* queue_vector_peek(QueueVector* queue_vector, Copy copy_value);

void queue_vector_enqueue_cmp(QueueVector* queue_vector, void* value, Compare cmp, Copy copy_value);

void queue_vector_print(QueueVector* queue_vector, Print print_value);

void queue_vector_free(QueueVector* queue_vector);

#endif