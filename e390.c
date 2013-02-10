// Using Heron's formula, we get that the possible areas a
// satisfy a^2 = b^2+c^2+4b^2c^2 for 1 <= b < c
// Solve this iteratively on b using gcc __int128
#include <stdio.h>
#include <math.h>
#define MAX_A 10000000000LL
typedef unsigned long long int llu;
// Bisection
__int128 sqrt_llu(__int128 x, __int128 lo, __int128 hi) {
  if (lo < 0) lo = 1;
  while (hi > lo + 1) {
    __int128 mid = (lo+hi) / 2;
    if (mid * mid > x) hi = mid;
    else lo = mid;
  }
  if (lo * lo == x) return lo;
  if (hi * hi == x) return hi;
  return 0;
}

// Newton method on integers
__int128 sqrt_(__int128 n, __int128 x) {
  __int128 prev_x = 0;
  while (prev_x != x) {
    x = (x + n / x) / 2;
    prev_x = x;
  }
  if (x*x == n) return x;
  else return 0;
}

int main(int argc, char* argv[]) {
  __int128 total = 0;
  __int128 bmax = sqrt(MAX_A/2) + 1;
  for (__int128 b = 1; b <= bmax; b++) {
    __int128 b2 = b * b;
    printf("%llu %llu\n", (llu)b, (llu)total);
    for (__int128 c = b+1;; c++) {
      __int128 c2 = c * c;
      __int128 a2 = b2 + c2 + 4*b2*c2;
      double a_d = sqrt(a2);
      if (a_d > MAX_A) break;
//      __int128 a = sqrt_llu(a2, (__int128)a_d - 1000, (__int128)a_d + 1000);
      __int128 a = sqrt_(a2, sqrt(a2));
      if (a > 0) {
//        printf("%llu %llu %llu\n", (llu)b, (llu)c, (llu)a);
        total += a;
      }
    }
  }
  printf("%llu\n", (llu)total);
  return 0;
}
