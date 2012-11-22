// Dynamic programming solution for 377
// The idea is that if d(n) is the number of numbers with sum of digits n (not using 0)
// and f(n) is their sum, then:
// d(n) = \sum_{i=1}^9 d(n-i)                 using 0 for negative indexes, d(0) = 1
// f(n) = \sum_{i=1}^9 10*f(n-i) + i * d(n-i) using 0 for negative indexes, s(0) = 0
// Then the result comes from fast exponentiation of the 18*18 matrix that computes
// the values of f(i), d(i) for i in [n+1, n+9] using values of f(i), d(i)
// for i in [n, n+8]
#include<stdio.h>
#include<stdlib.h>
#define MODP 1000000000
#define DIM 18
#define HDIM 9
typedef unsigned long long int llu;

llu* mult_mod(llu* a, llu* b) {
  llu* res = malloc(DIM * DIM * sizeof *res);
  for (int i = 0; i < DIM; i++)
    for (int j = 0; j < DIM; j++) {
      llu sum = 0;
      for (int k = 0; k < DIM; k++) sum = (sum + a[i+DIM*k]*b[k+DIM*j]) % MODP;
      res[i + DIM * j] = sum;
    }
  return res;
}

llu* mult_vec(llu* a, llu* vec) {
  llu* res = malloc(DIM * sizeof *res);
  for (int i = 0; i < DIM; i++) {
    res[i] = 0;
    for (int k = 0; k < DIM; k++) res[i] = (res[i] + a[i+DIM*k]*vec[k]) % MODP;
  }
  return res;
}

int main(int argc, char* argv[]) {
  llu* a = malloc(DIM * DIM * sizeof *a);
  for (int i = 0; i < DIM * DIM; i++) a[i] = 0;
  for (int i = 0; i < HDIM; i++) {
    a[HDIM-1+DIM*i] = 10;
    a[HDIM-1+DIM*(i+HDIM)] = HDIM - i;
    a[DIM-1+DIM*(i+HDIM)] = 1;
    if (i < HDIM-1) {
      a[i+DIM*(i+1)] = 1;
      a[HDIM+i+DIM*(i+HDIM+1)] = 1;
    }
  }
  llu* vec = malloc(DIM * sizeof *vec);
  for (int i = 0; i < DIM; i++) vec[i] = 0;
  vec[DIM-1] = 1;
  llu total = 0;
  for (int i = 0; i < 17; i++) {
    llu* tmp = a;
    for (int j = 0; j < 13 - 1; j++) tmp = mult_mod(a, tmp);
    a = tmp;
    llu* v = mult_vec(a, vec);
    total += v[HDIM-1];
  }
  printf("%llu\n", total);
  return 0;
}
