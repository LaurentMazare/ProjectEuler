// Solution using the hook-formula as described in:
// http://en.wikipedia.org/wiki/Young_tableau
// Note that you have to reverse the numbering so that the
// structure is an actual Young tableau.
#include<stdio.h>
#define MOD_P 76543217LL
#define M 10000
#define N 5000
typedef long long int lli;
int cache[MOD_P];
lli pow_mod(lli x, lli n) {
  if (n == 0) return 1;
  else if (n % 2 == 0) {
    lli p = pow_mod(x, n / 2);
    return (p * p) % MOD_P;
  }
  else return (x * pow_mod(x, n-1)) % MOD_P;
}

lli inv(lli x) {
  if (cache[x] >= 0) return cache[x];
  return cache[x] = pow_mod(x, MOD_P-2); // Fermat's little Theorem
}

int main(int argc, char* argv[]) {
  for (int i = 0; i < MOD_P; i++) cache[i] = -1;
  lli nb_cells = M*M - N*N;
  lli res = 1LL;
  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= M-N; j++)
      res = (res * inv(i+j-1)) % MOD_P;
  res = (res * res) % MOD_P;
  for (int i = 1; i <= M-N; i++)
    for (int j = 1; j <= M-N; j++)
      res = (res * inv(i+j-1 + 2*N)) % MOD_P;
  for (int i = 1; i <= nb_cells; i++) res = (res * i) % MOD_P;
  printf("%lli\n", res);
  return 0;
}
