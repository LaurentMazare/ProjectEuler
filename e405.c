#include<stdio.h>
#define MOD_P 410338673
typedef long long int lli;
lli pow_mod(lli x, lli n, lli mod) {
  if (n == 0) return 1;
  if (n % 2 == 0) {x = pow_mod(x, n/2, mod); return (x*x) % mod;}
  return (x * pow_mod(x, n-1, mod)) % mod;
}

int main(int argc, char* argv[]) {
  int n = 2;
  int u = 2;
  int v = 8;
  int freq = MOD_P / 17 * 8;
  int mod = pow_mod(10, 1000000000000000000LL, freq);
  while (1) {
    n++;
    u = (4*u + v) % MOD_P;
    v = (2*v + 3 + (n % 2 == 0 ? 1: -1)) % MOD_P;
    if (n == mod) {printf("%d: %d\n", n, u); break;}
  }
  return 0;
}
