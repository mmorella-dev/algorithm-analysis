// File: ex2.c
// Author: Mae Morella

// FUNCTION DECLARATIONS

#include <stddef.h>  // for size_t definition
#include <stdbool.h>  // for bool type

// Returns the largest integer in the array
// Precondition: size > 0, a has at least `size` elements
int my_max(int a[], size_t size);

// Returns the average of the integers in the array
// Precondition: size > 0, a has at least `size` elements
double my_avg(int a[], size_t size);

//
int* my_copy(int a[], size_t size);

//
void print_numbers(int a[], size_t size);

// Reverse the array in place.
void my_reverse(int a[], size_t size);

// Returns whether num is a prime number
// i.e. there exists no integer i > 2 such that num/i is an integer.
// Executes in O(n) time
bool isPrime(long num);

//
void print_prime_numbers(int a[], size_t size);