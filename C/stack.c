#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

Stack* stack_init(Free free_value)
{
  Stack* result = malloc(sizeof(Stack));
  result->list = list_init(free_value);
  result->size = 0;

  return result;
}

void stack_push(Stack* stack, void* value, Copy copy_value)
{
  list_add(stack->list, value, copy_value);
  stack->size = stack->list->size;
}

void* stack_pop(Stack* stack, Copy copy_value)
{
  if(stack->size == 0)
    return NULL;

  void* result = list_get_first(stack->list, copy_value);
  list_remove_first(stack->list);
  stack->size = stack->list->size;

  return result;
}

void* stack_peek(Stack* stack, Copy copy_value)
{
  return list_get_first(stack->list, copy_value);
}

void stack_print(Stack* stack, Print print_value)
{
  list_print(stack->list, print_value);
}

void stack_free(Stack* stack)
{
  list_free(stack->list);
  free(stack);
}
