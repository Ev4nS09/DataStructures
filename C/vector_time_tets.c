#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "vector.h"
#include "linkedlist.h"

#define TRIALS 31
#define VECTOR_SIZE 67108864 

double start_timer = 0;
double stop_timer = 0;
double final_time = 0;

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
  List* list = list_init(free_int); 
  int t = 7;
  int v = 5;

  for(int i = 0; i < 10; i++)
    if(i != 7)
      list_add_last(list, &i, copy_int);

  list_add_cmp(list, &t, cmp_less, copy_int);
  //list_add_at(list, &v, 5, copy_int);
  //list_add_at(list, &t, 11, copy_int);
  printf("%d\n", list_contains_value(list, &t, cmp_int));
  //list_insertion_sort(list, cmp_less); 
  list_print(list, print_int);
  list_free(list);
  exit(0);

  for(int trial = 0; trial < TRIALS; trial++)
  {
    Vector* vector = vector_init(20, free_int);
    start_timer = (double) clock();     
    for(int i = 0; i < VECTOR_SIZE; i++)
      vector_add(vector, &i, copy_int);
    stop_timer = (double) clock();
    final_time += stop_timer / CLOCKS_PER_SEC - start_timer / CLOCKS_PER_SEC; 
    free_vector(vector);
  }

  final_time = final_time / TRIALS; 

  printf("Time for %d vector additions: %.6lf\n", VECTOR_SIZE, final_time);

  return 0;
}
