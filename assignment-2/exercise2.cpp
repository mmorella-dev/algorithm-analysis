// FILE: exercise2.cpp
// AUTHOR: mae morella


#include <algorithm>
#include <functional>  // for std::plus
#include <iostream>    // for std::cout
#include <numeric>     // for std::accumulate
#include <vector>      // for std::vector

int main() {
  using namespace Exercise2;
  std::vector<int> v = {10, 5, 15, 12};

  // Calculate print maximum value
  int highest = *std::max_element(v.begin(), v.end());
  std::cout << "The highest number: " << highest << '\n';

  // Calculate and print average
  double sum = std::accumulate(v.begin(), v.end(), 0.0);
  double avg = sum / v.size();
  std::cout << "The average of the numbers: " << avg << '\n';

  // Make a copy of the array
  std::vector<int> outNumbers(v);  // copy constructor
  std::cout << "The original array: ";
  // Print the copied array
  for (int n : outNumbers) std::cout << n << ' ';
  std::cout << '\n';

  // Reverse the array in place, and print it
  std::reverse(outNumbers.begin(), outNumbers.end());
  std::cout << "The reverse array: ";
  for (int n : outNumbers) std::cout << n << ' ';
  std::cout << '\n';

  // Print the prime numbers in the array.
  std::cout << "The prime numbers in the array: ";
  std::copy_if(outNumbers.begin(), outNumbers.end(),
               std::ostream_iterator<int>(std::cout, " "), isPrime);
  std::cout << '\n';

  std::cout << '\n';  // final newline
  return 0;
}

namespace Exercise2 {

// FUNCTION IMPLEMENTATIONS

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