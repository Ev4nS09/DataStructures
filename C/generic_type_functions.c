#include "generic_type_functions.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Type
{
    Free free_value;
    Copy copy_value;
    Compare compare_value;
}Type;

Type type_init(Free free_value, Copy copy_value, Compare compare_value)
{
  Type result;
  result.free_value = free_value;
  result.copy_value = copy_value;
  result.compare_value = compare_value;

  return result;
}

void free_generic(void* value)
{
    free(value);
}

void* copy_generic(void* value)
{
    if(value == (void*) 0)
        return NULL;

    long double* result = malloc(sizeof(long double));
    *result = *(long double*) value;

    return result;
}

int compare_generic(void* value1, void* value2)
{
    return *(long double*) value1 > *(long double*) value2 ? 1 : 0;
}

void print_generic(void* value)
{
  printf("%Lf\n", *(long double*) value);  
}
    

