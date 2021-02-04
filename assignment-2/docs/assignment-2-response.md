# Assignment 2: Java $\rightarrow$ C/C++

KSU College of Computing and Software Engineering<br>
CS 4306 - Algorithm Analysis
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

The *basic operation* (or, most time-consuming operation) of this function is to access the array at `a[i]`, and compare it against the previously found value stored in `max`. The for loop executes that operation once for every integer in the range $\left[1, n\right)$. Therefore, we can define a time function $C(n)$ as follows:

$$
C(n) = \sum\limits_{i = 1}^{n-1} 1 = n - 1 \in \Theta(n)
$$

The time complexity of `my_max` is $\Theta(n)$, where $n$ is the size of the input array.

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

We can observe that this function's basic operation is accessing the array at `a[i]`, implicitly casing it to a double, and adding it to the variable `sum`.  The for loop executes once for every integer in the range $[0, n)$.

$$
C(n) = \sum\limits_{i = 0}^{n-1} 1 = n \in \Theta(n)
$$

The running time of `my_avg` is within $\Theta(n)$.

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

In this function, there are two "basic operations", and it is not certain which one will take more time.

#### Operation 1: Allocate memory

This function's first operation is to call the C `malloc` function. `malloc` allocates a block of heap memory, and return a pointer to that memory. This block is made up of $n$ "chunks" of memory, where each "chunk" is the number of bytes needed to store an `int` value.

The exact running time of this memory allocation is not certain, as it is defined by the implementation. It's easy to imagine that a naive implementation would perform at most one basic operation per each allocated byte, and so we can assume an upper bound of $O(n)$. However, many systems are known to use efficient $O(1)$ algorithms (source: ["Time complexity of memory allocation"](https://stackoverflow.com/questions/282926/time-complexity-of-memory-allocation) from stackoverflow.com). I'll assume that the complexity will have an upper bound such that $t_1(n) \in O_1(n)$, and a lower bound such that $t_1(n) \in \Omega(1)$.

#### Operation 2: Copy array

The other basic operation of this function is the "copy" operation of `a[i]`, and assigning that value to `b[i]`. This occurs within a for loop from $0$ to $n-1$. As shown in the above cases, we can trivially show that this loop will have a tightly bounded linear time complexity, $t_2(n) \in \Theta(n)$.

#### Putting them together

The textbook gives the following theorem for finding the time complexity resulting from performing two algorithms in sequence:

$$
\begin{align*}
\text{If } t_1(n) &\in O(g_1(n))\text{, and } t_2(n) \in O(g_2(n))\text{, then}, \\
&t_1(n) + t_2(n) \in O(\max\{g_1(n), g_2(n)\})
\end{align*}
$$

Between the two operations, the maximum time complexity is $O(n)$. Therefore, the combination of these two operations $t_1(n) + t_2(n)$ is also in $O(n)$.

We can apply the same theorem to the lower bounds. We know that $t_1(n) \in \Omega(1)$ and $t_2(n) \in \Omega(n)$, therefore $t_1(n) + t_2(n) \in \Omega(n)$.

Assuming that the `malloc` operation is in $O(n)$, we can therefore conclude that the running time complexity of this `my_copy` implementation is within $\Theta(n)$. In other words, it is **strictly linear**.

### 4. The "print array" function (`print_numbers`)

```c
void print_numbers(const int a[], size_t n) {
  for (int i = 0; i < n; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
}
```

This function iterates over the array, and prints each item to the console.

$$
C(n) = \sum\limits_{i = 0}^{n-1} 1 = n \in \Theta(n)
$$

Like the **strictly linear** array functions described above, this algorithm is also $\Theta(n)$.

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

This function reverses an array in place. It loops on the range $[0, \frac{n}{2})$, and so executes the "swap" operation exactly $\frac12 n$ times.

$$
C(n) = \sum\limits_{i = 0}^{n/2 - 1} 1 = \frac n2 \in \Theta(n)
$$

This results in the **strictly linear** time complexity $\Theta(\frac12 n)$, which is equivalent to $\Theta(n)$.

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

This function calculates the primality of an integer $m$ by dividing it against every natural number in the range $[2, \sqrt m]$. In the worst case (i.e. a prime is found), the maximum number of basic operations needed to do so is defined by:

$$
C_{worst}(m) = \sum\limits_{i = 2}^{\sqrt{m}} 1 = \sqrt{m} - 2 \in O(\sqrt{m})
$$

If $m$ were the input size, this would normally imply that the algorithm is $\in O(\sqrt m)$, and therefore sublinear. However, conventionally, the "input size" for this algorithm is not $m$'s *value*, but rather its *length*, i.e. the approximate number of bits (or keystrokes, hex digits, etc) needed to represent it. We know that $m = 2^n - 1$ where $n$ is the number of bits needed to represent m. Therefore we can substitute that value for $m$ in the above function to find the complexity in terms of size $n$:

$$
C_{worst}(n) = \sum\limits_{i = 2}^{\sqrt{2^n - 1}} 1 = \sqrt{2^n-1} - 2 \in  O(2^{n/2})
$$

In all cases where $m$ is an even number divisible by two, the loop will perform only one operation before exiting. In other words, for all even numbers, the execution will be constant.

$$
C(1) = \sum\limits_{i = 2}^{\sqrt 1} 1 = 0 \in \Omega(1)
$$

Therefore, in terms of the binary input size $n$ (equal to $\lceil log_2 n\rceil$), `is_prime` has an **exponential** upper bound $O(2^{n/2})$ and a **constant** lower bound $\Omega(1)$.

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

This function iterates over the array, checks whether each number is prime, and if it is, prints it. In this case, the basic operation is the inner loop of `is_prime`, a function we know to have exponential complexity in the worst case.

Suppose the input array $A$:

$$
A = \{A_0, A_1, \dots,A_{n-1}\}
$$

The complexity of this function relies simultaneously on the size of the input array $n = |A|$, and the length of the biggest input inside the array, $m = log_2 (A_{max})$.

$$
C(n, m) = \sum\limits_{i = 0}^{n - 1} \left( \sum\limits_{i = 2}^{\sqrt{2^m - 1}} 1 \right) \in O(n \cdot 2^{m/2})
$$

Therefore, the time complexity of `print_prime_numbers` has an upper bound $O(n \cdot 2^{m/2})$.

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
