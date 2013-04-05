#include<stdio.h>
#include<math.h>

double f(double r) {
  double r4999 = pow(r, 4999);
  double r5000 = r * r4999;
  double t1 = 900 * (1 - r5000) / (1 - r);
  double t2 = 3 * (1 - 5000 * r4999 + 4999 * r5000) / ((1 - r) * (1 - r));
  return t1 - t2 + 6e11;
}
double ff(double r) {
  int k;
  double res = 0;
  for (k=1;k<=5000;k++) res += (900-3*k)*pow(r,k-1);
  return res+6e11;
}


double zero(double min, double max) {
  while (1) {
    double mid;
    if (max - min < 1e-15) break;
    mid = (min + max) / 2;
    if (ff(mid) < 0) max = mid;
    else min = mid;
  }
  return min;
}
int main(int argc, char* argv[]) {
  double z = zero(1+1e-5,1+1e-2);
  printf("%.12f\n", z);
  return 0;
}
