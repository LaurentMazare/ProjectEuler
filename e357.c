#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#define MAX_N 100000000

int main(int argc, char* argv[]) {
  char* primes = (char*)malloc(MAX_N*sizeof(char));
  long long int sum = 1;
  int i, nb = 0;
  for(i=2; i<MAX_N; i++)
    primes[i] = 1;
  for(i=2; i<MAX_N; i++) {
    int j = 1;
    int tmp;
    if (primes[i]) nb++;
    while ((tmp = ++j * i) < MAX_N) primes[tmp]=0;
  }
  for(i=2; i<MAX_N-1; i+=4) 
    if(primes[i+1] && i % 9 != 0 && i % 25 != 0) {
      int ok = 1;
      int j;
      int n = (int)sqrt(i);
      for(j=2; j<n; j++)
        if(i % j == 0 && !primes[j + i / j]) {
          ok = 0;
          break;
        }
      if(ok) sum += i;
  }
  printf("%lli\n", sum);
  free(primes);
  return 0;
}
