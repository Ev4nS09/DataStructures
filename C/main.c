#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "vector.h"
#include "linkedlist.h"
#include "queue.h"
#include "stack.h"
#include "stack_vector.h"
#include "queue_vector.h"
#include "generic_type_functions.h"
#include "hash_map.h"

#define MAX_UNSIGNED_INT 4294967295

void free_int(void* integer)
{
  free((int*)integer);
}

void* copy_int(void* integer)
{
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

int cmp_less(void* value1, void* value2)
{
  return *(int*) value1 > *(int*) value2;
}

int hash_int(void* key)
{
  return (*(int*)key) & 0x7FFFFFFF;
}


int main()
{
  void* x = malloc(sizeof(void));

  unsigned int y =  (unsigned int) (((long long) x) % MAX_UNSIGNED_INT) & 0x7FFFFFF;

  printf("%d\n", y);

  free(x);

  return 0;
}
