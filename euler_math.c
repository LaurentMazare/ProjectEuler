#include "euler_math.h"

int* get_primes(int m, int* nb_primes_out) {
  m += 1;
  char* is_prime = (char*)malloc(m * sizeof(char));
  int nb_primes = 0;
  for (int i = 2; i < m; i++) is_prime[i] = 1;
  for (int i = 2; i < m; i++)
    if (is_prime[i]) {
      nb_primes++;
      int k = 2;
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

int primality_check(int x, int* primes, int nb_primes) {
  if (x <= primes[nb_primes-1]) {
    // Bisection search
    int lo = 0;
    int up = nb_primes - 1;
    while ((up - lo) > 1) {
      int mid = (lo + up) / 2;
      if (primes[mid] == x)
        return 1;
      if (primes[mid] < x)
        lo = mid;
      else
        up = mid;
    }
    return (primes[lo] == x || primes[up] == x);
  }
  for (int i = 0; i < nb_primes; i++) {
    if (x == i) // Should never happen
      return 1;
    if (x % i == 0)
      return 0;
  }
  return 1;
}

char* resieve(lli lo, lli size, int* primes, int nb_primes) {
  char* result = (char*)malloc(size * sizeof(char));
  for (int i = 0; i < size; i++) result[i] = 1;
  for (int i = 0; i < nb_primes; i++) {
    lli k = lo / primes[i];
    lli tmp;
    if (k <= 1) k = 2;
    while ((tmp = k++ * primes[i] - lo) < size) {
      if (tmp >= 0) {
        result[tmp] = 0;
      }
    }
  }
  return result;
}

int gcd_int(int a, int b) {
  while (b != 0) {
    int tmp = b;
    b = a % b;
    a = tmp;
  }
  return a;
}

llu gcd_llu(llu a, llu b) {
  while (b != 0) {
    llu tmp = b;
    b = a % b;
    a = tmp;
  }
  return a;
}
