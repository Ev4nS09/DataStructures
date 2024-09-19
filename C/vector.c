/*
  Author: Afonso Rio Soares da Silva
  Version: 1.0
  Date: 24/04/2024

  THe code below implements a generic type vector in C, so it uses an array of pointers to the values you add
  to that array.

  REMINDER: THE CODE WILL NOT STOP YOU FROM USING ALL THE MEMORY YOU HAVE ON YOUR PC, SO USE IT WISELY AND AT YOUR
  OWN RISK!!
*/

#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>

#include "vector.h"
#include "generic_type_functions.h"


Vector* vector_init_empty()
{
  Vector* result = malloc(sizeof(Vector));

  result->array =  calloc(MIN_CAPACITY, sizeof(void*));
  result->capacity = MIN_CAPACITY;
  result->size = 0;

  return result;
}

Vector* vector_init(unsigned int initial_capacity)
{
  if(initial_capacity > MAX_CAPACITY)
    return NULL;
    
  Vector* result = malloc(sizeof(Vector));
  result->capacity = initial_capacity > MIN_CAPACITY ? initial_capacity : MIN_CAPACITY;
  result->array = calloc(initial_capacity, sizeof(void*));
  result->size = 0;
  
  return result;
}

Vector* vector_init_array(void** array, unsigned int array_size, unsigned int array_capacity)
{
    if(array_size > MAX_CAPACITY >> 1 || array_size > array_capacity || array_capacity > MAX_CAPACITY)
        return NULL;

    if(array_capacity < MIN_CAPACITY)
    {
        array_capacity = MIN_CAPACITY;
        array = realloc(array, sizeof(void*) * array_capacity);
    }

    Vector* result = malloc(sizeof(Vector));
    result->array = array;
    result->size = array_size;
    result->capacity = array_capacity;

    return result;
}

void vector_destroy(Vector* vector, Free free_value)
{
  for(int i = 0; i < vector->size && free_value; i++) 
    free_value(vector->array[i]);

  free(vector->array);
  free(vector);
}

Vector* vector_copy(Vector* vector, Copy copy_value)
{
  if(!vector)
    return NULL;

  Vector* result = malloc(sizeof(Vector));

  result->array = malloc(sizeof(void*) * vector->size);

  for(int i = 0; i < vector->size; i++)
    result->array[i] = COPY(copy_value, vector->array[i]);

  result->size = vector->size;
  result->capacity = vector->capacity;

  return result;
}


int vector_resize(Vector* vector, unsigned int new_capacity)
{
  if(new_capacity < vector->size || new_capacity > MAX_CAPACITY || new_capacity < MIN_CAPACITY)
    return 1;

  void** resized_array = realloc(vector->array, new_capacity * sizeof(void*));

  vector->array = resized_array;
  vector->capacity = new_capacity;

  return 0; 
}


int _vector_add(Vector* vector)
{
  if(vector->size == MAX_CAPACITY)
    return 1;

  if(vector->size >= vector->capacity)
    vector_resize(vector, vector->capacity << 1);

  vector->size = vector->size + 1;

  return 0;
}

int vector_set(Vector* vector, void* value, unsigned int index, Copy copy_value, Free free_value)
{
 if(index >= vector->size)
    return 1; 

  void* temp_value = vector->array[index];
  vector->array[index] = copy_value ? copy_value(value) : value;

  if(temp_value != NULL)
    free_value(temp_value);

  return 0;
}

int vector_add_at(Vector* vector, void* value, unsigned int index, Copy copy_value)
{
  if(index > vector->size)
   return 1; 

  if(vector->array[index] != NULL)
    memmove(vector->array + index+1, vector->array + index, (vector->size - index) * sizeof(void*));
    
  vector->array[index] = copy_value ? copy_value(value) : value;
  vector->size = vector->size + 1;

  if(vector->size >= vector->capacity)
    vector_resize(vector, vector->capacity << 1);

  return 0;
}

int vector_remove(Vector* vector, unsigned int index, Free free_value)
{
  if(index >= vector->size)
    return 1;

  vector_set(vector, NULL, index, NULL, free_value);
  memmove(vector->array + index, vector->array + index+1, (vector->size - (index+1)) * sizeof(void*));

  vector->size = vector->size - 1;

  if(vector->size <= vector->capacity >> 2)
    vector_resize(vector, vector->capacity >> 1);

  return 0;
}

int vector_remove_from_to(Vector* vector, unsigned int from, unsigned int to, Free free_value)
{
  if(from >= vector->size || to >= vector->size)
    return 1;

  if(from > to)
  {
    int temp = from;
    from = to;
    to = temp;
  }

  for(int i = from; i <= to; i++)
    vector_set(vector, NULL, i, NULL, free_value);

  memmove(vector->array + from, vector->array + to + 1, (vector->size - to) * sizeof(void*));
  
  vector->size = vector->size - (to - from + 1);
  
  if(vector->size <= vector->capacity >> 2)
    vector_resize(vector, vector->size << 2 > MIN_CAPACITY ? vector->size << 2 : MIN_CAPACITY);

  return 0;
}

void* vector_get(Vector* vector, unsigned int index, Copy copy_value)
{
  if(!vector || index >= vector->size)
    return NULL;

  return COPY(copy_value, vector->array[index]);
}

void* vector_get_remove(Vector* vector, unsigned int index, Copy copy_value, Free free_value)
{
  if(!vector || index >= vector->size)
    return NULL;

  void* result = COPY(copy_value, vector->array[index]);

  if(copy_value)
    vector_remove(vector, index, free_value);
  else 
    vector->array[index] = NULL; 

  return result;
}


int vector_set_size(Vector* vector, unsigned int new_size, Free free_value)
{
    if(!vector)
        return 1;

    for(int i = vector->size; i < new_size; i++)
        vector_add(void*, vector, NULL);

    if(vector->size >  new_size)
        vector_remove_from_to(vector, new_size, vector->size - 1, free_value);
  
    vector->size = new_size;

    return 0;
}

int vector_set_capacity(Vector* vector, unsigned int new_capacity, Free free_value)
{
    if(!vector || new_capacity > MAX_CAPACITY || new_capacity < MIN_CAPACITY)
        return 1;

    if(vector->size > new_capacity)
        vector_remove_from_to(vector, new_capacity++, vector->size - 1, free_value);

    vector_resize(vector, new_capacity);  

    return 0;
}

void vector_print(Vector* vector, Print print_value)
{
  if(!vector)
  {
    printf("Vector: NULL\n");
    return;
  }

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
        print_value(vector->array[i]);
      printf(", ");
    }
    if(vector->array[vector->size-1] == (void*) 0)
      printf("NULL");
    else
      print_value(vector->array[vector->size-1]);
    printf("]\n");
  }
  
  printf("Capacity: %d\n", vector->capacity);
  printf("Size: %d\n", vector->size);
}



