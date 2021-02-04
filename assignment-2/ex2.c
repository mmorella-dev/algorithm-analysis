// FILE: ex2.c
// AUTHOR: Mae Morella
// ===================

// This file contains implementations for the functions defined in ex2.h.

#include "ex2.h"

#include <stdbool.h>  // for bool type
#include <stddef.h>   // for size_t definition
#include <stdio.h>    // for printf(const char *format, ...)
#include <stdlib.h>   // for malloc(size_t size)

// FUNCTION IMPLEMENTATIONS
// ========================

int my_max(const int a[], size_t n) {
  int max = a[0];
  for (int i = 1; i < n; i++)
    if (a[i] > max) max = a[i];
  return max;
}
double my_avg(const int a[], size_t n) {
  double sum = 0.0;
  for (int i = 0; i < n; i++) {
    sum += a[i];  // <- implicit cast from int to double
  }
  return sum / n;
}
int* my_copy(const int a[], size_t n) {
  int* copy = (int*)malloc(n * sizeof(int));
  for (int i = 0; i < n; i++) {
    copy[i] = a[i];
  }
  return copy;
}
void print_numbers(const int a[], size_t n) {
  for (int i = 0; i < n; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
}
void my_reverse(int a[], size_t n) {
  for (int i = 0; i < n / 2; i++) {
    int j = (n - 1) - i;  // reverse iterator
    int t = a[i];         // temp storage for swap
    a[i] = a[j];
    a[j] = t;
  }
}
bool is_prime(long m) {
  if (m < 2) {
    return false;
  }
  for (long i = 2; i * i <= m; i++) {
    if (m % i == 0) {
      return false;
    }
  }
  return true;
}
void print_prime_numbers(const int a[], size_t n) {
  for (int i = 0; i < n; i++) {
    if (is_prime(a[i])) {
      printf("%d ", a[i]);
    }
  }
  printf("\n");
}
