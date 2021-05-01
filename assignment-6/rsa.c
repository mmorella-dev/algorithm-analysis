/*
 * rsa.c
 * Author: Morella, Mae
 *
 * A simple implementation of the RSA cryptosystem algorithm using small
 * numbers. Extremely breakable. Should not be used for actual cryptography.
 */

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct KeyPair {
  unsigned long e;
  unsigned long n;
};

// The value returned by extended_gcd
struct EuclidTriple {
  unsigned long d;  // the greatest common denominator of the inputs
  long x;           // an integer such that d = ax + by
  long y;           // an integer such that d = ax + by
};

// Returns (d, x, y) where d is the GCD of a, b
// x and y are assigned such that d = ax + by
struct EuclidTriple extended_gcd(long a, long b) {
  struct EuclidTriple t = {b, 0, 1};
  if (a != 0) {
    struct EuclidTriple p = extended_gcd(b % a, a);
    t.d = p.d;
    t.x = p.y - (b / a) * p.x;
    t.y = p.x;
  }
  printf("%d * %d + %d * %d == %d\n", a, t.x, b, t.y, t.d);
  assert(t.d == (a * t.x) + (b * t.y));
  return t;
}

// Returns a^b (mod n)
// Precond: a, b >= 0, n > 0
unsigned long modular_exponentiation(unsigned long a, unsigned long b,
                                     unsigned long n) {
  int c = 0;
  int d = 1;
  int width = (int)log2(b) + 1;
  for (int i = width; i >= 0; i--) {
    c = 2 * c;
    d = (d * d) % n;
    if ((b >> i) & 1 == 1) {
      c += 1;
      d = (d * a) % n;
    }
  }
  return d;
}

struct KeyPair generate_public_key(unsigned int p, unsigned int q,
                                   unsigned int e) {
  int n = p * q;
  // Calculate gcd to ensure that e and phi are relatively prime
  assert(extended_gcd(e, (p - 1) * (q - 1)).d == 1);
  struct KeyPair public = {e, n};
  return public;
}

struct KeyPair generate_private_key(unsigned int p, unsigned int q,
                                    unsigned int e) {
  unsigned int n = p * q;
  int phi = (p - 1) * (q - 1);
  struct EuclidTriple t = extended_gcd(e, phi);
  assert(t.d == 1);  // ensure the gcd is 1

  // let d be the multiplicative inverse, modulo phi(n)
  int d =
      (t.x % phi + phi) % phi;  // use corrolary 31.26 to find the mult inverse

  assert((e * d) % phi == 1);  // check that d is the mult inverse
  struct KeyPair private = {d, n};
  return private;
}

unsigned int crypt(unsigned long msg, struct KeyPair *key) {
  return modular_exponentiation(msg, key->e, key->n);
}

int main(int argc, char *argv[]) {
  FILE *f = fopen("keygen.env", "r");
  if (!f) {
    fprintf(stderr, "Error opening keygen.env!\n");
    return EXIT_FAILURE;
  }
  unsigned int p, q, e;
  fscanf(f, "%d,%d,%d", &p, &q, &e);
  struct KeyPair pub = generate_public_key(p, q, e);
  printf("Public key: {%d,%d}\n", pub.e, pub.n);
  struct KeyPair priv = generate_private_key(p, q, e);
  printf("Private key: {%d,%d}\n", priv.e, priv.n);
  printf("Enter a number to encrypt (< %d): ", pub.n);
  unsigned long message;
  scanf("%zzu", &message);
  unsigned int msg = crypt(message, &pub);
  printf("encrypted: %d\n", msg);
  printf("decrypted: %d\n", crypt(msg, &priv));
  fclose(f);
  return EXIT_SUCCESS;
}