#include<stdio.h>

int gcd(int a, int b) {
  while (b != 0) {
    int t = b;
    b = a % b;
    a = t;
  }
  return a;
}

int main(int argc, char* argv[]) {
  int p = 1009;
  int q = 3643;
  int n = p * q;
  int phi = (p-1) * (q-1);
  int nb = 0;
  int min_unconcealed = n;
  long long int sum = 0;
  for (int e = 2; e < phi; e++) {
    if (1 == gcd(e, phi)) {
      int unconcealed = (gcd(e-1, p-1) + 1) * (gcd(e-1, q-1) + 1);
      if (unconcealed < min_unconcealed) {
        nb = sum = 0;
        min_unconcealed = unconcealed;
      }
      if (unconcealed == min_unconcealed) {
        nb++;
        sum += e;
      }
    }
  }
  printf("%lli\n", sum);
  return 0;
}
