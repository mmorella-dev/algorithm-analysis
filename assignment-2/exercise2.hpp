// FILE: exercise2.hpp
// AUTHOR: mae morella
#ifndef EXERCISE2_HPP
#define EXERCISE2_HPP

#include <vector>  // for std::vector

namespace Exercise2 {
using value_t = int;  // a value which
using vector_t = std::vector<value_t>;

// Given the vector a, return the largest value in that vector.
value_t myMax(const vector_t &a);

// Given the vector a, return the average of its values.
double myAvg(const vector_t &a);

// Given the vector, returns a new vector containing the same values.
vector_t myCopy(const vector_t &a);

// Given the vector `a`, prints every number in `a`.
void printNumbers(const vector_t &a);

// Reverses the vector in place.
void myReverse(vector_t &a);

// Determines whether `num` is a prime number.
bool isPrime(long num);

// Prints every number in a which is prime.
void printPrimeNumbers(const vector_t &a);

}  // namespace Exercise2

#endif /* GRANDPARENT_H */