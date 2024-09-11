#ifndef vector_int_h
#define vector_int_h

typedef struct Vector_int
{
  int* array;
  int capacity;
  int size;
}Vector_int;

Vector_int* vector_int_init(int initial_capacity);

void free_vector_int(Vector_int* vector);

Vector_int* vector_int_init(int initial_capacity);

void vector_int_add(Vector_int* vector, int value);

void vector_int_print(Vector_int* vector);

#endif
