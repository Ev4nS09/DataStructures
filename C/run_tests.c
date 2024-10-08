#include <stdio.h>
#include <stdlib.h>
#include "vector_tests.h"
#include "vector.h"
#include "tests_util.h"
#include "my_error.h"

#define BOLD_ON "\e[1m"
#define BOLD_OFF "\e[m"
#define RED_ON "\033[31m"
#define GREEN_ON "\033[32m"
#define COLOR_OFF "\033[m"

void *copy_int2(void *integer) {
  if (integer == (void *)0)
    return NULL;

  int *result = malloc(sizeof(int));
  *result = *(int *)integer;

  return result;
}

void free_int2(void *integer) { free((int *)integer); }

int main()
{
    Vector* v = vector_init(128, sizeof(int));

    for(int i = 0; i < 32; i++)
        vector_add(v, i);

    printf("%d\n", vector_add(v, 24342));
    printf("%d\n", *(int*) v);

    printf("%p %p %p %p %p %p\n", v, v+1, &v->capacity, &v->size, &v->type_size, &v->array);
    




    vector_destroy(v, NULL);

    //test_vector(((int) argv[1][0]) - '0');

    if(NUM_OF_ERRORS == 0)
        printf(GREEN_ON " All Tests Passed.\n" COLOR_OFF);
    else
        printf(RED_ON "%d Tests failed.\n" COLOR_OFF, NUM_OF_ERRORS);
    
    return 0;
}

