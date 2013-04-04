#include<stdio.h>
#include<stdlib.h>
#define MAXP 100000

typedef long long int lli;

int nb_primes;
char* is_prime;
int* primes;

int isp(lli l) {
  if (l < MAXP) return is_prime[l];
  for (int i = 0; i < nb_primes; i++) {
    lli p = primes[i];
    if (p * p > l) return 1;
    if (l % p == 0) return 0;
  }
  return 1;
}

lli s(int remaining_digits, int nb_digits, int digit, lli prefix) {
  if(nb_digits > remaining_digits) return 0;
  if (remaining_digits == 0) {
    if (nb_digits == 0 && isp(prefix)) {
      return prefix;
    }
    return 0;
  }
  lli result = 0;
  int start_from = 0;
  if (prefix == 0) start_from = 1;
  for (int x = start_from; x <= 9; x++)
    if (x == digit)
      result += s(remaining_digits-1, nb_digits-1, digit, prefix * 10 + x);
    else
      result += s(remaining_digits-1, nb_digits, digit, prefix * 10 + x);
  return result;
}

int main(int argc, char* argv[]) {
  is_prime = (char*)malloc(sizeof(char)*MAXP);
  nb_primes = 0;
  for (int i = 2; i < MAXP; i++) is_prime[i] = 1;
  for (int i = 2; i < MAXP; i++)
    if (is_prime[i]) {
      int index, j = 1;
      while ((index = ++j * i) < MAXP) is_prime[index] = 0;
      nb_primes++;
    }
  primes = (int*)malloc(sizeof(int)*nb_primes);
  nb_primes = 0;
  for (int i = 2; i < MAXP; i++) if (is_prime[i]) primes[nb_primes++] = i;
  
  lli result = 0;
  int truc = 10;
  for (int i = 0; i <= 9; i++) {
    lli tmp = 0;
    int k = truc;
    while (1) {
      if ((tmp = s(truc, --k, i, 0)) != 0) break;
    }
    result += tmp;
  }
  printf("%lli\n", result);

  return 0;
}
