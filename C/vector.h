#ifndef vector_h
#define vector_h

#include "generic_type_functions.h"

typedef struct Vector
{
  void** array;
  int capacity;
  int size;
  void(*free_value)(void*);
}Vector;

Vector* vector_empty_init(Free free_value);

Vector* vector_init(int initial_capacity, Free free_value);

void free_vector(Vector* vector);

Vector* vector_init(int initial_capacity, Free free_value);

void vector_add(Vector* vector, void* value, Copy copy_value);

void vector_set(Vector* vector, void* value, int index);

void vector_add_at(Vector* vector, void* value, int index, Copy copy_value);

void vector_remove(Vector* vector, int index);

void vector_remove_from_to(Vector* vector, int from, int to);

void* vector_get(Vector* vector, int index);

void vector_set_size(Vector* vector, int new_size);

void vector_print(Vector* vector, Print print_value);

#endif
