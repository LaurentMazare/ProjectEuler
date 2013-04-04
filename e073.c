#include <stdio.h>

int fi(int n) 
{ 
  int result = n; 
  int i;
  for(i=2;i*i <= n;i++) 
  { 
    if (n % i == 0) result -= result / i; 
    while (n % i == 0) n /= i; 
    if (i!=2) i++;
  } 
  if (n > 1) result -= result / n; 
  return result;
}
int gcd(int a, int b) {
  while (b!=0) {
    int t = b;
    b = a % b;
    a = t;
  }
  return a;
}

#define MAXF 12000
int main(int argc, char* argv[]) {
  int n;
  long long sum=0;
  for(n=2;n<=MAXF;n++) {
    int d=1+n/3;
    while(d*2<=n) {
      if (gcd(d,n)==1) sum++;
      d++;
    }
  }
  printf("%lli\n",sum-1);
  return 0;
}
