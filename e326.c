// By generating the first hundred terms, we could note that:
// a_{6n}   = 3n
// a_{6n+1} = 4n + 1
// a_{6n+2} = 3n + 1
// a_{6n+3} = n
// a_{6n+4} = 6n + 3
// a_{6n+5} = n
// And the sum_{a_k} % p has period 6*p
// Only the last point is relevant and so we generate all
// the sums of a_k % p for k between 1 and n
#include <stdio.h>
#include <stdlib.h>
#define MAX_P 1000000000000ULL
#define MOD_P 1000000
typedef unsigned long long int llu;

int main(int argc, char* argv[]) {
  int* sums = malloc(MOD_P * sizeof *sums);
  for (int i = 0; i < MOD_P; i++) sums[i] = 0;
  int current_sum = 0;
  for (int n = 0; n < 6 * MOD_P; n++) {
    if (n == 0) current_sum = 0;
    else {
      int n6 = n % 6;
      int nd = n / 6;
      int tmp = n6 == 0 ? 3 * nd
        : n6 == 1 ? 4 * nd + 1
        : n6 == 2 ? 3 * nd + 1
        : n6 == 3 ? nd
        : n6 == 4 ? 6 * nd + 3
        : nd;
      current_sum = (current_sum + tmp) % MOD_P;
    }
    if (n > MAX_P) break;
    sums[current_sum] += 1 + (MAX_P - n) / (6 * MOD_P);
  }
  llu total = 0;
  for (int n = 0; n < MOD_P; n++) {
    llu nb_elt = sums[n];
    total += (nb_elt * (nb_elt - 1)) / 2;
  }
  printf("%llu\n", total);
  return 0;
}
