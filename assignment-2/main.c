// FILE: main.c
// AUTHOR: Mae Morella
// ===================

// This file contains a test program for the functions defined in ex2.h.

#include <stddef.h>  // for size_t definition
#include <stdio.h>   // for printf(const char *format, ...)

#include "ex2.h"

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
