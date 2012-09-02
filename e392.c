#include<stdio.h>
#include<math.h>
#define STEPS 400

int main(int argc, char* argv[]) {
  double lo = 0.0000001;
  double up = 0.9999999;
  while (up - lo>1e-15) {
    double mid = (up + lo) / 2;
    double x_m2 = 0;
    double x_m1 = mid;
    double area = x_m1 - x_m2;
    for (int i = 2; i <= STEPS/2 + 1; i++) {
      double sqrt1 = sqrt(1 - x_m1 * x_m1);
      double sqrt2 = sqrt(1 - x_m2 * x_m2);
      double x = x_m1 - (sqrt1 - sqrt2) * sqrt1 / x_m1;
      area += (x - x_m1) * sqrt1;
      x_m2 = x_m1;
      x_m1 = x;
      if (x_m1 > 1) break;
    }
    printf(">>>%f %.10f\n", x_m1, 4*area);
    if (x_m1 > 1) up = mid;
    else lo = mid;
  }

  return 0;
}
