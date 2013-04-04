#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[]) {
  double min = 1;
  int where_min = 0;
  int where_d = 0;
  int d;
  for (d=2; d<1000000; d++) {
    double frac;
    double n = floor(3.0 * d / 7.0);
    if (d % 7 != 0) {
    frac = 0 - n / d;
    if (frac < min - 1e-15) {
      min = frac;
      where_min = d;
      where_d = n;
    }
    }
  }
  printf("%i\n", where_d);
  return 0;
}

