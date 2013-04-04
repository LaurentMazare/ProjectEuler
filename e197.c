#include<stdio.h>
#include<math.h>
double f(double x) {
  double e = pow(2, 30.403243784 - x * x);
  return floor(e) * 1e-9;
}
int main(int argc, char* argv[]) {
  int n = 0;
  double u = -1;
  while (n++<10000) {
    u=f(u);
  }
  printf("%.9f\n", u+f(u));
  return 0;
}
