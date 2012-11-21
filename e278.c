#include "euler_math.h"

int main(int argc, char* argv[]) {
  int nb_primes;
  int* primes = get_primes(5000, &nb_primes);
  lli total = 0;
  for (int i1 = 0; i1 < nb_primes; i1++) {
    lli p = primes[i1];
    for (int i2 = i1+1; i2 < nb_primes; i2++) {
      lli q = primes[i2];
      for (int i3 = i2+1; i3 < nb_primes; i3++) {
        lli r = primes[i3];
        total += p * q * r * 2LL - p * q - q * r - p * r;
      }
    }
  }
  printf("%lli\n", total);
  return 0;
}
