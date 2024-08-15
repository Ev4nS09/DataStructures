#include <stdio.h>
#include <stdlib.h>

#include "stack_vector.h"

StackVector* stack_vector_init(Free free_value)
{
  StackVector* result = malloc(sizeof(StackVector));
  result->vector = vector_empty_init(free_value);

  return result;
}

void stack_vector_push(StackVector* stack_vector, void* value, Copy copy_value)
{
    vector_add(stack_vector->vector, value, copy_value);
}

void* stack_vector_peek(StackVector* stack_vector, Copy copy_value)
{
    return copy_value(vector_get(stack_vector->vector, stack_vector->vector->size - 1)); 
}

void* stack_vector_pop(StackVector* stack_vector, Copy copy_value)
{
    return copy_value(vector_get_remove(stack_vector->vector, stack_vector->vector->size - 1, copy_value));
}

void stack_vector_print(StackVector* stack_vector, Print print_value)
{
    vector_print(stack_vector->vector, print_value);
}

void stack_vector_free(StackVector* stack_vector)
{
    free_vector(stack_vector->vector);
    free(stack_vector);
}