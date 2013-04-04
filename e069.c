#include<stdio.h>

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

#define MAXF 1000000
int main(int argc, char* argv[]) {
  int i;
  double max_fi=0;
  int where_max=-1;
  for(i=2;i<=MAXF;i++) {
    int f = fi(i);
    double n_fi=i*1.0/f;
    if (n_fi>max_fi) {max_fi=n_fi; where_max=i;}
  }
  printf("%i\n", where_max);
  return 0;
}
