#include <stdio.h>
#include <stdlib.h>

#include "vector.h"
#include "linkedlist.h"
#include "queue.h"
#include "stack.h"
#include "stack_vector.h"

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
  Queue* queue = queue_init(free_int);
  Stack* stack = stack_init(free_int);
  StackVector* stack_vector = stack_vector_init(free_int);

  for(int i = 0; i < 10; i++)
  {
    queue_enqueue(queue, &i, copy_int);
    stack_push(stack, &i, copy_int);
    stack_vector_push(stack_vector, &i, copy_int);
  }

  queue_dequeue(queue, copy_int);
  stack_pop(stack, copy_int);
  stack_vector_pop(stack_vector, copy_int);


  printf("%d ", *(int*)queue_peek(queue, copy_int));
  printf("%d ", *(int*)stack_peek(stack, copy_int));
  printf("%d\n", *(int*)stack_vector_peek(stack_vector, copy_int));

  

  queue_print(queue, print_int);
  stack_print(stack, print_int);
  stack_vector_print(stack_vector, print_int);

  queue_free(queue);
  stack_free(stack);
  stack_vector_free(stack_vector);

  Vector* v = vector_empty_init(free_int);

  for(int i = 0; i < 6; i++)
    vector_add(v, &i, copy_int);

  vector_remove(v, 2);

  vector_print(v, print_int);
}
