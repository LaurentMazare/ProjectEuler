#include<stdio.h>
#include<stdlib.h>
#define MOD 1000000007LL
#define MAXP 50000000
typedef long long int lli;

lli *facts; // Factorial cache
lli *ifacts; // Inverse factorial cache modulo MOD

lli chooses(lli n, lli p) {
  if (n < p) return 0;
  return ((facts[n]*ifacts[p]) % MOD *ifacts[n-p]) % MOD;
}

lli pow_mod(lli x, lli n) {
  if (n == 0) return 1;
  if (n & 1) return (x * pow_mod(x, n-1)) % MOD;
  lli tmp = pow_mod(x, n/2);
  return (tmp*tmp) % MOD;
}

// Closed form for n dices with excatly m pairs:
// c(n, m) = 6*5^(n-m-1)*chooses(n-1, m)
lli c(lli n, lli m) {
  if (n <= m) return 0;
  return (6 * pow_mod(5, n-m-1) * chooses(n-1, m)) % MOD;
}


int main(int argc, char* argv[]) {
  int* is_prime = malloc((1+MAXP) * sizeof *is_prime);
  facts = malloc((1+MAXP) * sizeof *facts);
  ifacts = malloc((1+MAXP) * sizeof *ifacts);
  for (int i = 0; i <= MAXP; ++i) {
    facts[i] = i ? (i*facts[i-1]) % MOD: 1;
    ifacts[i] = pow_mod(facts[i], MOD-2); // inverse with Fermat's little theorem
  }
  for (int i = 2; i <= MAXP; i++) is_prime[i] = 1;
  for (int i = 2; i <= MAXP; i++)
    if (is_prime[i]) {
      int j = i + i;
      while (j <= MAXP) {is_prime[j] = 0; j += i;}
    }

  lli total = 6, c_i = 6;
  int pi_i = 0;
  for (int i = 2; i <= MAXP; i++) {
    lli to_add = 0;
    if (is_prime[i]) {
      pi_i++;
      to_add = 5 * c(i-1, pi_i);
    }
    else to_add = MOD - c(i-1, pi_i);
    c_i = (6 * c_i + to_add) % MOD;
    total = (total + c_i) % MOD;
  }
  printf("%lli\n", total);
  return 0;
}
