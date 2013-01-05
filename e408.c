/* Use the inclusion-exclusion principles: we generate all the
 inadmissible points. Then we compute the total number of paths
 and substract the paths that have an inadmissible point then
 add back the ones with two inadmissible points and so on.
 This algorithm is quadratic in the number of inadmissible points
 (which is ~7k for 10^7. */
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define N 10000000
#define MOD_P 1000000007LL
typedef unsigned long long int llu;
llu *facts;
llu *facts_inv;

llu pow_mod(llu x, llu n) {
  if (n == 0) return 1;
  else if (n % 2 == 0) {
    llu p = pow_mod(x, n/2);
    return (p * p) % MOD_P;
  }
  return (x * pow_mod(x, n-1)) % MOD_P;
}

llu chooses(llu n, llu p) {
  return (((facts[n]*facts_inv[p])%MOD_P)*facts_inv[n-p]) % MOD_P;
}

int main(int argc, char* argv[]) {
  facts = malloc((2*N+1) * sizeof *facts);
  facts_inv = malloc((2*N+1) * sizeof *facts_inv);
  facts[0] = facts_inv[0] = 1;
  for (int i = 1; i < 2*N+1; i++) {
    facts[i] = (facts[i-1]*i) % MOD_P;
    facts_inv[i] = pow_mod(facts[i], MOD_P-2);
  }
  // Generate all the inaccessible points in a brute force way.
  // It would be better to use Euclid's formulae.
  llu *inacc_x = malloc(10000 * sizeof *inacc_x);
  llu *inacc_y = malloc(10000 * sizeof *inacc_y);
  int nb_inacc = 0;
  int lim = (int)sqrt(N);
  for (llu x = 1; x <= lim; x++) {
    llu x2 = x * x;
    for (llu y = 1; y <= lim; y++) {
      llu y2 = y * y;
      llu z2 = x2 + y2;
      llu z = (llu)(0.5 + sqrt(z2));
      if (z * z == z2) {
        inacc_x[nb_inacc] = x2;
        inacc_y[nb_inacc] = y2;
        nb_inacc++;
      }
    }
  }
  llu nb_paths = chooses(2*N, N);
  llu *tmp_paths = malloc(10000 * sizeof *tmp_paths);
  for (int idx = 0; idx < nb_inacc; idx++) {
    llu x = inacc_x[idx];
    llu y = inacc_y[idx];
    tmp_paths[idx] = chooses(x+y, x);
    for (int prev = 0; prev < idx; prev++) {
      llu prev_x = inacc_x[prev];
      llu prev_y = inacc_y[prev];
      if (prev_y > y || prev_x > x) continue;
      tmp_paths[idx] = (tmp_paths[idx] + tmp_paths[prev]*chooses(x+y-prev_x-prev_y, x-prev_x)) % MOD_P;
    }
    tmp_paths[idx] = ((MOD_P-1) * tmp_paths[idx]) % MOD_P;
    nb_paths = (nb_paths + tmp_paths[idx] * chooses(2*N-x-y, N-x)) % MOD_P;
  }
  printf("%llu\n", nb_paths);
  return 0;
}
