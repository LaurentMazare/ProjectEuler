#include<stdio.h>
#include<stdlib.h>

#define MAX_N 250250
#define EXP 250
#define MOD 10000000000000000ULL

typedef unsigned long long int ull;

int powm(int x, int n) {
  if (n == 0)
    return 1;
  if (n % 2 == 0) {
    x = powm(x, n / 2);
    return (x * x) % EXP;
  }
  return (x * powm(x, n-1)) % EXP;
}

int main(int argc, char* argv[]) {
  ull nb_subsets[EXP];
  ull tmp[EXP];
  for (int i = 0; i < EXP; i++) nb_subsets[i] = 0;
  for (int i = 0; i < MAX_N; i++) {
    int elem = powm(i+1, i+1);
    for (int j = 0; j < EXP; j++) tmp[j] = nb_subsets[j];
    for (int j = 0; j < EXP; j++)
      nb_subsets[j] = (tmp[j] + tmp[(EXP + j - elem) % EXP]) % MOD;
    nb_subsets[elem]= (nb_subsets[elem] + 1) % MOD;
  }
  printf("%llu\n", nb_subsets[0] % MOD);
  return 0;
}
