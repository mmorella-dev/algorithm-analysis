// FILE: ex2.h
// AUTHOR: Mae Morella
// ===================

// This header declares functions for the program implemented in ex2.c.
// Each function performs some basic operation on an array of integers.

// IMPLICIT PRECONDITIONS
// ======================
// Most functions take two parameters: an input array `arr`, and `size`,
// assumed to be the number of elements in that array. For all functions
// with these parameters, the following precondition is implied:
//
//   arr[i] is defined for all indices in the range [0, size).
//
// As a consequence, these functions do not accept zero-length arrays, and
// passing a `size` greater than the array's actual capacity will result in
// undefined behavior.

#include <stdbool.h>  // for bool type
#include <stddef.h>   // for size_t definition

// FUNCTION DECLARATIONS
// =====================

// Returns the largest integer in the given array
int my_max(const int arr[], size_t size);

// Returns the average of the integers in the given array
double my_avg(const int arr[], size_t size);

// Returns a pointer to a new array which is the same size as the given array,
// and contains the same elements.
int* my_copy(const int arr[], size_t size);

// Given an array, prints its elements in order.
void print_numbers(const int arr[], size_t size);

// Given an array, reverses the order of its elements.
// Postcondition: arr is now in reverse order.
void my_reverse(int arr[], size_t size);

// Returns whether the given number is prime.
// i.e. there exists no integer i > 1 such that num/i is an integer.
bool is_prime(long num);

// Given an array, print only the elements which are prime numbers
void print_prime_numbers(const int arr[], size_t size);
