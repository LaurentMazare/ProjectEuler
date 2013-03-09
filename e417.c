#include<stdio.h>
#include<stdlib.h>
#define MAXP 100000000
#define MIN(X,Y) ((X) < (Y) ? (X): (Y))
typedef long long int lli;

int* factors;

int phi(int n) {
  int res = 1;
  while (n != 1) {
    int p = factors[n];
    res *= p - 1;
    n /= p;
    while (n % p == 0) {
      n /= p;
      res *= p;
    }
  }
  return res;
}

lli pow_mod(lli x, int n, int m) {
  if (n == 0) return 1;
  if (n&1) return (x * pow_mod(x, n-1, m)) % m;
  lli p = pow_mod(x, n/2, m);
  return (p*p) % m;
}

void all_divs(int x, int div, int* divs, int* nb_divs) {
  if (x == 1) {divs[*nb_divs] = div; (*nb_divs)++;}
  if (1 < x) {
    int p = factors[x];
    int nb_p = 0;
    while (x % p == 0) {x /= p; nb_p++;}
    for (int i = 0; i <= nb_p; i++) {
      all_divs(x, div, divs, nb_divs);
      div *= p;
    }
  }
}

int sort_int(const void *x, const void *y) {
  const int a = *(int*)x;
  const int b = *(int*)y;
  if (a > b)
    return 1;
  else
    return (a < b) ? -1: 0;
}

int main(int argc, char* argv[]) {
  factors = malloc((1+MAXP) * sizeof *factors);
  for (int i = 2; i <= MAXP; i++) factors[i] = i;
  for (int i = 2; i <= MAXP; i++)
    if (factors[i] == i) {
      int j = i + i;
      while (j <= MAXP) {factors[j] = i; j += i;}
    }
  lli total = 0;
  int divs[10000];
  for (int n = 3; n <= MAXP; n++) {
    if (n % 100000 == 0) printf("%d\n", n / 100000);
    int nn = n;
    int nb_divs = 0;
    while (nn % 2 == 0) nn /= 2;
    while (nn % 5 == 0) nn /= 5;
    if (nn == 1) continue;
    int ph = phi(nn);
    all_divs(ph, 1, divs, &nb_divs);
    qsort(divs, nb_divs, sizeof(int), sort_int);
    for (int i = 0; i < nb_divs; i++) {
      int div = divs[i];
      if (pow_mod(10, div, nn) == 1) {
        total += div;
        break;
      }
    }
  }
  printf("%lli\n", total);
  return 0;
}
