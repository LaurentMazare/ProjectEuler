#include<stdio.h>
#include<stdlib.h>
#define MAX 1000000
int main(int argc, char*argv[]) {
  int sum = 0;
  char* is_prime = (char*)malloc(MAX*sizeof(char*));
  int i;
  is_prime[0] = is_prime[1] = 0;
  for (i=2; i<MAX; i++) is_prime[i] = 1;
  for (i=2; i<MAX; i++) {
    int j = 1;
    int tmp;
    while ((tmp = ++j * i) < MAX) is_prime[tmp] = 0;
  }

  for (i=11; i<MAX; i++) {
    int tmp1 = i;
    int tmp2 = i;
    while (is_prime[tmp1]) {
      tmp1/=10;
    }
    while (is_prime[tmp2]) {
      int tmp3 = tmp2;
      int fact = 1;
      while ( (tmp3 /= 10) != 0) fact *= 10;
      tmp2 = tmp2 % fact;
    }
    if (tmp1 == 0 && tmp2 == 0) sum += i; 

  }
  printf("%i\n", sum);

  return 0;
}
