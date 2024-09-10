#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>

#include "vector.h"

void free_int(void* integer)
{
  free((int*)integer);
}

void* copy_int(void* integer)
{
    if(integer == (void*) 0)
        return NULL;

    int* result = malloc(sizeof(int));
    *result = *(int*)integer;

    return result;
}

void print_int(void* integer)
{
  printf("%d", *(int*)integer);
}

int cmp_int(void* value1, void* value2)
{
  return *(int*) value1 == *(int*) value2;
}

int vector_init_empty_test()
{
    Vector* v = vector_init_empty(free_int);

    if(v->capacity != DEFAULT_CAPACITY)
        return 1;
    else if(v->array == NULL)
        return 1;

    return errno;
}

int vector_ini_test()
{
    Vector* vector_1 = vector_init(32, free_int);
    Vector* vector_2 = vector_init(10, free_int);

    return 0;
}
