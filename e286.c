#include<stdio.h>
#include<stdlib.h>

double proba(double q) {
  double p[21][51];

  p[0][0] = 1;
  for (int j = 1; j <= 20; j++) p[j][0] = 0;
  for (int i = 1; i <= 50; i++) {
    double score_p = 1 - (double)i / q;
    p[0][i] = (1 - score_p) * p[0][i-1];
    for (int j = 1; j <= 20; j++)
      p[j][i] = p[j][i-1] * (1 - score_p) + p[j-1][i-1] * score_p;
  }
  return p[20][50];
}

int main(int argc, char* argv[]) {
  double low = 50;
  double up = 100;
  while (up - low > 1e-12) {
    double mid = (low + up) / 2;
    double p = proba(mid);
    if (p < 0.02) up = mid;
    else low = mid;
  }
  printf("%.10f\n", (low + up) / 2);
  return 0;
}
