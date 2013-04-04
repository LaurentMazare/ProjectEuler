#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int is_prime(int i) {
  int ok = 1;
  int j = 0;
  int n = (int)sqrt(i);
  for (j = 2; j <= n; j++) {
    if (i % j == 0) ok = 0;
  }
  return ok;
}

int main(int argc, char* argv[]) {
  int length = 0;
  int i = 1;
  int nb_primes = 0;
  int nb = 1;
  while (1) {
    int j = 0;
    length+=2;
    for (j=0; j<4; j++) {
      nb++;
      i+=length;
      if (is_prime(i)) {
        nb_primes++;
      }
    }
    if (10 * nb_primes < nb) {
      printf("%i\n", length+1);
      break;
    }
  }
  return 0;
}
