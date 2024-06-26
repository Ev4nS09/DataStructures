#include <iostream>
#include <vector>
#include <chrono>
#include <stdio.h>
#include <time.h>

#define TRIALS 31
#define VECTOR_SIZE 67108864

double start =0;
double stop = 0;

int main()
{
  
  for(int i = 0; i < TRIALS; i++)
  {
    std::vector<double> vector;
    start = ((double)clock()) / CLOCKS_PER_SEC;
    for(double j = 0; j < VECTOR_SIZE; j++)
    {
      vector.push_back(j);
    }
    stop += (((double)clock()) / CLOCKS_PER_SEC - start);
  } 
  stop /= TRIALS;
  printf("%.6lf", stop);
}
