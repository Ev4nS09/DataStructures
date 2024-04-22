#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 16

typedef struct Vector
{
  void** array;
  int capacity;
  int size;
  void(*free_value)(void*);
}Vector;

void free_array(void** array, int size, void (*free_value)(void*))
{
  for(int i = 0; i < size; i++)
    free_value(array[i]);
}

Vector* vector_empty_init(void (*free_value)(void*))
{
  Vector* result = calloc(INITIAL_CAPACITY, sizeof(Vector));

  result->array = malloc(sizeof(void*));
  result->capacity = 0;
  result->size = 0;
  result->free_value = free_value;

  return result;
}

Vector* vector_init(int initial_capacity, void (*free_value)(void*))
{
  Vector* result = malloc(sizeof(Vector));

  result->array = calloc(initial_capacity, sizeof(void*));
  result->capacity = initial_capacity;
  result->size = 0;
  result->free_value = free_value;
  
  return result;
}

void vector_resize(Vector* vector, int new_capacity)
{
  void** resized_array = realloc(vector, new_capacity);
  void** temp_array = vector->array;

  vector->array = resized_array;
  vector->capacity = new_capacity;

  free(temp_array);
}


void vector_add(Vector* vector, void* value)
{
  vector->array[vector->size] = value;
  vector->size = vector->size + 1;

  if(vector->size >= vector->capacity)
    resize_vector(vector, vector->capacity*2);
}


void free_vector(Vector* vector)
{
  free_array(vector->array, vector->size, vector->free_value);
  free(vector->array);
  free(vector);
}

void free_value(void* integer)
{
  free(integer);
}

int main()
{
  while(1){
  Vector* vector = vector_init(2, free_value);
  int *n = malloc(sizeof(int));
  *n = 2;
  int *m = malloc(sizeof(int));
  *m = 3;
  vector_add(vector, n);
  vector_add(vector, m);

  free_vector(vector);
  }
  return 0;
}
