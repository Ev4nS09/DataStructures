#ifndef stack_h
#define stack_h

#include "generic_type_functions.h"
#include "linkedlist.h"

typedef struct Stack
{
  List* list;
  int size;
}Stack;

/*
  Initializes a stack and returns it
*/
Stack* stack_init(Free free_value);

/*
  Adds a value to the top of the stack
*/
void stack_push(Stack* stack, void* value, Copy copy_value);

/*
  Returns a copy of the top value of the stack and removes it
*/
void* stack_pop(Stack* stack, Copy copy_value);

/*
  Return a copy of the top value of the stack without removing it
*/
void* stack_peek(Stack* stack, Copy copy_value);

/*
  Prints the stack to the console
*/
void stack_print(Stack* stack, Print print_value);

/*
  Frees the stack
*/
void stack_free(Stack* stack);

#endif


