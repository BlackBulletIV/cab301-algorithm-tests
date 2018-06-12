#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int brute_force_median(int* A, int n)
{
  int i, j, num_smaller, num_equal;
  int k = ceil(n / 2.0);

  for (i = 0; i < n; ++i)
  {
    num_smaller = 0;
    num_equal = 0;

    for (j = 0; j < n; ++j)
    {
      if (A[j] < A[i])
      {
        num_smaller++;
      }
      else if (A[j] == A[i])
      {
        num_equal++;
      }
    }

    if (num_smaller < k && k <= (num_smaller + num_equal))
    {
      return A[i];
    }
  }
}

int partition(int* A, int n, int l, int h)
{
  int j, tmp;
  int pivot_val = A[l];
  int pivot_loc = l;

  for (j = l + 1; j <= h; ++j)
  {
    if (A[j] < pivot_val)
    {
      pivot_loc++;
      tmp = A[pivot_loc];
      A[pivot_loc] = A[j];
      A[j] = tmp;
    }
  }

  tmp = A[pivot_loc];
  A[pivot_loc] = A[l];
  A[l] = tmp;
  return pivot_loc;
}

int med_select(int* A, int n, int l, int m, int h) 
{
  int pos = partition(A, n, l, h);
  if (pos == m) return A[pos];
  if (pos > m) return med_select(A, n, l, m, pos - 1);
  if (pos < m) return med_select(A, n, pos + 1, m, h);
}

int median(int* A, int n)
{
  int result;
  int* copy;

  if (n == 1)
  {
    return A[0];
  }
  else
  {
    copy = malloc(sizeof(int) * n);
    memcpy(copy, A, sizeof(int) * n);
    result = med_select(copy, n, 0, floor(n / 2.0), n - 1);
    free(copy);
    return result;
  }
}
