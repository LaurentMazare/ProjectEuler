#include<stdio.h>
#include<stdlib.h>

#define MAX 10000000
#define BASE 1234567891011LL
#define F10_14_P1 199461219007LL
#define F10_14 921144120792LL

#define MAXL 4000000

int main(int argc, char* argv[]) {
  int i;
  char* p = (char*)malloc(MAX*sizeof(char));
  char* np = (char*)malloc(MAX*sizeof(char));
  
  long long int base = 10000000;
  long long int res = 0;
  long long int* fib;
  int nb = 0;
  base = base * base;
  for(i=2; i<MAX; i++) p[i] = 1;
  for(i=2; i<MAX; i++) {
    int j = 1;
    int tmp;
    while((tmp = ++j * i) < MAX) p[tmp]=0;
  }
  for(i=2; i<MAX; i++) if (p[i]) nb++;
  // special sieve starting from 10^14 using p 

  for(i=2; i<MAX; i++) np[i]=1;
  for(i=2; i<MAX; i++)
    if (p[i]) {
      long long int j = base / i;
      long long int tmp;
      while ((tmp = ++j * i - base) < MAX) np[tmp]=0;
    }

  fib = (long long int*)malloc(MAXL*sizeof(long long int));
  for(i=0; i<MAXL; i++) {
    if (i==0)
      fib[i] = F10_14;
    else if (i == 1)
      fib[i] = F10_14_P1;
    else
      fib[i]=(fib[i-1]+fib[i-2])%BASE;
  }
  nb = 0;
  for(i=0; i<MAX; i++)
    if (np[i]) {
      res = (res + fib[i]) % BASE;
      nb++;
      if (nb == 100000)
        break;
  }
  printf("%lli\n", res);
  return 0;
}
