// FILE: ex2.c
// AUTHOR: Mae Morella
// ===================

// This file contains implementations for the functions defined in

#include "ex2.h"

#include <stdbool.h>  // for bool type
#include <stddef.h>   // for size_t definition
#include <stdio.h>    // for printf(const char *format, ...)
#include <stdlib.h>   // for malloc(size_t size)

// MAIN FUNCTION
// =============

int main() {
  int numbers[] = {10, 5, 15, 12};
  const size_t size = sizeof(numbers) / sizeof(numbers[0]);

  // Calculate print maximum value
  int highest = my_max(numbers, size);
  printf("The highest number: %d\n", highest);

  // Calculate and print average
  double avg = my_avg(numbers, size);
  printf("The average of the numbers: %g\n", avg);

  // Make a copy of the array
  int* out_numbers = my_copy(numbers, size);
  // Print the copied array
  printf("The original array: ");
  print_numbers(out_numbers, size);

  // Reverse the array in place, and print it
  my_reverse(out_numbers, size);
  printf("The reverse array: ");
  print_numbers(out_numbers, size);

  // Print the prime numbers in the array.
  printf("The prime numbers in the array: ");
  print_prime_numbers(out_numbers, size);

  printf("\n");
  return 0;
}

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
    int j = (n - 1) - i; // reverse iterator
    int t = a[i];        // temp storage for swap
    a[i] = a[j];
    a[j] = t;
  }
}
bool isPrime(long num) {
  if (num < 2) return false;
  if (num % 2 == 0) return false;
  for (long i = 3; i * i <= num; i++) {
    if (num % i == 0) return false;
  }
  return true;
}
void print_prime_numbers(const int a[], size_t n) {
  for (int i = 0; i < n; i++) {
    if (isPrime(a[i])) printf("%d ", a[i]);
  }
  printf("\n");
}
