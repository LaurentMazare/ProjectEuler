#include "euler_math.h"

char contains_200(llu x) {
  while (x != 0) {
    if (x % 1000 == 200)
      return 1;
    x /= 10;
  }
  return 0;
}

char is_prime_proof(llu x, int* primes, int nb_primes) {
  llu i = 1;
  llu tmp = x;
  while(i <= x) {
    llu x_digit = tmp % 10;
    for (int k = 0; k < 10; k++)
      if (primality_check(x + (k - x_digit) * i, primes, nb_primes))
        return 0;
    i *= 10;
    tmp /= 10;
  }
  return 1;
}

int main(int argc, char* argv[]) {
  int primes_up_to = 1000000;
  llu limit = (llu)primes_up_to * (llu)primes_up_to;
  int nb_primes;
  int* primes = get_primes(primes_up_to, &nb_primes);
  int nb = 0;
  llu squbes[500];
  for (int i = 0; i < nb_primes; i++) {
    llu p = (llu)primes[i];
    llu p2 = p * p;
    if (p2 > limit)
      break;
    for (int j = 0; j < nb_primes; j++) {
      llu q = (llu)primes[j];
      llu sqube = p2 * q * q * q;
      if (sqube > limit)
        break;
      if (contains_200(sqube) && is_prime_proof(sqube, primes, nb_primes))
        squbes[nb++] = sqube;
    }
  }
  printf("Found %i prime proof squbes.\n", nb);
  qsort(squbes, nb, sizeof(llu), sort_llu);
  for (int i = 0; i < 200; i++)
    printf("%d %llu\n", i, squbes[i]);
  return 0;
}
