#include "euler_math.h"
#include "math.h"
#define MAX_P 200000000000LL
#define LIM_P 40000000LL

llu count_rec(int* primes, int nb_primes, llu idx, llu current_n, llu current_phi) {
  llu sum = 0;
  llu max_p = 1 + MAX_P / current_n;
  for (llu idxp = idx; idxp < nb_primes; ++idxp) {
    llu p = primes[idxp];
    if (max_p < p) break;
    llu n = current_n * p, phi = current_phi * (p-1);
    if (current_n != 1 && (n-1) % (n-phi) == 0) {
      printf("Found: %llu (%llu)\n", n, phi);
      sum += n;
    }
    sum += count_rec(primes, nb_primes, idxp+1, n, phi);
  }
  return sum;
}

int main(int argc, char* argv[]) {
  int nb_primes;
  int* primes = get_primes(LIM_P, &nb_primes);
  printf("%llu\n", count_rec(primes, nb_primes, 0, 1, 1));
  return 0;
}
