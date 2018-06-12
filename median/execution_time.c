#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "algorithms.h"
#include "data.h"

double time_diff(struct timespec* t1, struct timespec* t2)
{
  return (double) ((t2->tv_sec - t1->tv_sec) + (t2->tv_nsec - t1->tv_nsec) / 1000000000.0L);
}

void test_array(int* A, int n, int reps, double* brute_avg, double* med_avg)
{
  static struct timespec t1;
  static struct timespec t2;
  int i;

  clock_gettime(CLOCK_MONOTONIC, &t1);

  for (i = 0; i < reps; ++i)
  {
    brute_force_median(A, n);
  }

  clock_gettime(CLOCK_MONOTONIC, &t2);
  *brute_avg += time_diff(&t1, &t2);
  clock_gettime(CLOCK_MONOTONIC, &t1);

  for (i = 0; i < reps; ++i)
  {
    median(A, n);
  }

  clock_gettime(CLOCK_MONOTONIC, &t2);
  *med_avg += time_diff(&t1, &t2);
}

int main(int argc, char** argv)
{
  int avg_tests = 100;
  int repetitions = 100;
  int num_sizes;
  int* test_sizes = get_test_sizes(&num_sizes);

  int* A;
  int i, j, n, discard;
  double brute_avg, med_avg;
  double* brute_data = malloc(sizeof(double) * num_sizes);
  double* med_data = malloc(sizeof(double) * num_sizes);

  printf("Performing %i tests with sizes:\n", num_sizes);
  print_int_array(test_sizes, num_sizes);
  printf("\nn:\tbrute average\tmedian average\n");

  srand(time(NULL));

  for (i = 0; i < num_sizes; ++i)
  {
    brute_avg = 0;
    med_avg = 0;
    n = test_sizes[i];

    for (j = 0; j < avg_tests; ++j)
    {
      A = rand_array(n);
      test_array(A, n, repetitions, &brute_avg, &med_avg);
      free(A);
    }

    brute_avg /= avg_tests;
    med_avg /= avg_tests;
    brute_data[i] = brute_avg;
    med_data[i] = med_avg;
    printf("%i:\t%.6f\t%.6f\n", n, brute_avg, med_avg);
  }

  printf("\n\nARRAY FORM\n\n");

  printf("Brute averages\n");
  print_double_array(brute_data, num_sizes);
  printf("\n");
  printf("Median averages\n");
  print_double_array(med_data, num_sizes);

  free(brute_data);
  free(med_data);
  free(test_sizes);
}
