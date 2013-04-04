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

#define SIZE 1000000
int main(int argc, char* argv[]) {
  int i, j, sum;
  int max_primes=0;
  int where_max=0;
  int* prime = (int*)malloc(SIZE*sizeof(int));
  for (i=2; i<SIZE; i++) prime[i]=is_prime(i);
  i=2;
  while (i < SIZE) {
    if (prime[i]) {
      int nb_primes=1;
      sum = i;
      j = i+1;
      while (j < SIZE) {
        if (prime[j]) {
          nb_primes++;
          sum+=j;
          if (SIZE <= sum) break;
          if (prime[sum] && max_primes<nb_primes) {
            max_primes=nb_primes;
            where_max=sum;
          }
        }
        j++;
      }
    }
    i++;
  }
  printf("%i\n", where_max);
  return 0;
}
