#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "algorithms.h"
#include "data.h"

int main(int argc, char** argv)
{
  int avg_tests = 100;
  int num_sizes;
  int* test_sizes = get_test_sizes(&num_sizes);

  int i, j, n, discard;
  int* A;
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
      brute_avg += brute_force_median(A, n);
      med_avg += median(A, n);
      free(A);
    }

    brute_avg /= avg_tests;
    med_avg /= avg_tests;
    brute_data[i] = brute_avg;
    med_data[i] = med_avg;
    printf("%i:\t%.3f\t%.3f\n", n, brute_avg, med_avg);
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

