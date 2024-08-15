#ifndef stack_vector_h
#define stack_vector_h

#include "generic_type_functions.h"
#include "vector.h"

typedef struct StackVector
{
  Vector* vector;
}StackVector;

StackVector* stack_vector_init(Free free_value);

void stack_vector_push(StackVector* stack_vector, void* value, Copy copy_value);

void* stack_vector_peek(StackVector* stack_vector, Copy copy_value);

void* stack_vector_pop(StackVector* stack_vector, Copy copy_value);

void stack_vector_print(StackVector* stack_vector, Print print_value);

void stack_vector_free(StackVector* stack_vector);

#endif