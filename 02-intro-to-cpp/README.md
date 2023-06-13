# 2. Converting Java to C++

This assignment consists of the simple task of rewriting Exercise2.java (a single Java class containing some elementary array operations) into C and C++.

I created two solutions:

* [ex2.c](ex2.c) – a simple C implementation
* [exercise2.cpp](exercise2.cpp) – a C++14 implementation, making use of STL containers and algorithms.

See my [full report](docs/assignment-2-response.md).

## Usage

```sh
make # Compile
java Exercise2  # Java implementation
./ex2           # C implementation
./exercise2     # C++ implementation
```

### Sample output

```txt
The highest number: 15
The average of the numbers: 10.5
The original array: 10 5 15 12 
The reverse array: 12 15 5 10 
The prime numbers in the array: 5
```