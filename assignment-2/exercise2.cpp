// FILE: exercise2.cpp
// AUTHOR: mae morella

#include "exercise2.hpp"

#include <functional>  // for std::plus
#include <iostream>    // for std::cout
#include <numeric>     // for std::accumulate
#include <vector>      // for std::vector

int main() {
  using namespace Exercise2;
  vector_t numbers = {10, 5, 15, 12};

  // Calculate print maximum value
  value_t highest = myMax(numbers);
  std::cout << "The highest number: " << highest << '\n';

  // Calculate and print average
  double avg = myAvg(numbers);
  std::cout << "The average of the numbers: " << avg << '\n';

  // Make a copy of the array
  vector_t outNumbers = myCopy(numbers);
  std::cout << "The original array: ";
  // Print the copied array
  printNumbers(outNumbers);

  // Reverse the array in place, and print it
  myReverse(outNumbers);
  std::cout << "The reverse array: ";
  printNumbers(outNumbers);

  // Print the prime numbers in the array.
  std::cout << "The prime numbers in the array: ";
  printPrimeNumbers(outNumbers);

  std::cout << '\n';  // final newline
  return 0;
}

namespace Exercise2 {

// FUNCTION IMPLEMENTATIONS

value_t myMax(const vector_t &a) {
  auto it = a.begin();
  value_t max = *it;
  while (it++ != a.end()) {
    if (*it > max) max = *it;
  }
  return max;
}
double myAvg(const vector_t &a) {
  int count = a.size();
  double sum = 0.0;
  for (auto x : a) sum += x;
  return sum / count;
}

inline vector_t myCopy(const vector_t &a) { return vector_t(a); }

void printNumbers(const vector_t &a) {
  for (const auto n : a) std::cout << n << ' ';
  std::cout << '\n';
}
void myReverse(vector_t &a) {
  // similar implementation to std::reverse from <algorithm> header
  auto first = a.begin(), last = a.end();
  while (first != last && first != --last) {  // performs size/2 swaps.
    std::swap(*first, *last);
    ++first;
  }
}
bool isPrime(long num) {
  if (num < 2) return false;
  for (long i = 2; i * i <= num; i++)
    if (num % i == 0) return false;
  return true;
}
void printPrimeNumbers(const vector_t &a) {
  for (const auto n : a) {
    if (isPrime(n)) std::cout << n << ' ';
  }
  std::cout << '\n';
}
}  // namespace Exercise2