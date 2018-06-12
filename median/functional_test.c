#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "algorithms.h"
#include "data.h"

void report_errors(int* brute_total, int* med_total, int* brute_errors, int* med_errors)
{
  printf("Brute set error: %i, Median set error: %i\n", *brute_errors, *med_errors);
  fflush(stdout);
  *brute_total += *brute_errors;
  *med_total += *med_errors;
  *brute_errors = 0;
  *med_errors = 0;
}

int main(int argc, char** argv)
{
  int* A;
  int i, j, n, result, med, rmed;
  int brute_errors = 0;
  int med_errors = 0;
  int brute_total = 0;
  int med_total = 0;
  int max_power = 14;
  int reps = 5;

  srand(time(NULL));

  for (i = 0; i <= max_power; ++i)
  {
    n = pow(2, i);
    if (i > 0) n++;

    printf("Ordered set of size %i\n", n);
    fflush(stdout);

    A = sequential_array(n, &med);

    // print results for set 2^4 as an example
    if (i <= 5) print_int_array(A, n);

    result = brute_force_median(A, n);
    if (result != med) brute_errors++;
    if (i <= 5) printf("Brute result: %i (expected %i)\n", result, med);

    result = median(A, n);
    if (result != med) med_errors++;
    if (i <= 5) printf("Median result: %i (expected %i)\n", result, med);

    if (i <= 5) fflush(stdout);
    free(A);

    report_errors(&brute_total, &med_total, &brute_errors, &med_errors);
    printf("Random sets of size %i (odd)\n", n);
    fflush(stdout);

    for (j = 0; j < reps; ++j)
    {
      A = odd_array(n, 1, &med);
      result = brute_force_median(A, n);
      if (result != med) brute_errors++;
      result = median(A, n);
      if (result != med) med_errors++;
      free(A);
    }

    report_errors(&brute_total, &med_total, &brute_errors, &med_errors);
    printf("Random sets of size %i (odd) with 3 medians\n", n);
    fflush(stdout);

    for (j = 0; j < reps; ++j)
    {
      A = odd_array(n, 3, &med);
      result = brute_force_median(A, n);
      if (result != med) brute_errors++;
      result = median(A, n);
      if (result != med) med_errors++;
      free(A);
    }

    report_errors(&brute_total, &med_total, &brute_errors, &med_errors);

    if (i > 0)
    {
      n--; // make even
      printf("Ordered set of size %i (even)\n", n);
      fflush(stdout);

      A = sequential_array(n, &med);
      rmed = med + 1;
      if (i <= 5) print_int_array(A, n);

      result = brute_force_median(A, n);
      if (result != med) brute_errors++;
      if (i <= 5) printf("Brute result: %i (expected %i)\n", result, med);

      result = median(A, n);
      if (result != rmed) med_errors++;
      if (i <= 5) printf("Median result: %i (expected %i)\n", result, rmed);

      if (i <= 5) fflush(stdout);
      free(A);

      report_errors(&brute_total, &med_total, &brute_errors, &med_errors);
      printf("Random sets of size %i (even)\n", n);
      fflush(stdout);
  
      for (j = 0; j < reps; ++j)
      {
        // difference in median result (left or right) due 
        A = even_array(n, &med, &rmed);
        result = brute_force_median(A, n);
        if (result != med) brute_errors++;
        result = median(A, n);
        if (result != rmed) med_errors++;
        free(A);
      }      

      report_errors(&brute_total, &med_total, &brute_errors, &med_errors);
    }

    printf("\n");
  }

  printf("Total brute force median errors: %i\n", brute_total);
  printf("Total median errors: %i\n", med_total);
}
