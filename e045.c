#include<stdio.h>

int main(int argc, char* argv[]) {
  long long int i = 1;
  long long int j = 1;
  long long int k = 1;
  while (1) {
    long long int t = (i * (i + 1)) / 2;
    long long int p = (j * (3*j-1)) / 2;
    long long int h = (k * (2 * k - 1));
    if (t == p && p == h && t > 40755) {
      printf("%lli\n", t);
      break;
    }
    if (t <= p && t <= h) i++;
    if (p <= t && p <= h) j++;
    if (h <= t && h <= p) k++;
  }
  return 0;
}
