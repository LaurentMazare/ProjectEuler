#include "euler_math.h"
int main(int argc, char* argv[]) {
  llu coeffs[25];
  for (int i = 0; i <= 24; i++)
    coeffs[i] = i ? ((i+1) * (i+2) * (i+3)) / 6: 1;
  int nb_primes;
  int* primes = get_primes(100, &nb_primes);
  llu res = 0;
  llu up = 10000000000000000ULL;
  int nb_prod = 1 << nb_primes; // 2 ** 25
  for (int i = 1; i < nb_prod; i++) {
    llu prod = 1;
    int nb_bits = 0;
    int ok = 1;
    for (int j = 0; j < nb_primes; j++)
      if (i & (1 << j)) {
        nb_bits++;
        prod *= primes[j];
        if (prod > up) {
          ok = 0;
          break;
        }
      }
    if (!ok) continue;
    if (nb_bits < 4) continue;
    if (nb_bits % 2 == 0)
      res += coeffs[nb_bits-4] * (up / prod);
    else
      res -= coeffs[nb_bits-4] * (up / prod);
  }
  printf("Nb: %llu before %llu\n", res, up);
  return 0;
}

