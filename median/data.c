#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "data.h"

int rand_range(int min, int max)
{
  return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

// Fisher-Yates shuffle in place
int shuffle(int* A, int n)
{
  int i, j, tmp;

  for (i = 0; i < n; ++i)
  {
    j = rand_range(i, n - 1);
    tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
  }
}

int* rand_array(int n)
{
  int i;
  int* A = malloc(sizeof(int) * n);

  for (i = 0; i < n; ++i)
  {
    A[i] = rand_range(0, MAX_VAL);
  }

  return A;
}

int* odd_array(int n, int num_med, int* median)
{
  int i;
  int mid = ceil(n / 2.0) - 1;
  int med = rand_range(mid + 1, MAX_VAL - mid - 1);
  int switch_point = num_med + (n - num_med) / 2;
  int* A = malloc(sizeof(int) * n);

  for (i = 0; i < n; ++i)
  {
    if (i < num_med)
    {
      A[i] = med;
    }
    else if (i < switch_point)
    {
      A[i] = rand_range(0, med - 1);
    }
    else
    {
      A[i] = rand_range(med + 1, MAX_VAL);
    }
  }

  shuffle(A, n);
  *median = med;
  return A;
}

int* even_array(int n, int* left_median, int* right_median)
{
  int i;
  int rmid = ceil((n - 1) / 2.0);
  int lmid = floor((n - 1) / 2.0);
  int rmed = rand_range(rmid + 1, MAX_VAL - rmid - 2);
  int lmed = rmed - 1;
  int* A = malloc(sizeof(int) * n);

  if (n % 2 > 0)
  {
    printf("WARNING: attempted to make split median array of odd length... exiting\n");
    exit(1);
  }

  for (i = 0; i < n; ++i)
  {
    if (i < lmid)
    {
      A[i] = rand_range(0, lmed - 1);
    }
    else if (i > rmid)
    {
      A[i] = rand_range(rmed + 1, MAX_VAL);
    }
    else
    {
      A[i] = i == lmid ? lmed : rmed;
    }
  }

  shuffle(A, n);
  *left_median = lmed;
  *right_median = rmed;
  return A;
}

int* sequential_array(int n, int* median)
{
  int i;
  int* A = malloc(sizeof(int) * n);
  *median = ceil(n / 2.0) - 1;
  for (i = 0; i < n; ++i) A[i] = i;
  return A;
}

int* get_test_sizes(int* length)
{
  int i;
  int* A;
  *length = 36;
  A = malloc(sizeof(int) * (*length));
  A[0] = 0;

  for (i = 0; i < *length; ++i)
  {
    A[i] = i == 0 ? 1 : (A[i - 1] + (i < 6 ? 10 : 50) + i);
  }

  return A;
}

void print_int_array(int* A, int n)
{
  int i;
  printf("[");

  for (i = 0; i < n; ++i)
  {
    printf(i == n - 1 ? "%i" : "%i,", A[i]);
  }

  printf("]\n");
}

void print_double_array(double* A, int n)
{
  int i;
  printf("[");

  for (i = 0; i < n; ++i)
  {
    printf(i == n - 1 ? "%.6f" : "%.6f,", A[i]);
  }

  printf("]\n");
}

