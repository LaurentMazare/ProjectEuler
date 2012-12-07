#include<stdio.h>
#include<stdlib.h>
#define MAX_P 60000000
#define MOD_P 1000000000000000000ULL
typedef unsigned long long int llu;

int main(int argc, char* argv[]) {
  int* factors = malloc((MAX_P + 2) * sizeof *factors);
  for (int i = 1; i <= MAX_P+1; i++) factors[i] = i;
  for (int i = 2; i <= MAX_P+1; i++)
    if (factors[i] == i) {
      int j = i * 2;
      while (j <= MAX_P+1) {factors[j] = i; j+=i;}
    }
  int* nb_factors = malloc((MAX_P + 1) * sizeof *nb_factors);
  int max_factors = 0;
  for (int i = 1; i <= MAX_P; i++) {
    int nb = 1;
    for (int j = 0; j < 2; j++) {
      int n = i + j;
      while (n != 1) {
        int f = factors[n];
        int nb_f = 0;
        if (f == 2) n /= 2;
        while (n % f == 0) {n /= f; nb_f++;}
        nb *= 1 + nb_f;
      }
    }
    nb_factors[i] = nb;
    if (nb > max_factors) max_factors = nb;
  }
  free(factors);

  int* nb_df = malloc((max_factors + 1) * sizeof *nb_df);
  int* inv_df = malloc((max_factors + 1) * sizeof *inv_df);
  for (int i = 0; i <= max_factors; i++) nb_df[i] = 0;
  for (int i = 1; i <= MAX_P; i++) nb_df[nb_factors[i]]++;
  int nb_inv = 0;
  for (int i = 0; i <= max_factors; i++)
    if (nb_df[i] != 0) inv_df[i] = nb_inv++;

  llu total = 0;
  int* nbs = malloc(nb_inv * sizeof *nbs);
  llu* pairs = malloc(nb_inv * sizeof *pairs);
  for (int i = 0; i < nb_inv; i++) nbs[i] = pairs[i] = 0;
  for (int i = 1; i <= MAX_P; i++) {
    int inv = inv_df[nb_factors[i]];
    int nb_pairs = 0;
    for (int j = inv+1; j < nb_inv; j++) nb_pairs = (nb_pairs + nbs[j]) % MOD_P;
    llu nb_triples = 0;
    for (int j = inv+1; j < nb_inv; j++) nb_triples = (nb_triples + pairs[j]) % MOD_P;
    nbs[inv]++;
    pairs[inv] = (pairs[inv] + nb_pairs) % MOD_P;
    total = (total + nb_triples) % MOD_P;
    if ((i == 20) || (i == 100) || (i == 1000)) printf("%d %llu\n", i, total);
  }
  printf("%llu\n", total);
  return 0;
}
