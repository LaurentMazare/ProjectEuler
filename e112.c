#include <stdio.h>
int is_decreasing(int n) {
  int last_digit = n % 10;
  n /= 10;
  while (n != 0) {
    if (last_digit > n % 10) return 0;
    last_digit = n % 10;
    n /= 10;
  }
  return 1;
}

int is_increasing(int n) {
  int last_digit = n % 10;
  n /= 10;
  while (n != 0) {
    if (last_digit < n % 10) return 0;
    last_digit = n % 10;
    n /= 10;
  }
  return 1;
}

int is_bouncy(int n) {
  return !is_increasing(n) && !is_decreasing(n);
}

int main(int argc, char* argv[]) {
  int nb_bouncy = 0;
  int nb = 0;
  int n = 0;
  do {
    if (is_bouncy(++n)) nb_bouncy++;
    nb++;
  }
  while (nb_bouncy * 100 != nb * 99);
  printf("%i\n", n);

  return 0;
}
