#include <errno.h>
#include <error.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "tests_util.h"
#include "vector.h"
#include "vector_tests.h"

/* The tests will be done with integer values to simplify the tests.
 This will not affect the effects of the functions being tested.
*/

void print_int(void *integer) { printf("%d", *(int *)integer); }


int is_vector_equal_to_array(Vector *vector, int *array, int array_size) {
  int result = 1;
  for (int i = 0; i < array_size; i++) {
    int current = *(int *)vector->array[i];

    if (current != array[i]) {
      result = 0;
      break;
    }
  }

  return result;
}

void add_values_to_vector(Vector *vector, int number_of_values) {
  for (int i = 0; i < number_of_values; i++) {
    int *value = malloc(sizeof(int));
    *value = i;
    vector_add(int*, vector, value);
  }
}

void free_int(void *integer) { free((int *)integer); }

void *copy_int(void *integer) {
  if (integer == (void *)0)
    return NULL;

  int *result = malloc(sizeof(int));
  *result = *(int *)integer;

  return result;
}

int cmp_int(void *value1, void *value2) {
  return *(int *)value1 == *(int *)value2;
}

int test_vector_destroy() {
  PRINT_TEST;

  Vector *vector_1 = vector_init(MIN_CAPACITY);
  int *value_1 = malloc(sizeof(int));
  *value_1 = 2;
  vector_1->array[5] = (void *)value_1;
  vector_1->size = 6;
  vector_destroy(vector_1, free_int);

  Vector *vector_2 = vector_init(MIN_CAPACITY);
  int *value_2 = malloc(sizeof(int));
  *value_2 = 4564;
  vector_2->array[7] = (void *)value_2;
  vector_2->size = 8;
  vector_destroy(vector_2, free_int);

  Vector *vector_3 = vector_init(MIN_CAPACITY);
  int *value_3 = malloc(sizeof(int));
  *value_3 = 34;
  vector_3->array[15] = (void *)value_3;
  vector_3->size = 16;
  vector_destroy(vector_3, free_int);

  return errno;
}

int test_vector_init_empty() {
  PRINT_TEST;

  Vector *vector = vector_init_empty();

  ASSERT_TEST(vector->capacity == MIN_CAPACITY);
  ASSERT_TEST(vector->array != NULL);
  ASSERT_TEST(vector->size == 0);

  vector_destroy(vector, free_int);

  return errno;
}

int test_vector_init() {
  PRINT_TEST;

  Vector *vector_1 = vector_init(32);
  ASSERT_TEST(vector_1->capacity == 32);
  ASSERT_TEST(vector_1->array != NULL);
  ASSERT_TEST(vector_1->size == 0);

  Vector *vector_2 = vector_init(10);
  ASSERT_TEST(vector_2->capacity == MIN_CAPACITY);
  ASSERT_TEST(vector_2->array != NULL);
  ASSERT_TEST(vector_2->size == 0);

  vector_destroy(vector_1, free_int);
  vector_destroy(vector_2, free_int);

  return errno;
}

int test_vector_init_array() {
  PRINT_TEST;

  int size_1 = 8;
  int **array_vector_1 = malloc(sizeof(int *) * size_1);

  for (int i = 0; i < size_1; i++)
    array_vector_1[i] = copy_int(&i);

  Vector *vector_1 =
      vector_init_array((void **)array_vector_1, size_1, size_1);

  int array_1[size_1];
  for (int i = 0; i < size_1; i++)
    array_1[i] = i;
  ASSERT_TEST(is_vector_equal_to_array(vector_1, array_1, size_1));
  ASSERT_TEST(vector_1->capacity == MIN_CAPACITY);
  ASSERT_TEST(vector_1->array != NULL);
  ASSERT_TEST(vector_1->size == size_1);

  int size_2 = 32;
  int **array_vector_2 = malloc(sizeof(int *) * size_2);

  for (int i = 0; i < size_2; i++)
    array_vector_2[i] = copy_int(&i);

  Vector *vector_2 =
      vector_init_array((void **)array_vector_2, size_2, size_2);

  int array_2[size_2];
  for (int i = 0; i < size_2; i++)
    array_2[i] = i;
  ASSERT_TEST(is_vector_equal_to_array(vector_2, array_2, size_2));
  ASSERT_TEST(vector_2->capacity == size_2);
  ASSERT_TEST(vector_2->array != NULL);
  ASSERT_TEST(vector_2->size == size_2);

  vector_destroy(vector_1, free_int);
  vector_destroy(vector_2, free_int);

  return errno;
}

