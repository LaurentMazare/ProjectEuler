#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX 64000000

int main(int argc, char* argv[]) {
  unsigned long long int i;
  unsigned long long int* sigma2 =(unsigned long long int*)malloc(MAX*sizeof(unsigned long long int));
  unsigned long long int sum = 0;

  for (i=1; i<MAX; i++) sigma2[i] = 0;

  for (i=1; i<MAX; i++) {
    unsigned long long int n = 0;
    unsigned long long int tmp = 0;
    unsigned long long int sqr_i = i * i;
    unsigned long long int sqrt_sigma2;
    while ((tmp = ++n * i) < MAX)
      sigma2[tmp] += sqr_i;
    sqrt_sigma2 =(long long int)(sqrt(sigma2[i])+0.1);
    if (sqrt_sigma2 * sqrt_sigma2 == sigma2[i]) sum += i;
  }
  printf("%lli\n", sum);

  return 0;
}
