#include <stdio.h>

int* chain_length;

int phi(int n) 
{ 
  int result = n; 
  for(int i=2;i*i <= n;i++) 
  { 
    if (n % i == 0) result -= result / i; 
    while (n % i == 0) n /= i; 
    if (i!=2) i++;
  } 
  if (n > 1) result -= result / n; 
  return result;
}

int main(int argc, char* argv[]) {
  int last = 0;
  double min = 1;
  for (int i = 330; i < 1000000000; i+=330) {
    double v = ((double)phi(i))/(i-1);
    if (v < min) {
      min = v;
      last = i;
    }
  }
  printf("%i\n", last);
  return 0;
}
