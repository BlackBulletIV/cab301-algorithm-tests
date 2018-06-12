#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int get_rand_val(int* array, int len)
{
  int index = floor(((float) rand()) / RAND_MAX * (len - 1) + 0.5);
  return array[index];
}

// find the odd number below a random index
int get_rand_odd(int len)
{
  int index = floor(((float) rand()) / RAND_MAX * (len - 1) + 0.5);
  return index * 2 - 1;
}

int set_base_power(int* base)
{
  if (*base == 10)
  {
    return 9; // 10^10 is greater than 2^30
  }
  else if (*base == 3)
  {
    return 18; // 3^19 is greater than 2^30
  }
  else
  {
    *base = 2; // ensure base is set to 2
    return 30;
  }
}

int binary_search(int* A, int n, int K)
{
  int l = 0;
  int r = n - 1;
  int m;

  while (l <= r)
  {
    m = (l + r) / 2;

    if (A[m] == K)
    {
      return m;
    }
    else if (K < A[m])
    {
      r = m - 1;
    }
    else
    {
      l = m + 1;
    }
  }

  return -1;
}

int binary_search_basic_ops(int* A, int n, int K)
{
  int l = 0;
  int r = n - 1;
  int m;
  int ops = 0;

  while (l <= r)
  {
    m = (l + r) / 2;
    ops++;

    if (A[m] == K) // basic operation
    {
      return ops;
    }
    else if (K < A[m])
    {
      r = m - 1;
    }
    else
    {
      l = m + 1;
    }
  }

  return ops;
}

void test_algorithm(int* A, int n)
{
  int i, index, val;
  int errors;
  printf("Test on %i element array\n", n);
  printf("First three tests:\n");

  for (i = 0; i < 3; ++i)
  {
    val = get_rand_val(A, n);
    index = binary_search(A, n, val);
    printf("Test value %i: %i\n", i + 1, val);
    printf("Returned index: %i\n", index);
    printf("Indexed value: %i\n", A[index]);
    if (val != A[index]) errors++;
  }

  for (i = 0; i < 997; ++i)
  {
    val = get_rand_val(A, n);
    index = binary_search(A, n, val);
    if (val != A[index]) errors++;
  }

  printf("1000 tests completed with %i errors\n", errors);

  index = binary_search(A, n, -5);
  printf("Test non-value: -5\n");
  printf("Returned index: %i\n", index);
  fflush(stdout);
}

void test_basic_operations(int* A, int base)
{
  static int avg_tests = 1000;
  static int pow_start = 0;
  int pow_end = set_base_power(&base);

  int i, j, val, non_val, index, n;
  double avg_ops;
  double na_avg_ops;

  for (i = pow_start; i <= pow_end; ++i)
  {
    n = pow(base, i);
    avg_ops = 0;
    na_avg_ops = 0;

    for (j = 0; j < avg_tests; ++j)
    {
      val = get_rand_val(A, n);
      non_val = get_rand_odd(n);
      avg_ops += binary_search_basic_ops(A, n, val);
      na_avg_ops += binary_search_basic_ops(A, n, non_val);
    }
    
    avg_ops /= avg_tests;
    na_avg_ops /= avg_tests;

    printf("%i^%i items: %.3f, no result: %.3f\n", base, i, avg_ops, na_avg_ops);
    fflush(stdout);
  }
}

void test_execution_time(int* A, int base)
{
  static int avg_tests = 100;
  static int repetitions = 1000000;
  static int pow_start = 0;
  int pow_end = set_base_power(&base);

  int i, j, k, val, non_val, index, n;
  struct timespec t1;
  struct timespec t2;
  double avg_time;
  double na_avg_time;

  for (i = pow_start; i <= pow_end; ++i)
  {
    n = pow(base, i);
    avg_time = 0;
    na_avg_time = 0;

    for (j = 0; j < avg_tests; ++j)
    {
      val = get_rand_val(A, n);
      non_val = get_rand_odd(n);
      clock_gettime(CLOCK_MONOTONIC, &t1);

      for (k = 0; k < repetitions; ++k)
      {
        binary_search(A, n, val);
      }

      clock_gettime(CLOCK_MONOTONIC, &t2);
      avg_time += (double) ((t2.tv_sec - t1.tv_sec) + (t2.tv_nsec - t1.tv_nsec) / 1000000000.0L);
      clock_gettime(CLOCK_MONOTONIC, &t1);

      for (k = 0; k < repetitions; ++k)
      {
        binary_search(A, n, non_val);
      }

      clock_gettime(CLOCK_MONOTONIC, &t2);
      na_avg_time += (double) ((t2.tv_sec - t1.tv_sec) + (t2.tv_nsec - t1.tv_nsec) / 1000000000.0L);
    }
    
    avg_time /= avg_tests;
    na_avg_time /= avg_tests;
    printf("%i^%i items: %.6f, no result: %.6f\n", base, i, avg_time, na_avg_time);
    fflush(stdout);
  }
}

int main(int argc, char** argv)
{
  // create 2^30 array of even numbers
  // this leaves evenly spaced gaps to test for values not present in the array
  int len = pow(2, 30);
  int* A = malloc(sizeof(int) * len);
  int i;

  for (i = 0; i < len; ++i)
  {
    A[i] = i * 2;
  }

  srand((unsigned) time(NULL));

  printf("==== Algorithm Test ====\n");
  test_algorithm(A, pow(2, 10)); // limit to 2^10
  printf("\n");

  printf("==== Basic Operations ====\n");
  test_basic_operations(A, 2);
  test_basic_operations(A, 3);
  test_basic_operations(A, 10);
  printf("\n");

  printf("==== Execution Time ====\n");
  test_execution_time(A, 2);
  test_execution_time(A, 3);
  test_execution_time(A, 10);

  free(A);
  return 0;
}
