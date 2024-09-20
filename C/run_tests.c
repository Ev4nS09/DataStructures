#include <stdio.h>
#include <stdlib.h>
#include "vector_tests.h"
#include "vector.h"
#include "tests_util.h"

#define BOLD_ON "\e[1m"
#define BOLD_OFF "\e[m"
#define RED_ON "\033[31m"
#define GREEN_ON "\033[32m"
#define COLOR_OFF "\033[m"

void *copy_int(void *integer) {
  if (integer == (void *)0)
    return NULL;

  int *result = malloc(sizeof(int));
  *result = *(int *)integer;

  return result;
}

void free_int(void *integer) { free((int *)integer); }

int main(int argc, char* argv[])
{
    Vector* v = vector_init_empty();

    for(int i = 0; i < MAX_CAPACITY; i++)
        vector_add(int*, v, copy_int(&i));
        //vector_add(int, v, i);

    vector_destroy(v, free_int);

    //test_vector(((int) argv[1][0]) - '0');

    if(NUM_OF_ERRORS == 0)
        printf(GREEN_ON " All Tests Passed.\n" COLOR_OFF);
    else
        printf(RED_ON "%d Tests failed.\n" COLOR_OFF, NUM_OF_ERRORS);
    
    return 0;
}

