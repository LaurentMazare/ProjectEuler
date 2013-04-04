#include<stdio.h>
#define BASE 100000000LL

long long exp_mod(int n, int base) {
  long long l = 1;
  long long period = 0;
  long long n_bis;
  int i;
  if (n==0) return 1;
  if (base==1) return 0;
  while (1) {
    l = (l * 1777LL) % base;
    period++;
    if (l == 1) break;
  }
  n_bis = exp_mod(n-1, period);
  l=1;
  for (i=0; i<n_bis; i++)
    l = (l * 1777LL) % base;
  return l;
}


int main(int argc, char* argv[]) {
  printf("%lli\n", exp_mod(1855, BASE));
  return 0;
}
