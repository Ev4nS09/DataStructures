#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "vector.h"

#define TRIALS 31
#define VECTOR_SIZE 100000000

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

int main()
{
  printf("%lf\n", sizeof(int*));

  for(int trial = 0; trial < TRIALS; trial++)
  {
    Vector* vector = vector_init(1, free_int);
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
