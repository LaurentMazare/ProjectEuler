// We first note that the number of solutions of x^3 = 1 modulo n
// is equal to 3^k where k is the number of distinct prime factors p
// of n such that p = 1 modulo 3
// For 242 solutions (243=3^5 including 1), n should have 5 distinct
// prime factors = 1 mod 3 or 4 such distinct factors + be divisible
// by 9.
#include<stdio.h>
#include<stdlib.h>
#define MAX_P 100000000000LL
#define MAX_PRIME 7500000LL
typedef unsigned long long int llu;

int *prime_d;
llu *factors;
int nb_factors;

llu sum(int nb, int start, llu acc) {
  llu total = 0;
  if (nb == 0) {
    for (int i = 1; i * acc <= MAX_P; i++) {
      llu to_factorize = i;
      if (to_factorize % 9 == 0 && acc % 9 != 0) continue;
      int to_skip = 0;
      while (to_factorize != 1) {
        llu f = prime_d[to_factorize];
        while (to_factorize % f == 0) to_factorize /= f;
        if (f % 3 == 1 && acc % f != 0) {to_skip = 1; break;}
      }
      if (!to_skip) total += i * acc;
    }
    return total;
  }
  for (int i = start; i < nb_factors; i++) {
    int f = factors[i];
    if (acc * f > MAX_P) break;
    total += sum(nb-1, i+1, acc * f);
  }
  return total;
}

int main(int argc, char* argv[]) {
  prime_d = malloc(MAX_PRIME * sizeof *prime_d);
  nb_factors = 1;
  for (int i = 2; i < MAX_PRIME; i++) prime_d[i] = i;
  for (int i = 2; i < MAX_PRIME; i++)
    if (prime_d[i] == i) {
      int j = i + i;
      while (j < MAX_PRIME) {prime_d[j] = i; j += i;}
      if (i % 3 == 1) nb_factors += 1;
    }
  factors = malloc(nb_factors * sizeof *factors);
  nb_factors = 0;
  factors[nb_factors++] = 9;
  for (int i = 2; i < MAX_PRIME; i++) if (prime_d[i] == i && i % 3 == 1) factors[nb_factors++] = i;
  printf("Found %d relevant primes.\n", nb_factors);
  printf("%llu\n", sum(5, 0, 1));
  return 0;
}
