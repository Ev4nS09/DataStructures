#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <signal.h>

#include "vector.h"
#include "vector_tests.h"

/* The tests will be done with integer values to simplify the tests. 
 This will not affect the effects of the functions being tested.
*/

#define BOLD_ON  "\e[1m"
#define BOLD_OFF "\e[m"
#define RED_ON "\033[31m"

int SHOW_PRINT = 0;

void sighandler(int);

void assert_test(int expr, int line, const char* function)
{
    if(expr)
    {
        printf(RED_ON "X Failed Test " BOLD_ON "%s()" BOLD_OFF RED_ON ". Line: " BOLD_ON "%d\n", function + 5, line);
        exit(1);
    }
}

#define ASSERT_TEST(expr) (assert_test(expr ? 0 : 1, __LINE__, __func__))

void seg_fault(int signum)
{
    printf("Segmentation Fault.");          
    exit(1);
}
    

int is_vector_equal_to_array(Vector* vector, int* array, int array_size)
{
    int result = 1;
    for(int i = 0; i < array_size; i++)
    {
        int current = *(int*) vector->array[i];

        if(current != array[i])
        {
            result = 0;
            break;
        }
    }

    return result;
}

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

int test_vector_init_empty()
{
    if(SHOW_PRINT) printf("Testing function," BOLD_ON " vector_init_empty" BOLD_OFF "...\n");

    Vector* vector = vector_init_empty(free_int);

    ASSERT_TEST(vector->capacity == DEFAULT_CAPACITY);
    ASSERT_TEST(vector->array != NULL);
    ASSERT_TEST(vector->size == 0);
    ASSERT_TEST(vector->free_value != NULL);

    return errno;
}

int test_vector_init()
{
    Vector* vector_1 = vector_init(32, free_int);

    ASSERT_TEST(vector_1->capacity == 32);
    ASSERT_TEST(vector_1->array != NULL);
    ASSERT_TEST(vector_1->size == 0);
    ASSERT_TEST(vector_1->free_value != NULL);

    return errno;
}

int test_vector_resize()
{
    Vector* vector = vector_init(16, free_int);
    return 0;
}    


int test_vector_add()
{
    Vector* vector = vector_init(16, free_int);

    return 0;
}

void test_vector(int show_print)
{
    signal(SIGSEGV, seg_fault);
    SHOW_PRINT = show_print;
    
    ASSERT_TEST(!test_vector_init_empty());
}
    

