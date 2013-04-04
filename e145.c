#include <stdio.h>
int is_reversible(int n) {
  int old_n = n;
  int reverse_n = 0;
  int sum;
  if (n%10==0) return 0;
  while (n != 0) {
    reverse_n *= 10;
    reverse_n += n % 10;
    n/=10;
  }
  sum = old_n+reverse_n;
  while (sum != 0) {
    if ((sum % 10) % 2 == 0) return 0;
    sum /= 10;
  }
  return 1;
}
int main(int argc, char* argv[]) {
  int i;
  int nb=0;
  for (i=1; i<1000000000; i++)
    if (is_reversible(i)) nb++;
  printf("%i\n", nb);
  return 0;
}

