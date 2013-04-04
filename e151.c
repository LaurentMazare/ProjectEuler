#include<stdio.h>
double f(int a5, int a4, int a3, int a2) {
  double result = 0;
  int nb = a2 + a3 + a4 + a5;
  if (!a4 && !a3 && !a2) return 0;
  if (1 == nb) result++;
  if (a5) result += a5 * f(a5-1, a4, a3, a2) / nb;
  if (a4) result += a4 * f(a5+1, a4-1, a3, a2) / nb;
  if (a3) result += a3 * f(a5+1, a4+1, a3-1, a2) / nb;
  if (a2) result += a2 * f(a5+1, a4+1, a3+1, a2-1) / nb;
  return result;
}

int main(int argc, char* argv[]) {
  printf("%.6f\n", f(1, 1, 1, 1));
  return 0;
}
