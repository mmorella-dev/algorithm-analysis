// File: ex2.c
// Author: Mae Morella

// FUNCTION DECLARATIONS

#include <stdbool.h>  // for bool type
#include <stddef.h>   // for size_t definition

// Returns the largest integer in the array
// Precondition: size > 0, a has at least `size` elements
int my_max(const int arr[], size_t size);

// Returns the average of the integers in the array
// Precondition: size > 0, and arr has at least `size` elements
double my_avg(const int arr[], size_t size);

// Given an array, create a clone with the same size and same elements
// Precondition: size > 0, and arr has at least `size` elements
int* my_copy(const int arr[], size_t size);

// Given an array, prints the integers in the indexes [0, size)
// Precondition: arr has at least `size` elements
void print_numbers(const int arr[], size_t size);

// Reverse the indices [0, size) of the array in place.
void my_reverse(int arr[], size_t size);

// Returns whether num is a prime number i.e. there exists no integer i > 2
// such that num/i is an integer.
bool isPrime(long num);

// Given an array, prints every integer in the indexes [0, size) which is a
// prime number.
void print_prime_numbers(const int arr[], size_t size);