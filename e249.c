#include<stdio.h>
#include<stdlib.h>

#define PRIMES 4999
#define MOD 10000000000000000ULL

typedef unsigned long long int ull;

int main(int argc, char* argv[]) {
  char* is_prime = (char*)malloc(sizeof(char)*(PRIMES+1));
  int nb_primes = 0;
  int sum_primes = 0;
  for(int i = 2; i <= PRIMES; i++) is_prime[i] = 1;
  for(int i = 2; i <= PRIMES; i++)
    if (is_prime[i]) {
      nb_primes++;
      sum_primes += i;
      int j = 1;
      int index;
      while ( (index = ++j * i) <= PRIMES ) is_prime[index] = 0;
    }
  int* primes = (int*)malloc(nb_primes * sizeof(int));
  nb_primes = 0;
  for(int i = 2; i <= PRIMES; i++)
    if (is_prime[i])
      primes[nb_primes++] = i;

  free(is_prime);
  sum_primes += 10;
  is_prime = (char*)malloc(sum_primes * sizeof(char));
  for(int i = 2; i < sum_primes; i++) is_prime[i] = 1;
  for(int i = 2; i < sum_primes; i++)
    if (is_prime[i]) {
      int j = 1;
      int index;
      while ( (index = ++j * i) < sum_primes ) is_prime[index] = 0;
    }

  ull* nb_subsets = (ull *)malloc(sizeof(ull) * sum_primes);
  ull* tmp = (ull *)malloc(sizeof(ull) * sum_primes);
  for(int i = 0; i < sum_primes; i++) nb_subsets[i] = 0;

  for(int i = 0; i < nb_primes; i++) {
    int p = primes[i];
    for(int j = 0; j < sum_primes; j++) tmp[j] = nb_subsets[j];
    for(int j = 0; j < sum_primes - p - 1; j++)
      nb_subsets[j+p] = (tmp[j+p] + tmp[j]) % MOD;
    nb_subsets[p] = (nb_subsets[p] + 1) % MOD;
  }
  ull sum = 0;
  for(int i = 2; i < sum_primes; i++)
    if (is_prime[i]) sum = (sum + nb_subsets[i]) % MOD;
  printf("%llu\n", sum);
  return 0;
}
