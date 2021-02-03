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

### Main method implementation (`main.c`)

The other sweeping rewrite is of the main method, which is extracted into its own file, `main.c`. The source code is reproduced later in this document. Java uses `System.out.println` to output, but the C code uses `printf`. The previous main method also included several undefined or unused values, which have been omitted here.

### Function implementations (`ex2.c`)

From here, the implementation details are mostly identical to those in the Java program. In the next section, show the source for each function as I discuss its time complexity.

## Part 2: Analyzing time complexity

### 1. The "maximum element" function (`my_max`)

### 2. The "average value" function (`my_avg`)

### 3. The "array copy" function (`my_copy`)

### 4. The "print array" function (`print_numbers`)

### 5. The "reverse in place" function (`my_reverse`)

### 6. The "check if prime" function (`is_prime`)

### 7. The "print only primes" function (`print_prime_numbers`)

## Appendix A: Screenshots of execution

![Screenshot of the unmodified `Exercise2.java` executing within a terminal.](scr-java.png)

![Screenshot of the C program `main.c` executing within a terminal](scr-c.png)

## Appendix B: C source code

