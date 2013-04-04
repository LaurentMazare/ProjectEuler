#include <stdio.h>
long long base;

long long two_pow(long long y) {
  long long result = 1;
  while (y--) result = (result * 2) % base;
  return result;
}
int main(int argc, char *argv[]) {
  //28433*2^7830457+1
  long long x;
  base = 10000000000LL;
  x = (two_pow(7830457) * 28433 + 1) % base;
  printf("%lli\n", x);
  return 0;
}
