#include<stdio.h>
#include<math.h>

int is_pen(long long int l) {
  double delta = (1.0 + 24 * l);
  double n = (1 + sqrt(delta)) / 6.0;
  int nn = (int)(n + 0.1);
  if (nn * (3 * nn - 1) == 2 * l) return 1;
  return 0;
}

int main(int argc, char* argv[]) {
  int i = 1;
  long long int diff;
  while (1) {
    int k = 1;
    diff = (i * (3 * i - 1)) / 2;
    while (1) {
      long long int p_b = (k * (3 * k - 1)) / 2;
      long long int p_a = p_b + diff;
      long long int sum = p_a + p_b;
      if (is_pen(p_a) && is_pen(sum) ) {
        printf("%lli\n", diff);
        return 0;
      }
      k++;
      if (k > 10000) break;
    }
    i++;
    if (i > 10000) break;
  }
  return 0;
}
