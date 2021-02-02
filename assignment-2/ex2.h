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
//   arr[i] is defined for all indices i the range [0, size).
//
// As a consequence, these functions do not accept zero-length arrays, nor


#include <stdbool.h>  // for bool type
#include <stddef.h>   // for size_t definition

// FUNCTION DECLARATIONS
// =====================

// Returns the largest integer in the array
int my_max(const int arr[], size_t size);

// Returns the average of the integers in the range arr[0, size)
double my_avg(const int arr[], size_t size);

// Given an array, returns a pointer to a new array with the same size, and containing same elements as the.
int* my_copy(const int arr[], size_t size);

// Given an array, prints the integers in order.
void print_numbers(const int arr[], size_t size);

// Reverses a given array in place.
// Postcondition: arr is now in reverse order.
void my_reverse(int arr[], size_t size);

// Returns whether num is a prime number i.e. there exists no integer i > 2
// such that num/i is an integer.
bool isPrime(long num);

// Given an array, prints every integer in the indexes [0, size) which is a
// prime number.
void print_prime_numbers(const int arr[], size_t size);
