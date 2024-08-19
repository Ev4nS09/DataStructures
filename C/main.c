#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "vector.h"
#include "linkedlist.h"
#include "queue.h"
#include "stack.h"
#include "stack_vector.h"
#include "queue_vector.h"


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

int main()
{
  int a = 2;
  typeof(a) b = 3;


  return 0;

}
