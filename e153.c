#include "euler_math.h"
#define LIM 100000000

int main(int argc, char* argv[]) {
  llu total = 0;
  for (int x = 1; x <= LIM; x++) {
    llu x2 = (llu)x * (llu)x;
    total += x * (LIM / x);
    for (int y = 1;; y++) {
      if (1 != gcd_int(x, y)) continue;
      llu rho = x2 + (llu)y * (llu)y;
      if (rho > LIM) break;
      int mult = 0;
      while (++mult * rho <= LIM)
        total += 2 * x * mult * (LIM / (mult*rho));
    }
  }
  printf("%llu\n", total);
  return 0;
}
