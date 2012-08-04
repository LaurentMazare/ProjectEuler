#include "euler_math.h"
long long int hidden(int x, int* primes, int nb_primes) {
  llu sum = 0;
  for (int i = 1; i <= x; i++) {
    sum += i - phi_with_primes(i, primes, nb_primes);
  }
  return 6 * sum;
}

int main(int argc, char* argv[]) {
  int nb_primes;
  int* primes = get_primes(10000, &nb_primes);
  printf("%llu\n", hidden(10, primes, nb_primes));
  printf("%llu\n", hidden(1000, primes, nb_primes));
  printf("%llu\n", hidden(100000000, primes, nb_primes));
  return 0;
}
