#ifndef vector_h
#define vector_h

#include "generic_type_functions.h"

typedef struct Vector
{
  void** array;
  int capacity;
  int size;
  Free free_value;
}Vector;

/*
  Initializes an empty vector.
  All of the content of the struct vector are initialized as follows,
  Array: initializes all of the 16(initial capacity) * 8(size of void*) elements to null using calloc
  Capacity: is set to 16, since it is the default capicity
  Size: is set to 0
  Free: fucntion pointer to free the values that are going to be stored in the array
*/
Vector* vector_empty_init(Free free_value);

/*
  Initializes a vector with an initial capicity given by the user.
  All of the content of the struct vector are initialized as follows,
  Array: initializes all of the (initial capacity * 8(size of void*)) elements to null using calloc
  Capacity: is set to the initial capacity given by the user 
  Size: is set to 0
  Free: fucntion pointer to free the values that are going to be stored in the array
*/
Vector* vector_init(int initial_capacity, Free free_value);

/*
  Frees a vector given by it's user. The function iterates the array and frees every value from it using the function
*/
void free_vector(Vector* vector);

/*
  Adds and element to the vector, if the the size of the vector equals the capicity than we need to resize the array.
  We use the function resize and give the new capicty the following argument, vector->capacity * 2.
*/
void vector_add(Vector* vector, void* value, Copy copy_value);

/*
  Sets a value from the array for another one at a given index
*/
void vector_set(Vector* vector, void* value, int index);

/*

*/
void vector_add_at(Vector* vector, void* value, int index, Copy copy_value);

void vector_remove(Vector* vector, int index);

void vector_remove_from_to(Vector* vector, int from, int to);

void* vector_get(Vector* vector, int index);

void vector_set_size(Vector* vector, int new_size);

void vector_print(Vector* vector, Print print_value);

#endif
