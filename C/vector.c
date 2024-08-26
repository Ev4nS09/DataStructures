/*
  Author: Afonso Rio Soares da Silva
  Version: 1.0
  Date: 24/04/2024

  THe code below implements a generic type vector in C, so it uses an array of pointers to the values you add
  to that array.

  REMINDER: THE CODE WILL NOT STOP YOU FROM USING ALL THE MEMORY YOU HAVE ON YOUR PC, SO USE IT WISELY AND AT YOUR
  OWN RISK!!
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"
#include "generic_type_functions.h"

void error_handler(char* message)
{
  printf("Error: %s\n", message);
  exit(1);
}

void free_array(void** array, int size, void (*free_value)(void*))
{
  for(int i = 0; i < size; i++)
    free_value(array[i]);
}

void free_vector(Vector* vector)
{
  free_array(vector->array, vector->size, vector->free_value);
  free(vector->array);
  free(vector);
}

Vector* vector_empty_init(void (*free_value)(void*))
{
  Vector* result = malloc(sizeof(Vector));

  result->array =  calloc(INITIAL_CAPACITY, sizeof(void*));
  result->capacity = INITIAL_CAPACITY;
  result->size = 0;
  result->free_value = free_value;

  return result;
}

Vector* vector_init(int initial_capacity, void (*free_value)(void*))
{
  if(initial_capacity < 0)
    error_handler("Invalid capicity");

  Vector* result = malloc(sizeof(Vector));
  result->array = calloc(initial_capacity, sizeof(void*));
  result->capacity = initial_capacity > 0 ? initial_capacity : INITIAL_CAPACITY;
  result->size = 0;
  result->free_value = free_value;
  
  return result;
}

Vector* vector_init_array(void** array, int array_size, Free free_value)
{
  Vector* result = malloc(sizeof(Vector));
  result->array = array;
  result->size = array_size;
  result->capacity = array_size * 2;
  result->free_value = free_value;

  return result;
}


void vector_resize(Vector* vector, int new_capacity)
{
  if(new_capacity < vector->size)
    error_handler("New capacity out of bounds");

  void** resized_array = realloc(vector->array, new_capacity * sizeof(void*));

  vector->array = resized_array;
  vector->capacity = new_capacity;
}


void vector_add(Vector* vector, void* value, void*(*copy_value)(void*))
{
  vector->array[vector->size] = copy_value(value);
  vector->size = vector->size + 1;

  if(vector->size >= vector->capacity)
    vector_resize(vector, vector->capacity << 1);
}

void vector_add_no_copy(Vector* vector, void* value)

void vector_set(Vector* vector, void* value, int index)
{
 if(index < 0 || index >= vector->size)
    error_handler("Index out of bounds");

  void* temp_value = vector->array[index];
  vector->array[index] = value;

  if(temp_value != (void*) 0)
    vector->free_value(temp_value);
}

void vector_add_at(Vector* vector, void* value, int index, void*(*copy_value)(void*))
{
  if(index < 0)
    error_handler("Index out of bounds");

  if(index >= vector->size)
    vector_set_size(vector, index);

  memmove(vector->array + index+1, vector->array + index, (vector->size - index) * sizeof(void*));
  vector->array[index] = copy_value(value);
  vector->size = vector->size + 1;

  if(vector->size >= vector->capacity)
    vector_resize(vector, vector->capacity * 2);

}

void vector_remove(Vector* vector, int index)
{
  vector_set(vector, 0, index);
  memmove(vector->array + index, vector->array + index+1, (vector->size - (index+1)) * sizeof(void*));

  vector->size = vector->size - 1;

  if(vector->size <= vector->capacity >> 2)
    vector_resize(vector, vector->capacity >> 1);
}

void vector_remove_from_to(Vector* vector, int from, int to)
{
  if(from < 0 || to < 0 || from > vector->size || to > vector-> size)
    error_handler("Invalid range");

  if(from > to)
  {
    int temp = from;
    from = to;
    to = temp;
  }
  else if(from == to)
  {
    vector_remove(vector, from);
    return;
  }

  for(int i = from; i < to; i++)
    vector_set(vector, NULL, i);

  memmove(vector->array + from, vector->array + to, (vector->size - (to)) * sizeof(void*));
  
  vector->size = vector->size - (to - from);
  
  if(vector->size <= vector->capacity >> 2)
    vector_resize(vector, vector->capacity >> 1);
}

void* vector_get(Vector* vector, int index, Copy copy_value)
{
  if(index < 0 || index >= vector->size)
    error_handler("Index out of bounds");

  return copy_value(vector->array[index]);
}

void* vector_get_remove(Vector* vector, int index, Copy copy_value)
{
  void* result = copy_value(vector->array[index]);
  vector_remove(vector, index);

  return result;
}

//This fucntion is private 
void* return_null_pointer(void* p)
{
  return (void*) 0;
}

void vector_set_size(Vector* vector, int new_size)
{
  if(new_size < 0)
    error_handler("Invalid size, the new size must be greater than 0");

  if(new_size > vector->size)
  {
    for(int i = vector->size; i < new_size; i++)
      vector_add(vector, (void*) 0, return_null_pointer);
  } 
  else if(new_size < vector->size)
  {
    vector_remove_from_to(vector, new_size, vector->size);
    vector->size = new_size;
  }
}

void vector_print(Vector* vector, void(*print)(void*))
{
  printf("Vector: ");
  if(vector->size == 0)
    printf("[]\n");
  else 
  {
    printf("[");
    for(int i = 0; i < vector->size - 1; i++)
    {
      if(vector->array[i] == (void*) 0)
        printf("NULL");
      else 
        print(vector->array[i]);
      printf(", ");
    }
    if(vector->array[vector->size-1] == (void*) 0)
      printf("NULL");
    else
      print(vector->array[vector->size-1]);
    printf("]\n");
  }
  
  printf("Capacity: %d\n", vector->capacity);
  printf("Size: %d\n", vector->size);
}



