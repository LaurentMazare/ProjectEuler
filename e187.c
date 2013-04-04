#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX 50000000
int main(int argc, char* argv[]) {
  char* is_prime = (char*)malloc((MAX+1)*sizeof(char));
  int* sum_prime = (int*)malloc((MAX+1)*sizeof(int));
  int i;
  int nb_primes = 0;
  int result = 0;
  for (i = 2; i <= MAX; i++) is_prime[i] = 1;
  for (i = 2; i <= MAX; i++) {
    int j = 1;
    int tmp;
    while ((tmp = ++j * i) <= MAX) is_prime[tmp] = 0;
  }
  for (i = 2; i <= MAX; i++) if (is_prime[i]) nb_primes++;

  sum_prime[1]=0;
  for (i = 2; i <= MAX; i++)
    sum_prime[i] = is_prime[i]+sum_prime[i-1];

  for (i = 2; i <= sqrt(2*MAX); i++)
    if (is_prime[i]) {
      result += sum_prime[(2*MAX)/i] - sum_prime[i] + 1;
    }
  printf("%i\n", result);
  return 0;
}
