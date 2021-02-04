# Assignment 2: Java $\rightarrow$ C/C++

KSU College of Computing and Software Engineering<br>
CS 4306 - Algorithm Analysis

Mae Morella ([mmorella@students.kennesaw.edu](mailto:mmorella@students.kennesaw.edu))<br>
February 1, 2021

## Problem Statement

1. Given the Java source file `Exercise2.java`, rewrite all of its functionality in C/C++.
2. For each operation, analyze the running time in terms of big-$O$ (upper bound) and big-$\Theta$ (tight bound) notation.

## Part 1: Rewriting the program in C

### Taking inventory

The Java program contains the following:

1. `myMax` - a method which returns the largest number in an array
1. `myAvg` - a method which returns the average of the numbers in an array
1. `myCopy` - a method which creates a new array as a copy of another array
1. `printNumbers` - a method which outputs an array's contents
1. `myReverse` - a method which reverses an array in place
1. `isPrime` - a method which determines whether a given integer is prime
1. `printPrimeNumbers` - a method which outputs the numbers in an array which are prime.
1. `main` - a program which tests the functionality of the above methods.

A notable feature of the Java implementation is that it's very "C-ish" and concrete. In other words, it makes heavy use of index-based `for` loops, static `int[]` arrays, etc. Java already shares a lot of language features with C, so translating is not that complicated.

The lack of OO in C is not a problem, because the Java class simply uses the `Exercise2` as a namespace for storing static methods. Static methods in Java are analogous to functions in C.

### Implementation

#### Header file (`ex2.h`)

From the above, I began creating function declarations in a C header.

One major difference in the Java and C syntaxes is that static arrays in C degrade into pointers; they don't store their own length.

To pass in an array as a function parameter, we're actually passing in a pointer. We need an additional parameter to communicate the array's length. C also cannot return an array from a function; instead the code returns an `int*` pointer, which can be treated like an array.

The result is the following function prototypes:

```c
int my_max(const int arr[], size_t size);
```

```c
double my_avg(const int arr[], size_t size);
```

```c
int* my_copy(const int arr[], size_t size);
```

```c
void print_numbers(const int arr[], size_t size);
```

```c
void my_reverse(int arr[], size_t size);
```

```c
bool isPrime(long num);
```

```c
void print_prime_numbers(const int arr[], size_t size);
```

### Main method implementation (`main.c`)

The other sweeping rewrite is of the main method, which is extracted into its own file, `main.c`. The source code is reproduced later in this document. Java uses `System.out.println` to output, but the C code uses `printf`. The previous main method also included several undefined or unused values, which have been omitted here.

### Function implementations (`ex2.c`)

From here, the implementation details are mostly identical to those in the Java program. In the next section, show the source for each function as I discuss its time complexity.

## Part 2: Analyzing time complexity

In the below descriptions, I'll show my C implementation for each function, and then analyze it.

In cases where not specified, assume that the quantity $n$ is equivalent to the function parameter `n`, a positive integer representing the size of the input array.

### 1. The "maximum element" function (`my_max`)

```c
// Returns the largest integer in the array
// Precondition: n > 0, a has at least `n` elements
int my_max(const int a[], size_t n) {
  int max = a[0];
  for (int i = 1; i < n; i++)
    if (a[i] > max) max = a[i];
  return max;
}
```
### 2. The "average value" function (`my_avg`)

```c
// Returns the average of the integers in the array
// Precondition: size > 0, and arr has at least `size` elements
double my_avg(const int a[], size_t n) {
  double sum = 0.0;
  for (int i = 0; i < n; i++) {
    sum += a[i]; // <- implicit cast from int to double
  }
  return sum / n;
}
```

### 3. The "array copy" function (`my_copy`)

```c
int* my_copy(const int a[], size_t n) {
  int* b_ptr = (int*)malloc(n * sizeof(int));
  for (int i = 0; i < n; i++) {
    b_ptr[i] = a[i];
  }
  return b_ptr;
}
```

### 4. The "print array" function (`print_numbers`)

```c
void print_numbers(const int a[], size_t n) {
  for (int i = 0; i < n; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
}
```

### 5. The "reverse in place" function (`my_reverse`)

```c
void my_reverse(int a[], size_t n) {
  for (int i = 0; i < n / 2; i++) {
    int j = (n - 1) - i; // reverse iterator
    int t = a[i];        // temp storage for swap
    a[i] = a[j];
    a[j] = t;
  }
}
```

### 6. The "check if prime" function (`is_prime`)

```c
bool isPrime(long m) {
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
```

### 7. The "print only primes" function (`print_prime_numbers`)

```c
void print_prime_numbers(const int a[], size_t n) {
  for (int i = 0; i < n; i++) {
    if (is_prime(a[i])) {
      printf("%d ", a[i]);
    }
  }
  printf("\n");
}
```

## Appendix A: Screenshots of execution

![Screenshot of the unmodified `Exercise2.java` executing within a terminal.](scr-java.png)

![Screenshot of the C program `main.c` executing within a terminal](scr-c.png)

## Appendix B: C source code

### `main.c`

```c
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

  // Calculate and print maximum value
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
```

### `ex2.h`

```c
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
bool isPrime(long num);

// Given an array, print only the elements which are prime numbers
void print_prime_numbers(const int arr[], size_t size);
```

### `ex2.c`

```c
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
    int j = (n - 1) - i; // reverse iterator
    int t = a[i];        // temp storage for swap
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
```
