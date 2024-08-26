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
  while(1){
  Type type_int = type_init(free_int, copy_int, cmp_int);

  HashMap* hash_map = hash_map_init(type_int, type_int, hash_int);

  for(int i = 0; i < 12; i++)
  {
    hash_map_put(hash_map, &i, &i);
  }

  hash_map_free(hash_map);
  }

  return 0;
}
