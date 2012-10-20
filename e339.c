/* Let e_{i, j} be the max number of white sheeps that Peredur could
 * get if he starts by removing the number of black sheeps that he
 * wants (i and j are the number of white and black sheeps respectively.
 * E(n) = 0.5 * e_{n-1, n+1} + 0.5 * e_{n+1, n-1}
 * e_{0, n} = 0, e_{n, 0} = n
 * e_{i, j} = max(e_{i, j-1}, p * e_{i+1, j-1} + (1-p) * e_{i-1, j+1})
 *            with p = i / (i+j)
 */
#include "euler_math.h"
#define TARGET 10000
double max(double x, double y) {
  return x < y ? y: x;
}

int main(int argc, char* argv[]) {
  double prev_e[TARGET*2+1];
  double e[TARGET*2+1];
  prev_e[0] = 0; prev_e[1] = 1; // Case where sum == 1
  for (int sum = 2; sum <= 2 * TARGET; sum++) {
    for (int i = 1; i < sum; i++) e[i] = prev_e[i];
    e[0] = 0; e[sum] = 0;
    // Bisection until e[sum] = sum
    double lo = e[sum/2];
    double up = e[sum/2]+2;
    while (up - lo > 1e-8) {
      double mid = (up + lo) / 2.0;
      e[sum/2+1] = mid;
      for (int i = sum/2+2; i <= sum; i++) {
        double p = (double)(i-1) / (double)sum;
        e[i] = 1.0/p * e[i-1] - (1.0-p)/p * e[i-2];
      }
      if (e[sum] > sum) up = mid; else lo = mid;
    }
    for (int i = 0; i <= sum; i++) prev_e[i] = e[i];
  }
  printf("E(%d) = %.6f\n", TARGET, 0.5*e[TARGET-1] + 0.5*e[TARGET+1]);
  return 0;
}
