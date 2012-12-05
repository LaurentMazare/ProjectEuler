#include "euler_math.h"
#define MOD_P 982451653
#define MAX_P 15000000
#define UP_TO 100000000000000LL

// Use Fermat's little theorem to compute the inverse
lli pow_mod(lli x, lli n) {
  if (n == 0) return 1;
  if (n % 2 == 0) {x = pow_mod(x, n/2); return (x*x) % MOD_P;}
  return (x * pow_mod(x, n-1)) % MOD_P;
}

int main(int argc, char* argv[]) {
  lli* fact = malloc(MAX_P * sizeof *fact);
  lli* sum_inv = malloc(MAX_P * sizeof *sum_inv);
  for (int i = 0; i < MAX_P; i++)
    if (i == 0) {fact[i] = 1; sum_inv[0] = 0;}
    else {
      fact[i] = (fact[i-1] * i) % MOD_P;
      sum_inv[i] = (pow_mod(i, MOD_P-2) + sum_inv[i-1]) % MOD_P;
    }
  lli total = 0;
  lli m;
  for (m = 1; ((m+1) * (m+2)) / 2 <= UP_TO; m++) {
    lli tmp = fact[m+1]*m + fact[m]*((((m+2)*(m-1)) / 2)%MOD_P)+fact[m+1]*(((m-1)*(sum_inv[m]-1))%MOD_P); 
    total = (tmp + total) % MOD_P;
  }
  lli tm = ((m+1)*m) / 2;
  lli l = UP_TO - tm;
  lli common = (fact[m+1] * (m-1)) % MOD_P;
  total = (total + common * (MOD_P+sum_inv[m]-sum_inv[m-l-1])) % MOD_P;
  printf("Total: %lli\n", total+1);
  return 0;
}
