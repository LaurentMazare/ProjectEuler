// Use the following formula:
// D(n)=\sum_{k=1}^n moebius(k)((floor(n/k)+1)^3-1)
// As n is quite large, we use a segmented sieve.
#include "euler_math.h"
#define NB_SIEVES 100000LL
#define SIEVE_SIZE 100000LL
#define MOD_P 1000000000LL

int main(int argc, char* argv[]) {
  int nb_primes;
  int* primes = get_primes(SIEVE_SIZE, &nb_primes);
  int* mu = malloc(SIEVE_SIZE * sizeof *mu);
  lli* is_p = malloc(SIEVE_SIZE * sizeof *is_p);
  lli n = SIEVE_SIZE * NB_SIEVES;
  lli d = 0;
  double d_f = 0;
  for (int sieve_id = 0; sieve_id < NB_SIEVES; sieve_id++) {
    lli base = SIEVE_SIZE * sieve_id + 1;
    for (int i = 0; i < SIEVE_SIZE; i++) {
      mu[i] = 1;
      is_p[i] = base+i;
    }
    for (int p_id = 0; p_id < nb_primes; p_id++) {
      lli p = primes[p_id];
      lli bb = base % p == 0 ? 0: (1 + base / p) * p - base;
      while (bb < SIEVE_SIZE) {
        while (is_p[bb] % p == 0) is_p[bb] /= p;
        mu[bb] *= -1;
        bb += p;
      }
      p *= p; // mu(x) = 0 if x is not square free
      bb = base % p == 0 ? 0: (1 + base / p) * p - base;
      while (bb < SIEVE_SIZE) {mu[bb] = 0; bb += p;}
    }
    for (int k = 0; k < SIEVE_SIZE; k++) {
      lli tmp = n/(base + k) + 1;
      lli tmp2 = tmp % MOD_P;
      lli tmp3 = ((tmp2 * tmp2) % MOD_P * tmp2) % MOD_P;
      double tmp_f = tmp;
      if (base+k == 1) mu[k] == 0;
      else if (is_p[k] == base + k) mu[k] = -1; // Prime number
      else if (is_p[k] != 1) mu[k] = -mu[k];
      d = (MOD_P + d + mu[k] * (tmp3 - 1)) % MOD_P;
      d_f += mu[k] * (tmp_f*tmp_f*tmp_f - 1);
//      printf("%llu %d\n", base+k, mu[k]);
    }
  }
  printf("%.9g %lli\n", d_f, d);
  return 0;
}
