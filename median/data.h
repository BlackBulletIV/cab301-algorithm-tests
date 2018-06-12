#ifndef _DATA_H
#define _DATA_H

#include <stdlib.h>

#define MAX_VAL (RAND_MAX / 10)

int rand_range(int min, int max);
int shuffle(int* A, int n);
int* rand_array(int n);
int* odd_array(int n, int num_med, int* median);
int* even_array(int n, int* left_median, int* right_median);
int* sequential_array(int n, int* median);
int* get_test_sizes(int* length);
void print_int_array(int* A, int n);
void print_double_array(double* A, int n);

#endif