int test_vector_resize() {
  PRINT_TEST;

  Vector *vector = vector_init_empty();

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

  vector_destroy(vector, free_int);

  return errno;
}

int test_vector_add() {
  PRINT_TEST;

  Vector *vector_1 = vector_init(MIN_CAPACITY);
  for (int i = 0; i < 8; i++)
    vector_add(int*,vector_1, copy_int(&i));

  ASSERT_TEST(vector_1->size == 8);
  ASSERT_TEST(vector_1->capacity == MIN_CAPACITY);

  // This method ensures that the copy function we pass is being used
  // if the function didn't work all numbers would be the last value i was
  // in this case all numbers would be 7, because the reference we pass is the
  // same
  int array_1[8] = {0, 1, 2, 3, 4, 5, 6, 7};
  ASSERT_TEST(is_vector_equal_to_array(vector_1, array_1, 8));

  Vector *vector_2 = vector_init(MIN_CAPACITY);
  for (int i = 0; i < 30; i++)
    vector_add(int*, vector_2, copy_int(&i));

  ASSERT_TEST(vector_2->size == 30);
  ASSERT_TEST(vector_2->capacity == 32);

  int array_2[30];
  for (int i = 0; i < 30; i++)
    array_2[i] = i;
  ASSERT_TEST(is_vector_equal_to_array(vector_2, array_2, 30));

  Vector *vector_3 = vector_init(MIN_CAPACITY);

  int *p1 = malloc(sizeof(int));
  *p1 = 1;
  int *p2 = malloc(sizeof(int));
  *p2 = 2;
  int *p3 = malloc(sizeof(int));
  *p3 = 3;
  int *p4 = malloc(sizeof(int));
  *p4 = 4;
  int *p5 = malloc(sizeof(int));
  *p5 = 5;

  vector_add(int*, vector_3, p1);
  vector_add(int*, vector_3, p2);
  vector_add(int*, vector_3, p3);
  vector_add(int*, vector_3, p4);
  vector_add(int*, vector_3, p5);

  ASSERT_TEST(p1 == vector_3->array[0]);
  ASSERT_TEST(p2 == vector_3->array[1]);
  ASSERT_TEST(p3 == vector_3->array[2]);
  ASSERT_TEST(p4 == vector_3->array[3]);
  ASSERT_TEST(p5 == vector_3->array[4]);

  vector_destroy(vector_1, free_int);
  vector_destroy(vector_2, free_int);
  vector_destroy(vector_3, free_int);

  return errno;
}

