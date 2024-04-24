#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector_int.h"

#define INITIAL_CAPACITY 16

void error_handler(char* message)
{
  printf("Error: %s\n", message);
  exit(1);
}

void free_vector_int(Vector_int* vector)
{
  free(vector->array);
  free(vector);
}

Vector_int* vector_int_init(int initial_capacity)
{
  if(initial_capacity < 0)
    error_handler("Invalid capicity");

  Vector_int* result = malloc(sizeof(Vector_int));
  result->array = calloc(initial_capacity, sizeof(int));
  result->capacity = initial_capacity > 0 ? initial_capacity : INITIAL_CAPACITY;
  result->size = 0;
  
  return result;
}

void vector_int_resize(Vector_int* vector, int new_capacity)
{
  if(new_capacity < vector->size)
    error_handler("New capacity out of bounds");

  int* resized_array = realloc(vector->array, new_capacity * sizeof(int));

  vector->array = resized_array;
  vector->capacity = new_capacity;
}


void vector_int_add(Vector_int* vector, int value)
{
  vector->array[vector->size] = value;
  vector->size = vector->size + 1;

  if(vector->size >= vector->capacity)
    vector_int_resize(vector, vector->capacity << 1);
}


void vector_int_print(Vector_int* vector)
{
  printf("Vector: ");
  if(vector->size == 0)
    printf("[]\n");
  else 
  {
    printf("[");
    for(int i = 0; i < vector->size - 1; i++)
    {
        printf("%d", vector->array[i]);
      printf(", ");
    }
      printf("%d", vector->array[vector->size-1]);
    printf("]\n");
  }
  
  printf("Capacity: %d\n", vector->capacity);
  printf("Size: %d\n", vector->size);
}



