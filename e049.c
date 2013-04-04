#include <stdio.h>

int is_prime(int i) {
  int j = 0;
  for (j = 2; j * j <= i; j++) {
    if (i % j == 0) return 0;
  }
  return 1;
}
int perm(int n1, int n2) {
  int digits1[10];
  int digits2[10];
  int n;
  for (n=0;n<10;n++) {
    digits1[n] = digits2[n] = 0;
  }
  while (n1 != 0) {digits1[n1%10]++; n1/=10;}
  while (n2 != 0) {digits2[n2%10]++; n2/=10;}
  for (n=0;n<10;n++)
    if (digits1[n]!=digits2[n]) return 0;
  return 1;
}

int main(int argc, char* argv[]) {
  int primes[10000];
  int n, k;
  for (n = 1000; n < 10000; n++) primes[n]=is_prime(n);
  for (n = 1000; n < 10000; n++)
    if (primes[n])
      for (k = 2; k < 5000; k++) {
        int n1 = n + k;
        int n2 = n + k*2;
        if (n2>=10000) break;
        if (primes[n1] && primes[n2] && perm(n, n1) && perm(n, n2)) {
          printf("%i%i%i\n", n, n1, n2);
        }
      }
  return 0;
}

