#include <stdio.h>
double fact(int i) {
  double res = 1;
  while (i != 1) {
    res *= i--;
  }
  return res;
}

double comb(int n, int r) {
  return fact(n)/(fact(r)*fact(n-r));
}

int main(int argc, char* argv[]) {
  int res=0;
  int i, n;
  for (n=1; n<=100; n++) {
  for (i=1; i<n; i++) {
    double c = comb(n, i);
    if (c>=1000000) {
      res++;
    }
  }
  }
  printf("%i\n", res);

  return 0;
}
