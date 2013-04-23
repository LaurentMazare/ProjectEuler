// We obtain the conditions:
// AB^2 + AD^2 = 2.(AO^2 + BO^2) = (AO+BO)^2 + (BO-AO)^2
// BC^2 + CD^2 = 2.(AO^2 + BO^2)
// Iterate over the possible values for AO^2 + BO^2
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define N 10000000000LL
#define MAX_P 100000000
typedef long long int lli;

int* factors;
int nb_primes;
int* primes;

// Sum of square function as described in:
// http://mathworld.wolfram.com/SumofSquaresFunction.html
int sum_squares(lli n) {
  int res = 1, nb2 = 1;
  while (!(n&1)) { n /= 2; ++nb2; }
  if (n % 4 == 3) return 0;
  for (int idx = 1; idx < nb_primes; ++idx) {
    lli p = primes[idx];
    if (n < MAX_P || n < p*p) break;
    int nb_p = 0;
    while (n % p == 0) { n /= p; ++nb_p; }
    if (p % 4 == 3 && (nb_p&1)) return 0;
    if (p % 4 == 1) res *= (nb_p + 1);
  }
  if (n != 1) {
    if (n < MAX_P) {
      while (n != 1) {
        int p = factors[n], nb_p = 0;
        while (n % p == 0) { n /= p; ++nb_p; }
        if (p % 4 == 3 && (nb_p&1)) return 0;
        if (p % 4 == 1) res *= (nb_p + 1);
      }
    }
    else {
      if (n % 4 == 3) return 0;
      else res *= 2;
    }
  }
  if (res & 1) res = (res - ((nb2&1)?-1:1)) / 2;
  else res /= 2;
  return res;
}

int main(int argc, char* argv[]) {
  factors = malloc(sizeof *factors * MAX_P);
  nb_primes = 0;
  for (int i = 0; i < MAX_P; ++i) factors[i] = i;
  for (int i = 2; i < MAX_P; ++i)
    if (factors[i] == i) {
      nb_primes++;
      int j = i+i;
      while (j < MAX_P) {factors[j] = i; j += i;}
    }
  primes = malloc(sizeof *primes * nb_primes);
  nb_primes = 0;
  for (int i = 2; i < MAX_P; ++i)
    if (factors[i] == i) primes[nb_primes++] = i;
  lli total = 0;
  for (lli a2_b2 = 1; a2_b2 <= N/4; ++a2_b2) {
    lli ll = sum_squares(2*a2_b2);
    if (!ll) continue;
    total += (ll * (ll-1) * (ll-2)) / 6;
  }
  printf("%lli\n", total);
}
