#include <stdio.h>
#define SIZE 10000
void cube_digits(int n, int* digits) {
  int i;
  long long n3 = n;
  n3 = n3 * n3 * n3;
  for (i=0; i<10; i++) digits[i]=0;
  while (n3!=0) {
    digits[n3%10]++;
    n3/=10;
  }
}
int compare_digits(int *d1, int *d2) {
  int i;
  for (i=0; i<10; i++) {if (d1[i]!=d2[i]) return 0;}
  return 1;
}

int main(int argc, char* argv[]) {
  int i;
  int digits[SIZE][10];
  for (i=0; i<SIZE; i++) cube_digits(i,digits[i]);
  for (i=0; i<SIZE; i++) {
    int j;
    int nb = 0;
    for (j=i+1; j<SIZE; j++)
      if (compare_digits(digits[i], digits[j])) {nb++;}
    if (nb>=4) {
      long long i3 = i;
      i3 = i3 * i3 * i3;
      printf("%lli\n", i3);
      return 0;
    }
  }
  return 0;
}
