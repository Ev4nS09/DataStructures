#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <features.h>
#include <signal.h>
#include <errno.h>

#include "vector.h"
#include "linkedlist.h"
#include "queue.h"
#include "stack.h"
#include "stack_vector.h"
#include "queue_vector.h"
#include "generic_type_functions.h"

#define MAX_UNSIGNED_INT 4294967295
#define BOLD_ON  "\e[1m"
#define BOLD_OFF "\e[m"
#define RED_ON "\033[31m"

void sighandler(int);

void _assert(int expr, int line, const char* function)
{
    if(expr)
    {
        printf(RED_ON "Failed Test in line " BOLD_ON "%d" BOLD_OFF RED_ON " and function " BOLD_ON "%s()" BOLD_OFF "\n", line, function);
        exit(1);
    }
}

#define ASSERT(expr) (_assert(expr ? 0 : 1, __LINE__, __func__))


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

int cmp_less(void* value1, void* value2)
{
  return *(int*) value1 > *(int*) value2;
}

int hash_int(void* key)
{
  return (*(int*)key) & 0x7FFFFFFF;
}

int seg_fault()
{
    int* a = malloc(sizeof(int));
    *(a + 502342) = 4363634;

    return 0;
}

void sighandler(int signum) {
   printf("Caught signal %d, coming out...\n", __LINE__);
   exit(1);
}

int x(int y)
{
    return y;
}

int main()
{
    Vector* v = vector_init_empty(free_int);
    for(int i = 0; i < 15; i++)
        vector_add(v, &i, copy_int);


    Vector* copy_v = vector_copy(v, copy_int);

    int x = 2;
    vector_set(v, &x, 0, copy_int);

    vector_remove_from_to(v, 3, 7);

    vector_print(v, print_int);
    vector_print(copy_v, print_int);

    vector_free(v); 
    vector_free(copy_v);

    //signal(SIGSEGV, sighandler); 

    //MY_ASSERT(1);

    ASSERT(1 == 2);

    return 0;
}
