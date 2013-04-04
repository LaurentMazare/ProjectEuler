#include <stdio.h>

int is_prime(int i) {
  int j = 0;
  for (j = 2; j * j <= i; j++) {
    if (i % j == 0) return 0;
  }
  return 1;
}

#define TYPE 100
#define MAXL 1000000000
int nb_primes = 0;
int primes[TYPE];

int aux(int min_factor, int max) {
  int nb = 0;
  int n;
  if (min_factor == nb_primes) return 1;
  for (n=min_factor; n<nb_primes; n++) {
    int p = primes[n];
    int nmax = max;
    while (nmax != 0) {
      nmax /= p;
      nb += aux(n+1, nmax);
    }
  }

  return nb;
}

int main(int argc, char* argv[]) {
  int n;
  for (n=2; n<=TYPE; n++) if (is_prime(n)) {
    primes[nb_primes++] = n;
  }
  printf("%i\n", aux(0, MAXL));

  return 0;
}
