// Use WolframAlpha to compute x(t) and y(t)
// Then the area is \int_0^1 y(t)x'(t)dt
// And the length is \int_0^1 sqrt(x'(t)^2+y'(t)^2) dt
// This last integral is computed by the numerical integration
// below
#include<stdio.h>
#include<math.h>
#define NB_STEPS 10000000

int main(int argc, char* argv[]) {
  double pi = 4.0 * atan(1);
  double v = 2 - sqrt((22-5*pi)/3);
  double l = 0;
  double prev_f = 0;
  for (int i = 0; i <= NB_STEPS; i++) {
    double t = ((double)i)/NB_STEPS;
    double t2 = t*t;
    double dx_dt = 9*v*t2 - 12*v*t + 3*v - 6*t2 + 6*t;
    double dy_dt = -9*v*t2 + 6*v*t + 6*t2 - 6*t;
    double f = sqrt(dx_dt*dx_dt + dy_dt*dy_dt);
    if (prev_f > 0) l += (f + prev_f) / (2.0 * NB_STEPS);
    prev_f = f;
  }
  printf("%.10f\n", 100 * (l*2/pi - 1));
  return 0;
}
