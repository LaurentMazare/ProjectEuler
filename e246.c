// Very brute force solution:
// Consider an ellipsis of equation a.x^2 + b.y^2 = 1.
// Tangents on point x0, y0 have eq a.x.x0 + b.y.y0 = 1
// Knowing that a.x0^2+b.y0^2 = 1, we obtain:
// a.e.x0^2 - 2.a.x.x0 + 1 - b.y^2 = 0 with e = a.x^2+b.y^2
// So we have two solutions for x0, xr and xs, given by:
// (2.a.x +/- 2.y.sqrt(a.b.(e-1))) / (2.a.e)
// yr and ys can easily be obtained (with a special case for y=0).
// Moreover, cos(Theta) = (PR^2+PS^2-RS^2)/(2.PR.PS)
// With PR^2 = (x-xr)^2 + (y-yr)^2
//      PS^2 = (x-xs)^2 + (y-ys)^2
//      RS^2 = (xr-xs)^2 + (yr-ys)^2
// And the condition Theta > 45deg is equivalent to cos(Theta)<0.5.
//
// It should be possible to optimize by following the contour instead
// of scanning the whole area.
#include<stdio.h>
#include<math.h>
double sqr(double x) {return x*x;}

int main(int argc, char* argv[]) {
  int total = 0;
  double a = 1.0 / (7500.0*7500.0);
  double b = 1.0 / (2500.0*2500.0*5.0);
  for (int x = 0; x <= 20000; x++) {
    double ax = a * x;
    for (int y = 0; y <= 20000; y++) {
      double by = b * y;
      double e = ax*x+by*y;
      if (e < 1) continue;
      double num2 = y*sqrt(a*b*(e-1));
      double den = a*e;
      double xr = (ax+num2)/den, xs = (ax-num2)/den;
      double yr, ys;
      if (y == 0)
        yr = sqrt((1-a*xr*xr)/b), ys = -sqrt((1-a*xr*xr)/b);
      else
        yr = (1-ax*xr)/by, ys = (1-ax*xs)/by;
      double ps2 = sqr(x-xs)+sqr(y-ys);
      double pr2 = sqr(x-xr)+sqr(y-yr);
      double rs2 = sqr(xr-xs)+sqr(yr-ys);
      double cosT = (pr2+ps2-rs2)/(2*sqrt(pr2*ps2));
      if (cosT <= 0 || cosT * cosT < 0.5) total += (x == 0 || y == 0) ? 2: 4;
    }
    }
  printf("%d\n", total);
  return 0;
}
