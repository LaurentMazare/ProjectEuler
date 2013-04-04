#include <stdio.h>
int is_pal(int* x) {
  int i, l = 0;
  int is_ok = 1;
  i = 0;
  while (x[i++] != -1) {
    l++;
  }
  for (i=0; i<l; i++) {
    if (x[i]!=x[l-i-1]) is_ok = 0;
  }
  return is_ok;
}

void basis(int* x, int basis, int n) {
  int i = 0;
  while (n!=0) {
    x[i++] = n % basis;
    n /= basis;
    x[i];
  }
  x[i]=-1;
}

int is_ok(int i) {
  int basis10[11];
  int basis2[21];
  int j;
  basis(basis2, 2, i);
  basis(basis10, 10, i);
  for (j=0; j<21; j++) {
    if (basis2[j]==-1) break;
  }
  return is_pal(basis2) && is_pal(basis10);
}

int main(int argc, char* argv) {
  int i;
  long long sum = 0;
  for (i=0; i<1000000; i++) {
    if (is_ok(i)) sum += i;
  }
  printf("%lli\n", sum);
  return 0;
}

