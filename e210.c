#include"euler_math.h"
#include<math.h>
lli sqr(lli x) { return x * x; }
lli count(lli n) {
  lli total = n * (2*n+1);
  double x0 = (double)n / 8.0;
  double y0 = x0;
  double r = x0 * sqrt(2.0);
  for (lli x_plus_y = 0; x_plus_y <= n/2; x_plus_y++) {
    double a = 2;
    double b = 2 * (y0 - x_plus_y - x0);
    double c = x0 * x0 + (y0 - x_plus_y) * (y0 - x_plus_y) - r * r;
    double delta = b*b - 4*a*c;
    double x_minf = (-b + sqrt(delta)) / (2.0 * a);
    lli x_max = (x_plus_y + n) / 2;
    lli x_min = (lli)x_minf;
    if (2*x_min <= x_plus_y) x_min = x_plus_y / 2 + 1;
    while (sqr(x_min-n/8) + sqr(x_plus_y-x_min-n/8) < 2 * sqr(n/8)) x_min++;
    total -= 2 * (1 + x_max - x_min);
  }
  return total;
}

int main(int argc, char* argv[]) {
  printf("%lli\n", count(1000000000));
  return 0;
}

