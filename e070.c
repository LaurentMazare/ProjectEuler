#include <stdio.h>

int phi(int n) 
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

int is_perm(int x, int y) {
  int digits[10];
  int i;
  for(i=0; i<10; i++) digits[i]=0;
  while (x!=0) {digits[x%10]++; x/=10;}
  while (y!=0) {digits[y%10]--; y/=10;}
  for(i=0; i<10; i++) if (digits[i]!=0) return 0;
  return 1;
}

int main(int argc, char* argv[]) {
  int n;
  double min_ratio = 2;
  int where = 0;
  for (n=2; n<10000000; n++) {
    int p = phi(n);
    if (is_perm(p, n) && ((n * 1.0) / p < min_ratio)) {
      min_ratio = (n*1.0) / p;
      where = n;
    }
  }
  printf("%i\n", where);
  return 0;
}