int test_vector_add_at()
{
    PRINT_TEST; 

    Vector* vector_1 = vector_init(MIN_CAPACITY); 
    ASSERT_TEST(vector_add_at(vector_1, NULL, 1000, copy_int));

    for(int i = 0; i < 15; i++)
        vector_add_at(vector_1, &i, vector_1->size, copy_int);

    int array_1[15] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    ASSERT_TEST(is_vector_equal_to_array(vector_1, array_1, 15));
    ASSERT_TEST(vector_1->size == 15);
    ASSERT_TEST(vector_1->capacity == MIN_CAPACITY);
    
    Vector* vector_2 = vector_init(MIN_CAPACITY); 

    for(int i = 0; i < 15; i++)
        vector_add_at(vector_2, &i, 0, copy_int);

    int array_2[15] = {14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    ASSERT_TEST(is_vector_equal_to_array(vector_2, array_2, 15));
    ASSERT_TEST(vector_2->size == 15);
    ASSERT_TEST(vector_2->capacity == MIN_CAPACITY);
            
    vector_destroy(vector_1, free_int);
    vector_destroy(vector_2, free_int);

    return errno;
}

int test_vector_set() {
  PRINT_TEST;

  Vector *vector_1 = vector_init(MIN_CAPACITY);
  add_values_to_vector(vector_1, 8);

  int *value = malloc(sizeof(int));
  *value = 69; //( ͡° ͜ʖ ͡°)
  ASSERT_TEST(vector_set(vector_1, value, -6, copy_int, free_int));
  ASSERT_TEST(vector_set(vector_1, value, 65454, copy_int, free_int));
  ASSERT_TEST(!vector_set(vector_1, value, 3, copy_int, free_int));
  ASSERT_TEST(vector_1->array[3]);
  ASSERT_TEST(*(int *)vector_1->array[3] == *value);

  ASSERT_TEST(!vector_set(vector_1, value, 4, NULL, free_int));
  ASSERT_TEST(vector_1->array[4] == value);

  vector_destroy(vector_1, free_int);

  return errno;
}

int test_vector_remove() {
    PRINT_TEST;

    int capacity_1 = MIN_CAPACITY;
    Vector *vector_1 = vector_init(capacity_1);
    ASSERT_TEST(vector_remove(vector_1, 0, free_int));
    add_values_to_vector(vector_1, 8);

    ASSERT_TEST(vector_remove(vector_1, -2, free_int));
    ASSERT_TEST(vector_remove(vector_1, 1000, free_int));
    ASSERT_TEST(!vector_remove(vector_1, 2, free_int));
    ASSERT_TEST(vector_1->array != NULL);
    ASSERT_TEST(vector_1->size == 7);
    ASSERT_TEST(vector_1->capacity == capacity_1);
    ASSERT_TEST(*(int *)vector_1->array[2] != 2);
    int array_1[7] = {0, 1, 3, 4, 5, 6, 7};
    ASSERT_TEST(is_vector_equal_to_array(vector_1, array_1, 7));

    int capacity_2 = 32;
    Vector *vector_2 = vector_init(capacity_2);
    add_values_to_vector(vector_2, 32 - 1);
    for (int i = 0; i < capacity_2 * 0.75 - 1; i++)
    ASSERT_TEST(!vector_remove(vector_2, 0, free_int));

    ASSERT_TEST(vector_2->array != NULL);
    ASSERT_TEST(vector_2->capacity == capacity_2 >> 1);
    ASSERT_TEST(vector_2->size == 31 - (capacity_2 * 0.75 - 1));
    int array_2[8] = {23, 24, 25, 26, 27, 28, 29, 30};
    ASSERT_TEST(is_vector_equal_to_array(vector_2, array_2, 7));

    int capacity_3 = MIN_CAPACITY;
    Vector *vector_3 = vector_init(capacity_3);

    int value;
    value = 2;
    vector_add(int*, vector_3, copy_int(&value));
    value = 10;
    vector_add(int*, vector_3, copy_int(&value));
    value = 34;
    vector_add(int*, vector_3, copy_int(&value));
    value = 12;
    vector_add(int*, vector_3, copy_int(&value));
    value = 3;
    vector_add(int*, vector_3, copy_int(&value));
    value = -4; 
    vector_add(int*, vector_3, copy_int(&value));
    value = -67;
    vector_add(int*, vector_3, copy_int(&value));
    value = 4363;
    vector_add(int*, vector_3, copy_int(&value));

    ASSERT_TEST(!vector_remove(vector_3, 2, free_int)); //{2, 10, 12, 3, -4, -67, 4363}
    ASSERT_TEST(!vector_remove(vector_3, 5, free_int)); //{2, 10, 12, 3, -4, 4363}
    ASSERT_TEST(!vector_remove(vector_3, 1, free_int)); //{2, 12, 3, -4, 4363}
    ASSERT_TEST(vector_remove(vector_3, 5, free_int));  // Error
    ASSERT_TEST(!vector_remove(vector_3, 0, free_int)); //{12, 3, -4, 4363}
    ASSERT_TEST(!vector_remove(vector_3, 3, free_int)); //{12, 3, -4}
    ASSERT_TEST(!vector_remove(vector_3, 0, free_int)); //{3, -4}

    int array_3[2] = {3, -4};
    ASSERT_TEST(is_vector_equal_to_array(vector_3, array_3, 2));

    vector_destroy(vector_1, free_int);
    vector_destroy(vector_2, free_int);
    vector_destroy(vector_3, free_int);

    return errno;
}

int test_vector_remove_from_to() {
  PRINT_TEST;

  Vector *vector_1 = vector_init(MIN_CAPACITY);
  add_values_to_vector(vector_1, 10);

  ASSERT_TEST(vector_remove_from_to(vector_1, -1, 7, free_int));
  ASSERT_TEST(vector_remove_from_to(vector_1, 2, 99, free_int));

  int array_1[4] = {0, 1, 8, 9};
  ASSERT_TEST(!vector_remove_from_to(vector_1, 2, 7, free_int));
  ASSERT_TEST(is_vector_equal_to_array(vector_1, array_1, 4));
  ASSERT_TEST(vector_1->size == 4);
  ASSERT_TEST(vector_1->capacity == 16);
  ASSERT_TEST(is_vector_equal_to_array(vector_1, array_1, 4));

  Vector *vector_2 = vector_init(MIN_CAPACITY);
  add_values_to_vector(vector_2, 32);

  int array_2[4] = {0, 1, 30, 31};
  ASSERT_TEST(!vector_remove_from_to(vector_2, 2, 29, free_int));
  ASSERT_TEST(is_vector_equal_to_array(vector_2, array_2, 4));
  ASSERT_TEST(vector_2->size == 4);
  ASSERT_TEST(vector_2->capacity == 16);

  Vector *vector_3 = vector_init(256);
  add_values_to_vector(vector_3, 251);

  int array_3[5] = {0, 1, 248, 249, 250};
  ASSERT_TEST(!vector_remove_from_to(vector_3, 2, 247, free_int));
  ASSERT_TEST(is_vector_equal_to_array(vector_3, array_3, 5));
  ASSERT_TEST(vector_3->size == 5);
  ASSERT_TEST(vector_3->capacity == 20);

  Vector *vector_4 = vector_init(256);
  add_values_to_vector(vector_4, 256);

  int array_4[0] = {};
  ASSERT_TEST(!vector_remove_from_to(vector_4, 0, 255, free_int));
  ASSERT_TEST(is_vector_equal_to_array(vector_4, array_4, 0));
  ASSERT_TEST(vector_4->size == 0);
  ASSERT_TEST(vector_4->capacity == 16);

  Vector *vector_5 = vector_init(256);
  add_values_to_vector(vector_5, 256);

  int array_5[4] = {252, 253, 254, 255};
  ASSERT_TEST(!vector_remove_from_to(vector_5, 0, 251, free_int));
  ASSERT_TEST(is_vector_equal_to_array(vector_5, array_5, 4));
  ASSERT_TEST(vector_5->size == 4);
  ASSERT_TEST(vector_5->capacity == 16);

  Vector *vector_6 = vector_init(256);
  add_values_to_vector(vector_6, 256);

  int array_6[4] = {0, 1, 2, 3};
  ASSERT_TEST(!vector_remove_from_to(vector_6, 4, 255, free_int));
  ASSERT_TEST(is_vector_equal_to_array(vector_6, array_6, 4));
  ASSERT_TEST(vector_6->size == 4);
  ASSERT_TEST(vector_6->capacity == 16);

  vector_destroy(vector_1, free_int);
  vector_destroy(vector_2, free_int);
  vector_destroy(vector_3, free_int);
  vector_destroy(vector_4, free_int);
  vector_destroy(vector_5, free_int);
  vector_destroy(vector_6, free_int);

  return errno;
}

int test_vector_get() 
{
    PRINT_TEST;

    Vector* vector_1 = vector_init(MIN_CAPACITY);
    add_values_to_vector(vector_1, 15);

    ASSERT_TEST(!vector_get(int*, vector_1, 100)); 
    ASSERT_TEST(!vector_get(int*, vector_1, 83475837)); 
//    ASSERT_TEST(!vector_get(int*, NULL, 5));
//    ASSERT_TEST(!vector_get(int*, NULL, 102322));
//    ASSERT_TEST(!vector_get(int*, NULL, 1, NULL));

    
    int* value_1 = vector_get(int*, vector_1, 0);
    ASSERT_TEST(*value_1 == 0);
    int* value_2 = vector_get(int*, vector_1, 1);
    ASSERT_TEST(*value_2 == 1);
    int* value_3 = vector_get(int*, vector_1, 2);
    ASSERT_TEST(*value_3 == 2);
    int* value_4 = vector_get(int*, vector_1, 3);
    ASSERT_TEST(*value_4 == 3);
    int* value_5 = vector_get(int*, vector_1, 14);
    ASSERT_TEST(*value_5 == 14);

    free(value_1);
    free(value_2);
    free(value_3);
    free(value_4);
    free(value_5);

    Vector* vector_2 = vector_init(MIN_CAPACITY);

    int *p1 = malloc(sizeof(int));
    *p1 = 1;
    int *p2 = malloc(sizeof(int));
    *p2 = 2;
    int *p3 = malloc(sizeof(int));
    *p3 = 3;
    int *p4 = malloc(sizeof(int));
    *p4 = 4;
    int *p5 = malloc(sizeof(int));
    *p5 = 5;

    vector_add(int*, vector_2, p1);
    vector_add(int*, vector_2, p2);
    vector_add(int*, vector_2, p3);
    vector_add(int*, vector_2, p4);
    vector_add(int*, vector_2, p5);

    ASSERT_TEST(vector_get(int*, vector_2, 0) == p1);
    ASSERT_TEST(vector_get(int*, vector_2, 1) == p2);
    ASSERT_TEST(vector_get(int*, vector_2, 2) == p3);
    ASSERT_TEST(vector_get(int*, vector_2, 3) == p4);
    ASSERT_TEST(vector_get(int*, vector_2, 4) == p5);

    vector_destroy(vector_1, free_int); 
    vector_destroy(vector_2, free_int); 
  

  return errno;
}


int test_vector_get_remove() 
{
    PRINT_TEST;

    Vector* vector_1 = vector_init(MIN_CAPACITY);
    add_values_to_vector(vector_1, 15);

    ASSERT_TEST(!vector_get_remove(vector_1, 100, NULL, free_int)); 
    ASSERT_TEST(!vector_get_remove(vector_1, 83475837, NULL, free_int)); 
    ASSERT_TEST(!vector_get_remove(NULL, 5, copy_int, free_int));
    ASSERT_TEST(!vector_get_remove(NULL, 102322, copy_int, free_int));
    ASSERT_TEST(!vector_get_remove(NULL, 1, NULL, free_int));

    int* value_0 = (int*) vector_get_remove(vector_1, 0, copy_int, free_int);
    ASSERT_TEST(*value_0 == 0);
    int* value_1 = (int*) vector_get_remove(vector_1, 0, copy_int, free_int);
    ASSERT_TEST(*value_1 == 1);
    int* value_2 = (int*) vector_get_remove(vector_1, 0, copy_int, free_int);
    ASSERT_TEST(*value_2 == 2);
    int* value_3 = (int*) vector_get_remove(vector_1, 0, copy_int, free_int);
    ASSERT_TEST(*value_3 == 3);
    int* value_14 = (int*) vector_get_remove(vector_1, 10, copy_int, free_int);
    ASSERT_TEST(*value_14 == 14);

    free(value_0);
    free(value_1);
    free(value_2);
    free(value_3);
    free(value_14);

    Vector* vector_2 = vector_init(MIN_CAPACITY);

    int *p1 = malloc(sizeof(int));
    *p1 = 1;
    int *p2 = malloc(sizeof(int));
    *p2 = 2;
    int *p3 = malloc(sizeof(int));
    *p3 = 3;
    int *p4 = malloc(sizeof(int));
    *p4 = 4;
    int *p5 = malloc(sizeof(int));
    *p5 = 5;

    vector_add(int*, vector_2, p1);
    vector_add(int*, vector_2, p2);
    vector_add(int*, vector_2, p3);
    vector_add(int*, vector_2, p4);
    vector_add(int*, vector_2, p5);

    ASSERT_TEST(vector_get_remove(vector_2, 0, NULL, free_int) == p1);
    ASSERT_TEST(vector_get_remove(vector_2, 1, NULL, free_int) == p2);
    ASSERT_TEST(vector_get_remove(vector_2, 2, NULL, free_int) == p3);
    ASSERT_TEST(vector_get_remove(vector_2, 3, NULL, free_int) == p4);
    ASSERT_TEST(vector_get_remove(vector_2, 4, NULL, free_int) == p5);

    vector_destroy(vector_1, free_int); 
    vector_destroy(vector_2, free_int); 

    free(p1);
    free(p2);
    free(p3);
    free(p4);
    free(p5);

    return errno;
}

int test_vector_set_size()
{
    PRINT_TEST; 

    Vector* vector_1 = vector_init(MIN_CAPACITY);
    add_values_to_vector(vector_1, 15);

    ASSERT_TEST(vector_set_size(NULL, 10, free_int)); 
    ASSERT_TEST(!vector_set_size(vector_1, 30, free_int));
    ASSERT_TEST(vector_1->size == 30);
    ASSERT_TEST(vector_1->capacity == 32);
    ASSERT_TEST(*(int*) vector_get(int*, vector_1, 6) == 6);
    ASSERT_TEST(*(int*) vector_get(int*, vector_1, 9) == 9);
    ASSERT_TEST(*(int*) vector_get(int*, vector_1, 14) == 14);
    
    ASSERT_TEST(!vector_set_size(vector_1, 4, free_int));
    ASSERT_TEST(vector_1->size == 4);
    ASSERT_TEST(vector_1->capacity == MIN_CAPACITY);
    ASSERT_TEST(*(int*) vector_get(int*, vector_1, 0) == 0);
    ASSERT_TEST(*(int*) vector_get(int*, vector_1, 1) == 1);
    ASSERT_TEST(*(int*) vector_get(int*, vector_1, 2) == 2);
    ASSERT_TEST(*(int*) vector_get(int*, vector_1, 3) == 3);

    vector_destroy(vector_1, free_int);

    return errno;
}

int test_vector_set_capacity()
{
    PRINT_TEST; 

    Vector* vector_1 = vector_init(MIN_CAPACITY);
    add_values_to_vector(vector_1, 15);

    ASSERT_TEST(vector_set_capacity(NULL, 10, free_int)); 
    ASSERT_TEST(vector_set_capacity(vector_1, MAX_CAPACITY + 1, free_int));
    ASSERT_TEST(vector_set_capacity(vector_1, 5, free_int));
    ASSERT_TEST(!vector_set_capacity(vector_1, 30, free_int));
    ASSERT_TEST(vector_1->size == 15);
    ASSERT_TEST(vector_1->capacity == 30);
    ASSERT_TEST(*(int*) vector_get(int*, vector_1, 6) == 6);
    ASSERT_TEST(*(int*) vector_get(int*, vector_1, 9) == 9);
    ASSERT_TEST(*(int*) vector_get(int*, vector_1, 14) == 14);
    
    ASSERT_TEST(!vector_set_capacity(vector_1, MIN_CAPACITY, free_int));
    ASSERT_TEST(vector_1->size == 15);
    ASSERT_TEST(vector_1->capacity == MIN_CAPACITY);
    ASSERT_TEST(*(int*) vector_get(int*, vector_1, 0) == 0);
    ASSERT_TEST(*(int*) vector_get(int*, vector_1, 1) == 1);
    ASSERT_TEST(*(int*) vector_get(int*, vector_1, 2) == 2);
    ASSERT_TEST(*(int*) vector_get(int*, vector_1, 3) == 3);

    vector_destroy(vector_1, free_int);

    return errno;
}

int test_vector(int show_print) 
{
    printf(GREEN_ON BOLD_ON "Testing Vector.\n" BOLD_OFF COLOR_OFF);
    SHOW_PRINT = show_print;

    ASSERT_TEST(!test_vector_destroy());
    ASSERT_TEST(!test_vector_init_empty());
    ASSERT_TEST(!test_vector_init());
    ASSERT_TEST(!test_vector_init_array());
    ASSERT_TEST(!test_vector_resize());
    ASSERT_TEST(!test_vector_add());
    ASSERT_TEST(!test_vector_add_at());
    ASSERT_TEST(!test_vector_set());
    ASSERT_TEST(!test_vector_remove());
    ASSERT_TEST(!test_vector_remove_from_to());
    ASSERT_TEST(!test_vector_get());
    ASSERT_TEST(!test_vector_get_remove());
    ASSERT_TEST(!test_vector_set_size());
    ASSERT_TEST(!test_vector_set_capacity());
    /*
    Vector *vector = vector_init(MAX_CAPACITY);
    for(int i = 0; i < 100; i++)
    vector_add(int*, vector, &i, copy_int);
    sleep(10);

    vector_destroy(vector);
    free(vector_get_header(x));
    */


    return 0;
}
