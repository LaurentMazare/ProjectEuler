/* This solution iterates over all possible values for the minimum a
 * and the second minimum b.
 * e = Sum_a Sum_b b * P[A = a and B = b] where A and B are the related
 * random variable.
 * If a = b:
 * P[A=a, B=a] = P[A=a] - P[A=a, B>a]
 * Else:
 * P[A=a, B=b] = P[A=a, B>=b] - P[A=a, B>b]
 * And if c(n, p) stands for chooses p within n,
 * P[A=a] = P[A>=a] - P[A>a]
 * P[A>=a] = c(N-1-M*(a-1), M-1) / c(N-1, M-1)
 *   This is because all segments have length at least a.
 * For b strictly greater than a,
 * P[A=a, B>=b] = M*c(N-1-M*(b-2)-a, M-2)/c(N-1, M-1) 
 *   This is because one segment among M has length a and
 *   all the others have length at least b.
 * These two last formulaes are precomputed in the arrays p_m1 and p_m2 below.
 */
#include<stdio.h>
#include<stdlib.h>
#define N 10000000
#define M 100
#define P_M1(x) ((x)>0 ? p_m1[x]: 0)
#define P_M2(x) ((x)>0 ? p_m2[x]: 0)

int main(int argc, char* argv[]) {
  double res = 0.0;
  double* p_m1 = malloc(N * sizeof *p_m1);
  double* p_m2 = malloc(N * sizeof *p_m2);
  for (int i = 0; i < N; i++) {
    if (i < M-1) p_m1[i] = 0;
    else {
      double prod1 = 1;
      for (int j = 0; j < M-1; j++) prod1 *= (double)(i-j)/(double)(N-1-j);
      p_m1[i] = prod1;
    }
    if (i < M-2) p_m2[i] = 0;
    else {
      double prod2 = 1;
      for (int j = 0; j < M-2; j++) prod2 *= (double)(i-j)/(double)(N-1-j);
      p_m2[i] = M*(M-1)*prod2/(N-M+1);
    }
  }
  for (int a = 1; a <= N / M; a++) {
    for (int b = a; b <= (N-a) / (M-1); b++) {
      double p_b = 0;
      if (a == b)
        p_b = P_M1(N-1-M*(a-1)) - P_M1(N-1-M*a) - P_M2(N-1-M*a);
      else
        p_b = P_M2(N-1-(M-1)*(b-1)-a) - P_M2(N-1-(M-1)*b-a);
      res += p_b * b;
    }
  }
  printf("%.5f\n", res);
  return 0;
}
