#ifndef vector_h
#define vector_h

#include <stdlib.h>
#include <limits.h>
#include "generic_type_functions.h"

#define MIN_CAPACITY 16
#define MAX_CAPACITY (UINT_MAX >> 3)

#define getp(type, vector, index) ((((type*) vector->array)[index]))

#define vector_add(vector, value) \
(!_vector_add(vector) ? (getp(typeof(value), vector, vector->size - 1) = value) : (0))

#define vector_get(type, vector, index) \
(_vector_get(vector, index) ? getp(type, vector, index) : (0))

#define vector_set(vector, value, index) \
(!_vector_set(vector, index, NULL) ? getp(typeof(value), vector, index) = value : (0))

#define vector_set_free(vector, value, index, free) \
(!_vector_set(vector, index, free) ? getp(typeof(value), vector, index) = value : (0))

#define _vector_get_remove(type, vector, index, free_value) \
       (vector_get(type, vector, index)); vector_remove(vector, index, free_value) 

#define copyv(type, original, copy) \
    for(int i = 0; i < copy->size; i++) {\
        getp(type, copy, i) = getp(type, original, i);}

#define _vector_copy(type, original, copy, copy_value) \
    if((copy = vector_copy(original, copy_value)) && copy_value == NULL){\
        copyv(type, original, copy)}\
        
        
        

/*
  A vector is just a struct that stores an array, it's size, and it's capicity.
  The size is the number of elemtns the array currenlty have 
  and the capacity is the 'actual' size of the array in memory.
  The magic of the vector is if we add a value to it and the numbe rof elemnts reaches the limit in memory
  we resize it to the double ammout of the previous capicity.
  It is advised to initialize the capicity of the vector to a power of two, so memory is less likely
  to be fragmented. 

*/
typedef struct Vector
{
    unsigned int capacity;
    unsigned int size;
    size_t type_size;
    void** array;
}Vector;

/*
  Initializes an empty vector.
  All of the content of the struct vector are initialized as follows,
  Array: initializes all of the 16(initial capacity) * 8(size of void*) elements to null using calloc
  Capacity: is set to 16, since it is the default capicity

  Free: fucntion pointer to free the values that are going to be stored in the array
*/
Vector* vector_init_empty(size_t type_size);

/*
  Initializes a vector with an initial capicity given by the user.
  All of the content of the struct vector are initialized as follows,
  Array: initializes all of the (initial capacity * 8(size of void*)) elements to null using calloc
  Capacity: is set to the initial capacity given by the user 
  Size: is set to 0
  Free: fucntion pointer to free the values that are going to be stored in the array
*/
Vector* vector_init(unsigned int initial_capacity, size_t type_size);

Vector* vector_init_array(void** array, unsigned int array_size, unsigned int array_capacity, size_t type_size);

Vector* vector_copy(Vector* vector, Copy copy_value);

/*
  Destroys a vector given by it's user. The function iterates the array and frees every value from it using the function
*/
void vector_destroy(Vector* vector, Free free_value);

int vector_resize(Vector* vector, unsigned int new_capacity);

/*
  Adds an element to the vector, if the the size of the vector equals the capicity than we need to resize the array.
  We use the function resize and give the new capicty the following argument, vector->capacity * 2.
*/
int _vector_add(Vector* vector);


/*
  Sets a value from the array for another one at a given index
*/
int _vector_set(Vector* vector, unsigned int index, Free free_value); 

/*
Adds an element to a vector like the fucntion 'vector_add' at a given position
*/
int vector_add_at(Vector* vector, void* value, unsigned int index, Copy copy_value);

/*
  Removes an element from the vector at a given position, and it frees the value that was stored
*/
int vector_remove(Vector* vector, unsigned int index, Free free_value);

/*
  Removes a chunk of elements from an index 'from' to an index 'to' inclusive
*/
int vector_remove_from_to(Vector* vector, unsigned int from, unsigned int to, Free free_value);

/*
  Return the value at the position given from the vector
*/
void* _vector_get(Vector* vector, unsigned int index);

void** vector_get_remove(Vector* vector, unsigned int index);

/*
  Sets the size of the array to the given one. If the the new size is less than the previous one 
  the values that "overflow" the vector with the new size will be freed. If the size is bigger than the previous
  size then the values that would be empty will be set to null.
*/
int vector_set_size(Vector* vector, unsigned int new_size, Free free_value);

int vector_set_capacity(Vector* vector, unsigned int new_capacity, Free free_value);

/*
  Prints a given vector
*/
void vector_print(Vector* vector, Print print_value);

#endif
