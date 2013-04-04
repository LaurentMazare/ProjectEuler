#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int is_prime(int i) {
  int ok = 1;
  int j = 0;
  int n = (int)sqrt(i);
  for (j = 2; j <= n; j++) {
    if (i % j == 0) ok = 0;
  }
  return ok;
}

#define SIZE 50000000
int main(int argc, char* argv[]) {
  int* cache = (int*)malloc(sizeof(int)*SIZE);
  int primes[7500];
  int i, j, k;
  int nb = 0;
  for (i=2; i<7500; i++) primes[i]=is_prime(i);
  for (i=2; i<SIZE; i++) cache[i]=0;
  for (i=2; i<7500; i++)
    if (primes[i])
    for (j=2; j<500; j++)
    if (primes[j])
      for (k=2; k<100; k++)
      if (primes[k]) {
        long long s = i*i + j*j*j + k*k*k*k;
        if (s < SIZE) cache[s]=1;
      }
  for (i=2; i<SIZE; i++) if (1 == cache[i]) nb++;
  printf("%i\n", nb);
  return 0;
}
