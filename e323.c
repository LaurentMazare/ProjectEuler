#include<stdio.h>
#include<math.h>

#define MAX_N 32

double fact(int n) {
  double res = 1;
  int i;
  for(i = 1; i <= n; i++)
    res *= (double)i;
  return res;
}
double comb(int k, int n) {
  double r = fact(n)/(fact(k) * fact(n-k));
  return r;
}

int main(int argc, char* argv[]) {
  int i;
  double e[MAX_N + 1];
  e[0] = 0;
  for(i = 1; i <= MAX_N; i++) {
    int j;
    double p = pow(2, i);
    double sum_comb = 0;
    for(j = 0; j < i; j++)
      sum_comb += e[j] * comb(j, i) / p;
    e[i] = (1 + sum_comb) / (1 - 1 / p);
  }
  printf("%.10f\n", e[MAX_N]);
  return 0;
}
