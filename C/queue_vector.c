#include <stdio.h>
#include <stdlib.h>

#include "queue_vector.h"

QueueVector* queue_vector_init(Free free_value)
{
    QueueVector* result = malloc(sizeof(QueueVector));

    result->vector = vector_empty_init(free_value);
    result->queue_start_pointer = 0;

    return result;
}

void queue_vector_enqueue(QueueVector* queue_vector, void* value, Copy copy_value)
{
    vector_add(queue_vector->vector, value, copy_value);
}

void* queue_vector_dequeue(QueueVector* queue_vector, Copy copy_value)
{
    void* result = vector_get(queue_vector->vector, queue_vector->queue_start_pointer, copy_value);
    vector_set(queue_vector->vector, NULL, queue_vector->queue_start_pointer);
    queue_vector->queue_start_pointer = queue_vector->queue_start_pointer + 1;


    if(queue_vector->vector->size >= MINIMUM_SIZE && queue_vector->queue_start_pointer > queue_vector->vector->size >> 2)
    {
        vector_remove_from_to(queue_vector->vector, 0, queue_vector->queue_start_pointer);
        queue_vector->queue_start_pointer = 0;
    }

    return result;
}

void* queue_vector_peek(QueueVector* queue_vector, Copy copy_value)
{
    return vector_get(queue_vector->vector, queue_vector->queue_start_pointer, copy_value);
}

void queue_vector_enqueue_cmp(QueueVector* queue_vector, void* value, Compare cmp, Copy copy_value)
{
    for(int i = 0; i < queue_vector->vector->size; i++)
    {
        if(cmp(queue_vector->vector->array[i], value))
        {
            vector_add_at(queue_vector->vector, value, i, copy_value);
            return;
        }
    }

    vector_add(queue_vector->vector, value, copy_value);
    
}

void queue_vector_print(QueueVector* queue_vector, Print print_value)
{
    vector_print(queue_vector->vector, print_value);
}

void queue_vector_free(QueueVector* queue_vector)
{
    free_vector(queue_vector->vector);
    free(queue_vector);
}