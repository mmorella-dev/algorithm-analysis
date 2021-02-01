// File: ex2.c
// Author: Mae Morella
// A source file
#include "ex2.h"

#include <stdbool.h>  // for bool type
#include <stddef.h>   // for size_t definition
#include <stdio.h>    // for printf(const char *format, ...)
#include <stdlib.h>   // for malloc(size_t size)

// MAIN FUNCTION

int main() {
  int numbers[] = {10, 5, 15, 12};
  const size_t size = sizeof(numbers) / sizeof(numbers[0]);

  // Calculate print maximum value
  int highest = myMax(numbers, size);
  printf("The highest number: %d\n", highest);

  // Calculate and print average
  double avg = myAvg(numbers, size);
  printf("The average of the numbers: %g\n", avg);

  // Make a copy of the array
  int* outNumbers = myCopy(numbers, size);
  // Print the copied array
  printf("The original array: ");
  printNumbers(outNumbers, size);

  // Reverse the array in place, and print it
  myReverse(outNumbers, size);
  printf("The reverse array: ");
  printNumbers(outNumbers, size);

  // Print the prime numbers in the array.
  printf("The prime numbers in the array: ");
  printPrimeNumbers(outNumbers, size);

  printf("\n");
  return 0;
}

// FUNCTION IMPLEMENTATIONS (defined and documented in ex2.h)

int myMax(int a[], size_t size) {
  int max = a[0];
  for (int i = 1; i < size; i++)
    if (a[i] > max) max = a[i];
  return max;
}
double myAvg(int a[], size_t size) {
  if (size == 0) return 0;
  double sum = 0;
  for (int i = 0; i < size; i++) sum += a[i];
  return sum / size;
}
int* myCopy(int a[], size_t size) {
  int* copy = (int*)malloc(size * sizeof(int));
  for (int i = 0; i < size; i++) {
    copy[i] = a[i];
  }
  return copy;
}
void printNumbers(int a[], size_t size) {
  for (int i = 0; i < size; i++) printf("%d ", a[i]);
  printf("\n");
}
void myReverse(int a[], size_t size) {
  int i = 0, j = size;
  for (int i = 0, j = size - 1; i < j; i++, j--) {
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
  }
}
bool isPrime(long num) {
  if (num < 2) return false;
  for (long i = 2; i * i <= num; i++)
    if (num % i == 0) return false;
  return true;
}
void printPrimeNumbers(int a[], size_t size) {
  for (int i = 0; i < size; i++) {
    if (isPrime(a[i])) printf("%d ", a[i]);
  }
  printf("\n");
}