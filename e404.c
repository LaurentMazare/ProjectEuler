// Using polar coordinates, we can show that the problem is equivalent to
// finding all the triples (a, b, c) such that:
// 5*b^2*c^2 = 4*a^2*(b^2+c^2)
// And a < b < c < 2*a
// For that purpose, we write 2a = b*c*sqrt(5/(b^2+c^2))
// and so there exists an integer alpha such that: b^2+c^2 = 5*alpha^2
//
// We now aim at finding all the triples (x, y, z) such that x^2+y^2=5z^2
// For this, we use the same trick as in 317 (see comments in the code).
// This is equivalent to x^2+y^2 = 5 where x and y are rationals.
// (2, 1) is a trivial solution for this.
// Other solutions (x, y) are on a line with (2, 1) that has a rational
// slope p/q (because (x, y) are rationals).
// Hence x = 2+t, y = 1+t*p/q
// This gives t = - (2m+4)/(1+m^2)
// Which in turn gives x = (2m^2-2m-2)/(1+m^2), y = (1-m^2-4m)/(1+m^2)
// x = (2p^2-2pq-2q^2)/(p^2+q^2), y = (q^2-p^2-4pq)/(p^2+q^2)
// Back into integers, we get:
// x = 2p^2-2pq-2q^2, y = q^2-p^2-4pq, z = p^2+q^2
#include<stdio.h>
#define MAX_A 100000000000000000LL
typedef long long int lli;
lli gcd(lli a, lli b) {
  if (b) return gcd(b, a % b);
  return a;
}

int main(int argc, char* argv[]) {
  lli total = 0;
  for (lli p = 1; p < 20000; ++p) {
    lli p2 = p * p;
    for (lli q = 1; q < 20000; ++q) {
      if (gcd(p, q) != 1) continue;
      lli q2 = q * q, pq = p * q;
      lli x = 2*p2 - 2*pq - 2*q2;
      lli y = q2 - p2 - 4*pq;
      lli z = p2 + q2;
      if (x < 0) x = -x;
      if (y < 0) y = -y;
      if (y < x) {
        lli tmp = y;
        y = x;
        x = tmp;
      }
      if (x <= z || 2*z <= y) continue;
      if (gcd(x, gcd(y, z)) != 1) continue;
      int parity = (x&1) && (y&1);
      lli qty = (MAX_A * (parity?1: 2)) / (x*y);
      total += qty;
    }
  }
  printf("%lli\n", total);
  return 0;
}
