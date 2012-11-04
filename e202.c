#include "euler_math.h"

int main(int argc, char* argv) {
  llu nb = 0;
  llu m = (12017639147L + 3) / 2;
  for (llu n = (3-m%3)%3; n < m; n += 3)
    if (n % 5 != 0 && n % 11 != 0 && n % 17 != 0 &&
        n % 23 != 0 && n % 29 != 0 && n % 41 != 0 && n % 47 != 0) nb++;
  // m is only divisible by these numbers (thanks to W. Alpha) *)
  printf("%llu\n", nb);
  return 0;
}
