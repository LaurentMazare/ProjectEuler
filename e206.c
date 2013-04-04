#include <stdio.h>

int is_ok(unsigned int x) {
  long long l = x;
  l = l * l;
  if (l % 10 != 0) return 0;
  l /= 100;
  if (l % 10 != 9) return 0;
  l /= 100;
  if (l % 10 != 8) return 0;
  l /= 100;
  if (l % 10 != 7) return 0;
  l /= 100;
  if (l % 10 != 6) return 0;
  l /= 100;
  if (l % 10 != 5) return 0;
  l /= 100;
  if (l % 10 != 4) return 0;
  l /= 100;
  if (l % 10 != 3) return 0;
  l /= 100;
  if (l % 10 != 2) return 0;
  l /= 100;
  if (l % 10 != 1) return 0;
  l = x;
  l = l * l;
  printf("%d\n", x);
  return 1;
}

int main(int argc, char *argv[]) {
  unsigned int n = 1000000010;
  unsigned int bound = 4 * n;
  while (n < bound) {
    n += 20;
    if (is_ok(n)) return 0;
  }

  return 0;
}
