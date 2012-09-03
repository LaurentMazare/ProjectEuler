#include "euler_math.h"
#define MAXL 100000000
#define MAXF 50

int max_antichain(int* factors, int nb_factors, int k) {
  if (nb_factors <= 1) return k <= factors[0];
  int res = 0;
  int m = factors[nb_factors-1] > k ? k: factors[nb_factors-1];
  for (int i = 0; i <= m; i++) {
    int tmp = max_antichain(factors, nb_factors-1, k-i);
    res += tmp;
  }
  return res;
}

int main(int argc, char* argv[]) {
  int* afactors = (int*)malloc((MAXL+1) * sizeof(int));
  lli sum = 1; // For i = 1
  for (int i = 0; i <= MAXL; i++) afactors[i] = 0;
  for (int nn = 2; nn <= MAXL; nn++) {
    if (afactors[nn]==0) {
      int tmp, k = 1;
      while ((tmp = k++ * nn) <= MAXL) afactors[tmp] = nn;
    }
    int n = nn;
    int factors[MAXF];
    int nb_factors = 0;
    int sum_i = 0;
    while (n != 1) {
      int i = 0;
      int tmp = afactors[n];
      while (n % tmp == 0) {
        n /= tmp;
        i += 1;
      }
      factors[nb_factors++] = i;
      sum_i += i;
    }
    int m = max_antichain(factors, nb_factors, sum_i / 2);
    if (nn < 100) {
      printf("%d %d\n", nn, m);
    }
    sum += m;
  }
  printf("%lli\n", sum);
  return 0;
}
