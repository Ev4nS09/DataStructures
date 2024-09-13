#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
#define GREEN_ON "\033[32m"
#define COLOR_OFF "\033[m" 


void sighandler(int);

void assert_test(int expr, int line, const char* function)
{
    if(expr)
    {
        printf(RED_ON "X Failed Test " BOLD_ON "%s" BOLD_OFF RED_ON ". Line: " BOLD_ON "%d\n", function + 5, line);
        exit(1);
    }
}


#define ASSERT_NAME(expr, func) (assert_test(expr ? 0 : 1, __LINE__, func))
#define ASSERT_TEST(expr) (ASSERT_NAME(expr, __func__))

int SHOW_PRINT = 0;
#define PRINT_TEST if(SHOW_PRINT) printf("Executing Test" BOLD_ON " %s"  BOLD_OFF "...\n", __func__ + 5)

#define CREATE_ARRAY(type, array_name, size) (type array_name[size]; for(int i = 0; i < size; i++) array_name[i] = i;)

void seg_fault(int signum)
{
    printf("Segmentation Fault.");          
    exit(1);
}
    
void print_int(void* integer)
{
  printf("%d", *(int*) integer);
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

void add_values_to_vector(Vector* vector, int number_of_values)
{
    for(int i = 0; i < number_of_values; i++)
    {
        int* value = malloc(sizeof(int));
        *value = i;
        vector_add(vector, value, NULL);
    }
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


int cmp_int(void* value1, void* value2)
{
  return *(int*) value1 == *(int*) value2;
}

int test_vector_free()
{
    PRINT_TEST;

    Vector* vector_1 = vector_init(MIN_CAPACITY, free_int);
    int* value_1 = malloc(sizeof(int)); *value_1 = 2;
    vector_1->array[5] = (void*) value_1;
    vector_free(vector_1);

    Vector* vector_2 = vector_init(MIN_CAPACITY, free_int);
    int* value_2 = malloc(sizeof(int)); *value_2 = 4564;
    vector_2->array[7] = (void*) value_2;
    vector_free(vector_2);

    Vector* vector_3 = vector_init(MIN_CAPACITY, free_int);
    int* value_3 = malloc(sizeof(int)); *value_3 = 34;
    vector_3->array[15] = (void*) value_3;
    vector_free(vector_3);

    return errno;
}

int test_vector_init_empty()
{
    PRINT_TEST;

    Vector* vector = vector_init_empty(free_int);

    ASSERT_TEST(vector->capacity == MIN_CAPACITY);
    ASSERT_TEST(vector->array != NULL);
    ASSERT_TEST(vector->size == 0);

    vector_free(vector);

    return errno;
}

int test_vector_init()
{ 
    PRINT_TEST;

    Vector* vector_1 = vector_init(32, free_int);
    ASSERT_TEST(vector_1->capacity == 32);
    ASSERT_TEST(vector_1->array != NULL);
    ASSERT_TEST(vector_1->size == 0);

    Vector* vector_2 = vector_init(10, free_int);
    ASSERT_TEST(vector_2->capacity == MIN_CAPACITY); 
    ASSERT_TEST(vector_2->array != NULL);
    ASSERT_TEST(vector_2->size == 0);

    vector_free(vector_1);
    vector_free(vector_2);

    return errno;
}

int test_vector_init_array()
{
    PRINT_TEST;

    int size_1 = 8;
    int** array_vector_1 = malloc(sizeof(int*) * size_1);

    for(int i = 0; i < size_1; i++)
        array_vector_1[i] = copy_int(&i);

    Vector* vector_1 = vector_init_array((void**) array_vector_1, size_1, free_int);

    int array_1[size_1]; for(int i = 0; i < size_1; i++) array_1[i] = i;
    ASSERT_TEST(is_vector_equal_to_array(vector_1, array_1, size_1));
    ASSERT_TEST(vector_1->capacity == size_1 * 2); 
    ASSERT_TEST(vector_1->array != NULL);
    ASSERT_TEST(vector_1->size == size_1);


    int size_2 = 32;
    int** array_vector_2 = malloc(sizeof(int*) * size_2);

    for(int i = 0; i < size_2; i++)
        array_vector_2[i] = copy_int(&i);

    Vector* vector_2 = vector_init_array((void**) array_vector_2, size_2, free_int);

    int array_2[size_2]; for(int i = 0; i < size_2; i++) array_2[i] = i;
    ASSERT_TEST(is_vector_equal_to_array(vector_2, array_2, size_2));
    ASSERT_TEST(vector_2->capacity == size_2 * 2); 
    ASSERT_TEST(vector_2->array != NULL);
    ASSERT_TEST(vector_2->size == size_2);


    vector_free(vector_1);
    vector_free(vector_2);

    return errno;

}

int test_vector_resize()
{
    PRINT_TEST;

    Vector* vector = vector_init_empty(free_int);

    ASSERT_TEST(!vector_resize(vector, 32));
    ASSERT_TEST(vector->capacity == 32);
    ASSERT_TEST(vector->array != NULL);

    ASSERT_TEST(vector_resize(vector, -2));
    ASSERT_TEST(vector->capacity == 32);
    ASSERT_TEST(vector->array != NULL);

    ASSERT_TEST(!vector_resize(vector, MAX_CAPACITY));
    ASSERT_TEST(vector->capacity == MAX_CAPACITY);
    ASSERT_TEST(vector->array != NULL);

    ASSERT_TEST(!vector_resize(vector, 353453));
    ASSERT_TEST(vector->capacity == 353453);
    ASSERT_TEST(vector->array != NULL);

    vector_free(vector);

    return errno;
}    


int test_vector_add()
{
    PRINT_TEST;

    Vector* vector_1 = vector_init(MIN_CAPACITY, free_int);
    for(int i = 0; i < 8; i++) 
       vector_add(vector_1, &i, copy_int); 

    ASSERT_TEST(vector_1->size == 8);
    ASSERT_TEST(vector_1->capacity == MIN_CAPACITY);

    //This method ensures that the copy function we pass is being used
    //if the function didn't work all numbers would be the last value i was
    //in this case all numbers would be 7, because the reference we pass is the same
    int array_1[8] = {0, 1, 2, 3, 4, 5, 6, 7}; 
    ASSERT_TEST(is_vector_equal_to_array(vector_1, array_1, 8));


    Vector* vector_2 = vector_init(MIN_CAPACITY, free_int);
    for(int i = 0; i < 30; i++) 
       vector_add(vector_2, &i, copy_int); 

    ASSERT_TEST(vector_2->size == 30);
    ASSERT_TEST(vector_2->capacity == 32);

    int array_2[30]; for(int i = 0; i < 30; i++) array_2[i] = i;
    ASSERT_TEST(is_vector_equal_to_array(vector_2, array_2, 30));


    Vector* vector_3 = vector_init(MIN_CAPACITY, free_int);
    
    int* p1 = malloc(sizeof(int)); *p1 = 1;
    int* p2 = malloc(sizeof(int)); *p2 = 2;
    int* p3 = malloc(sizeof(int)); *p3 = 3;
    int* p4 = malloc(sizeof(int)); *p4 = 4;
    int* p5 = malloc(sizeof(int)); *p5 = 5;

    vector_add(vector_3, p1, NULL); 
    vector_add(vector_3, p2, NULL); 
    vector_add(vector_3, p3, NULL); 
    vector_add(vector_3, p4, NULL); 
    vector_add(vector_3, p5, NULL); 

    ASSERT_TEST(p1 == vector_3->array[0]);
    ASSERT_TEST(p2 == vector_3->array[1]);
    ASSERT_TEST(p3 == vector_3->array[2]);
    ASSERT_TEST(p4 == vector_3->array[3]);
    ASSERT_TEST(p5 == vector_3->array[4]);


    vector_free(vector_1);
    vector_free(vector_2);
    vector_free(vector_3);

    return errno;
}

int test_vector_set()
{
    PRINT_TEST; 

    Vector* vector_1 = vector_init(MIN_CAPACITY, free_int);
    add_values_to_vector(vector_1, 8); 

    int* value = malloc(sizeof(int)); *value = 69; //( ͡° ͜ʖ ͡°)
    ASSERT_TEST(vector_set(vector_1, value, -6, copy_int)); 
    ASSERT_TEST(vector_set(vector_1, value, 65454, copy_int)); 
    ASSERT_TEST(!vector_set(vector_1, value, 3, copy_int)); 
    ASSERT_TEST(vector_1->array[3]);
    ASSERT_TEST(*(int*) vector_1->array[3] == *value);

    ASSERT_TEST(!vector_set(vector_1, value, 4, NULL)); 
    ASSERT_TEST(vector_1->array[4] == value);
    
    vector_free(vector_1);

    return errno;
}

int test_vector_remove()
{
    PRINT_TEST; 

    int capacity_1 = MIN_CAPACITY;
    Vector* vector_1 = vector_init(capacity_1, free_int);
    ASSERT_TEST(vector_remove(vector_1, 0));
    add_values_to_vector(vector_1, 8); 

    ASSERT_TEST(vector_remove(vector_1, -2));
    ASSERT_TEST(vector_remove(vector_1, 1000));
    ASSERT_TEST(!vector_remove(vector_1, 2)); 
    ASSERT_TEST(vector_1->array != NULL);
    ASSERT_TEST(vector_1->size == 7);
    ASSERT_TEST(vector_1->capacity == capacity_1);
    ASSERT_TEST(*(int*) vector_1->array[2] != 2);
    int array_1[7] = {0, 1, 3, 4, 5, 6, 7};
    ASSERT_TEST(is_vector_equal_to_array(vector_1, array_1, 7));
            

    int capacity_2 = 32;
    Vector* vector_2 = vector_init(capacity_2, free_int);
    add_values_to_vector(vector_2, 32 - 1); 
    for(int i = 0; i < capacity_2 * 0.75 - 1; i++)
        ASSERT_TEST(!vector_remove(vector_2, 0));

    ASSERT_TEST(vector_2->array != NULL);
    ASSERT_TEST(vector_2->capacity == capacity_2 >> 1);
    ASSERT_TEST(vector_2->size == 31 - (capacity_2 * 0.75 - 1));
    int array_2[8] = {23, 24, 25, 26, 27, 28, 29, 30};
    ASSERT_TEST(is_vector_equal_to_array(vector_2, array_2, 7));

    
    int capacity_3 = MIN_CAPACITY;
    Vector* vector_3 = vector_init(capacity_3, free_int);

    int value;
    value = 2; vector_add(vector_3, &value, copy_int); 
    value = 10; vector_add(vector_3, &value, copy_int); 
    value = 34; vector_add(vector_3, &value, copy_int); 
    value = 12; vector_add(vector_3, &value, copy_int); 
    value = 3; vector_add(vector_3, &value, copy_int); 
    value = -4; vector_add(vector_3, &value, copy_int); 
    value = -67; vector_add(vector_3, &value, copy_int); 
    value = 4363; vector_add(vector_3, &value, copy_int); 

        
    ASSERT_TEST(!vector_remove(vector_3, 2)); //{2, 10, 12, 3, -4, -67, 4363}
    ASSERT_TEST(!vector_remove(vector_3, 5)); //{2, 10, 12, 3, -4, 4363}
    ASSERT_TEST(!vector_remove(vector_3, 1)); //{2, 12, 3, -4, 4363}
    ASSERT_TEST(vector_remove(vector_3, 5));  //Error
    ASSERT_TEST(!vector_remove(vector_3, 0)); //{12, 3, -4, 4363}
    ASSERT_TEST(!vector_remove(vector_3, 3)); //{12, 3, -4}
    ASSERT_TEST(!vector_remove(vector_3, 0)); //{3, -4}

    int array_3[2] = {3, -4};
    ASSERT_TEST(is_vector_equal_to_array(vector_3, array_3, 2));

    vector_free(vector_1);
    vector_free(vector_2);
    vector_free(vector_3);

    return errno;
}

int test_vector_remove_from_to()
{
    PRINT_TEST;

    Vector* vector_1 = vector_init(MIN_CAPACITY, free_int);
    add_values_to_vector(vector_1, 10);


    ASSERT_TEST(vector_remove_from_to(vector_1, -1, 7));
    ASSERT_TEST(vector_remove_from_to(vector_1, 2, 99));

    int array_1[4] = {0, 1, 8, 9};
    ASSERT_TEST(!vector_remove_from_to(vector_1, 2, 7));
    ASSERT_TEST(is_vector_equal_to_array(vector_1, array_1, 4));
    ASSERT_TEST(vector_1->size == 4);
    ASSERT_TEST(vector_1->capacity == 16);
    ASSERT_TEST(is_vector_equal_to_array(vector_1, array_1, 4));


    Vector* vector_2 = vector_init(MIN_CAPACITY, free_int);
    add_values_to_vector(vector_2, 32);
    
    int array_2[4] = {0, 1, 30, 31};
    ASSERT_TEST(!vector_remove_from_to(vector_2, 2, 29));
    ASSERT_TEST(is_vector_equal_to_array(vector_2, array_2, 4));
    ASSERT_TEST(vector_2->size == 4);
    ASSERT_TEST(vector_2->capacity == 16);

    Vector* vector_3 = vector_init(256, free_int);
    add_values_to_vector(vector_3, 251);
    
    int array_3[5] = {0, 1, 248, 249, 250};
    ASSERT_TEST(!vector_remove_from_to(vector_3, 2, 247));
    ASSERT_TEST(is_vector_equal_to_array(vector_3, array_3, 5));
    ASSERT_TEST(vector_3->size == 5);
    ASSERT_TEST(vector_3->capacity == 20);

    Vector* vector_4 = vector_init(256, free_int);
    add_values_to_vector(vector_4, 256);
    
    int array_4[0] = {};
    ASSERT_TEST(!vector_remove_from_to(vector_4, 0, 255));
    ASSERT_TEST(is_vector_equal_to_array(vector_4, array_4, 0));
    ASSERT_TEST(vector_4->size == 0);
    ASSERT_TEST(vector_4->capacity == 16);

    vector_free(vector_1);
    vector_free(vector_2);
    vector_free(vector_3);
    vector_free(vector_4);

    return errno;
}

void test_vector(int show_print)
{
    printf(GREEN_ON BOLD_ON "Testing Vector.\n" BOLD_OFF COLOR_OFF);

    signal(SIGSEGV, seg_fault);
    SHOW_PRINT = show_print;
    
    ASSERT_TEST(!test_vector_free());
    ASSERT_TEST(!test_vector_init_empty());
    ASSERT_TEST(!test_vector_init());
    ASSERT_TEST(!test_vector_init_array());
    ASSERT_TEST(!test_vector_resize());
    ASSERT_TEST(!test_vector_add());
    ASSERT_TEST(!test_vector_set());
    ASSERT_TEST(!test_vector_remove());
    ASSERT_TEST(!test_vector_remove_from_to());
}
    

