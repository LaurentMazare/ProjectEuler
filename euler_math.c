#include "euler_math.h"

int* get_primes(int m, int* nb_primes_out) {
  m += 1;
  char* is_prime = (char*)malloc(m * sizeof(char));
  int nb_primes = 0;
  for (int i = 2; i < m; i++) is_prime[i] = 1;
  for (int i = 2; i < m; i++)
    if (is_prime[i]) {
      nb_primes++;
      int k = i;
      int tmp;
      while ((tmp = k++ * i) < m) is_prime[tmp] = 0;
    }
  int* primes = (int*)malloc(nb_primes * sizeof(int));
  nb_primes = 0;
  for (int i = 2; i < m; i++)
    if (is_prime[i])
      primes[nb_primes++] = i;
  *nb_primes_out = nb_primes;
  free(is_prime);
  printf("Sieve finished: %d primes found!\n", nb_primes);
  return primes;
}
