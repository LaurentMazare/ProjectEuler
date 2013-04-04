#include<stdio.h>

int is_pandigital(long long int n) {
  short digits[10];
  int i;
  for(i=0;i<10;i++) digits[i]=0;
  while (n!=0) {
    digits[n%10]=1;
    n/=10;
  }
  for(i=1;i<10;i++) if(digits[i]!=1) return 0;
  return !digits[0];
}

long long int product(long long int i, int n) {
  int j;
  long long int result = 0;
  for (j=1; j<=n; j++) {
    int tmp = i * j;
    int tmp_bis = tmp;
    long long int base = 1;
    while (tmp_bis != 0) {tmp_bis /= 10; base *= 10;};
    result = result * base + tmp;
  }
  return result;
}

int main(int argc, char* argv[]) {
  int n;
  long long int largest = 0;
  for (n=2; n<10; n++) {
    int i = 1;
    long long int p;
    while ((p = product(i, n)) < 1000000000LL) {
      if (is_pandigital(p)) {
        if (p > largest) largest = p;
      }
      i++;
    }
  }
  printf("%lli\n", largest);
  return 0;
}

