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


#define MAX 1000000
int main(int argc, char* argv[]) {
  int n;
  long long sum=0;
  for (n=2;n<=MAX;n++) {
    sum+=fi(n);
  }
  printf("%lli\n", sum);
  return 0;
} 
