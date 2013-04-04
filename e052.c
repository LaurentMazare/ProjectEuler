#include <stdio.h>

void get_digits(int n, int* digits) {
  int i;
  for (i = 0; i < 10; i++) digits[i]=0;
  while (n != 0) {
    digits[n%10]++;
    n/=10;
  }
}

int compare_digits(int *d1, int *d2) {
  int i;
  int ok=1;
  for (i=0; i<10; i++) {
    ok = ok && (d1[i] == d2[i]);
  }
  return ok;
}

int is_ok(int n) {
  int digits[10];
  int digits2[10];
  get_digits(n, digits);
  get_digits(n*2, digits2);
  if (!compare_digits(digits, digits2)) return 0;
  get_digits(n*3, digits2);
  if (!compare_digits(digits, digits2)) return 0;
  get_digits(n*4, digits2);
  if (!compare_digits(digits, digits2)) return 0;
  get_digits(n*5, digits2);
  if (!compare_digits(digits, digits2)) return 0;
  get_digits(n*6, digits2);
  if (!compare_digits(digits, digits2)) return 0;
  return 1;
}

int main(int argc, char* argv[]) {
  int res = 0;
  while (!is_ok(++res)) {
  }
  printf("%i\n", res);
  return 0;
}
