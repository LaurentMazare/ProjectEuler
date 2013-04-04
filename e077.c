#include <stdio.h>
#include <math.h>
#define NBPRIMES 10000
int primes[NBPRIMES];

int is_prime(int i) {
  int j = 0;
  int n = (int)sqrt(i);
  for (j = 2; j <= n; j++) {
    if (i % j == 0) return 0;
  }
  return 1;
}

int aux(int n, int max) {
  int nb = 0;
  int i = 0;
  if (n==0) return 1;
  while (1) {
    int p=primes[i++];
    if (p>max || n<p) break;
    nb+=aux(n-p, p);
  }
  return nb;
}

int main(int argc, char* argv[]) {
  int nb_primes = 0;
  int n = 1;
  while (1) {
    if (is_prime(++n))
      primes[nb_primes++]=n;
    if (nb_primes==NBPRIMES) break;
  }
  n=5;
  while (1) {
    int nb =aux(n,n);
    if (nb>=5000) {
      printf("%i\n", n);
      break;
    }
    n++;
  }
  return 0;
}
