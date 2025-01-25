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

void print_int(void* v)
{
    printf("%d", (*(int*) v));
}

void free_int2(void *integer) { free((int *)integer); }

int main()
{

    double* f = malloc(sizeof(double));

    int x = 1;
    double y = 2.1;

    ((int*) f)[0] = x;  
    ((int*) f)[1] = y;  

    printf("%d %lf\n", ((int*) f)[0], *((double*)(((int*) f) + 1)));

   //while(1){ 
    Vector* v = vector_init(1, sizeof(int));
    printf("%d\n", v->capacity);

    for(int i = 0; i < 32; i++)
        vector_add(v, i);


    int t = _vector_get_remove(int, v, 6, NULL);

    vector_print(v, print_int);
    printf("%d\n", t);


    vector_destroy(v, NULL);
    //}

    //test_vector(((int) argv[1][0]) - '0');
    //

    if(NUM_OF_ERRORS == 0)
        printf(GREEN_ON " All Tests Passed.\n" COLOR_OFF);
    else
        printf(RED_ON "%d Tests failed.\n" COLOR_OFF, NUM_OF_ERRORS);
    
    return 0;
}

