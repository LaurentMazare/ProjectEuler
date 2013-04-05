#include<stdio.h>
#include<stdlib.h>
#define MAX 1100000
#define BOUND 999966663333LL

int main(int argc, char* argv[]) {
  long long int i, idx;
  char* primes = (char*)malloc(MAX*sizeof(char));
  int* p = (int*)malloc(MAX*sizeof(char));
  int nb_p = 0;
  long long int result = 0;
  for (i=2; i<MAX; i++) primes[i] = 1;
  for (i=2; i<MAX; i++) {
    int j = 1;
    int tmp;
    while ((tmp = ++j * i) < MAX) primes[tmp] = 0;
  }
  for (i=2; i<MAX; i++)
    if (primes[i])
      p[nb_p++] = i;

  idx = 0;
  while (1) {
    long long int x = p[idx];
    long long int next = p[idx+1];
    for(i=next-1; i * next > x * x; i--) {
      if( i * next < BOUND && i % x != 0) result += i*next;
    }
    for(i=x+1; i * x <next * next; i++) {
      if( i * x < BOUND && i % next != 0) result += i*x;
    }
    idx++;
    if (next * next > BOUND)
      break;
  }
  printf("%lli\n", result);
  return 0;
}
