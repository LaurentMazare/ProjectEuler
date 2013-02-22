// Let a = AB, b = BC, c = AC, n = BE
// Using wxmaxima on the following, we obtain
// n = (a*b)/(b+c)
//   xc: (a^2+b^2-c^2)/(2*a);
//   yc: sqrt(b^2-xc^2);
//   xo: a/2;
//   yo: (b^2+c^2-a^2)/(4*yc);
//   a1: xc-xo;
//   a2: yc-yo;
//   b1: yc*(b+c);
//   b2: a*b-(b+c)*xc;
//   b3: xc*yc*(b+c)+yc*b2;
//   xe: b3 / (b1-a1*b2/a2);
//   ye: -a1*xe/a2;
//   n2: xe*xe+ye*ye;
//   factor(ratsimp(n2));
#include<stdio.h>
#define MAXP 100000

typedef long long int lli;

lli gcd(lli a, lli b) {
  while (b != 0) {
    lli tmp = b;
    b = a % b;
    a = tmp;
  }
  return a;
}

int main(int argc, char* argv[]) {
  lli res = 0;
  for (lli a = 1; a <= MAXP/2; a++) {
    if (a % 100 == 0) printf("%lli %lli\n", a, res);
    for (lli b_plus_c = a+1; b_plus_c <= 2*a; b_plus_c++) {
      if (MAXP < a + b_plus_c) break;
      lli den = b_plus_c / gcd(a, b_plus_c);
      lli tmp_res = b_plus_c/ 2 / den - (b_plus_c - a - 1) / den;
      if (tmp_res > 0) res += tmp_res;
    }
  }
  printf("Found %lli triangles.\n", res);
  return 0;
}
