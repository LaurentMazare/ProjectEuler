#include<stdio.h>
#include<stdlib.h>
typedef long long int lli;
typedef long long unsigned int llu;

#define M 100000000
#define N 100000000000LL
#define EXP 15

lli gcd_l(lli a, lli b) {
  while (b != 0) {
    lli tmp = b;
    b = a % b;
    a = tmp;
  }
  return a;
}

lli pow_mod(lli x, lli n, lli mod) {
  if (n == 0) return 1;
  if (n & 1) return (x * pow_mod(x, n-1, mod)) % mod;
  lli res = pow_mod(x, n/2, mod);
  return (res * res) % mod;
}

int main(int argc, char* argv[]) {
  int nb_primes = 0;
  int* factors = malloc((M+1) * sizeof *factors);
  for (int i = 2; i <= M; ++i) factors[i] = i;
  for (int i = 2; i <= M; ++i)
    if (factors[i] == i) {
      nb_primes++;
      int j = i;
      while (j <= M) {factors[j] = i; j +=i;}
    }
  int* primes = malloc(nb_primes * sizeof *primes);
  nb_primes = 0;
  for (int i = 2; i <= M; ++i)
    if (factors[i] == i) primes[nb_primes++] = i;
  printf("The sieve found %d primes!\n", nb_primes);

  llu res = 0;
  for (int idx_p = 0; idx_p < nb_primes; ++idx_p) {
    lli p = primes[idx_p];
    // First, find a primitive root g modulo p, i.e. g is a generator for Z/pZ*
    // Try any value starting from 2, this is quite efficient in practice.
    lli g;
    for (g = 2;; g++) {
      // If for all prime factors q of p-1, g^((p-1)/q) is different from 1,
      // Then g is a primitive root modulo p.
      lli phi = p - 1;
      int ok = 1;
      while (1 < phi) {
        int q = factors[phi];
        while (phi % q == 0) phi /= q;
        if (pow_mod(g, (p-1)/q, p) == 1) {ok = 0; break;}
      }
      if (ok) break;
    }
    // Then find the roots of unity mod p
    // i.e. the solutions to x^15 = 1 mod p
    // h is a primitive roots, that is roots are h, h^2, ..., h^d
    // See http://en.wikipedia.org/wiki/Root_of_unity_modulo_n
    lli d = gcd_l(EXP, p-1);
    lli h = pow_mod(g, (p-1)/d, p);
    // p-1 is a solution to x^15 = -1 mod p, roots are:
    // (p-1)*h^i where i is between 0 and d-1
    llu start = p-1;
    for (int i = 0; i < d; ++i) {
      res += p * (1 + (N-start) / p);
      start = (start * h) % p;
    }
  }
  printf("%llu\n", res);
  return 0;
}
