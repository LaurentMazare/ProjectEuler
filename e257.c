// THIS DOES NOT WORK FOR NOW
// As I've learn a lot looking at this one, here are some notes:
// First, a1/a2 = ((b+a)*(c+a)) / (b*c)
// Looking at the first values, a1/a2 is only equal to 2, 3, or 4.
//
// - a1/a2 = 4
// These are equilateral triangles, their number is MAXP / 3
//
// - a1/a2 = 2
// a*b + a*c + a*a = b*c
// (2a+b+c)^2 - (b+c)^2 = 4*b*c
// (2a+b+c)^2 = b^2 + c^2 + 6*b*c
// (2a+b+c)^2 = (b+3c)^2 - 8c^2
// To solve this, the general method is described in:
// http://mathforum.org/library/drmath/view/66725.html
// First solve u^2-8v^2 = 1 over rationals.
// For that, note that u=3, v=1 is a solution. Other solutions
// have the form u = 3+t, v = 1+t*p/q where gcd(p, q) = 1
// Reinjecting this into the equation, we obtain:
// u = (16*p*q - 3q^2 - 24p^2) / (q^2 - 8p^2)
// v = (-6*p*q +  q^2 +  8p^2) / (q^2 - 8p^2)
// And so we can get a, b, and c from p and q.
//
// - a1/a2 = 3 is similar to the previous case
// a*b + a*c + a*a = 2*b*c
// (2a+b+c)^2 = (b+5c)^2 - 24c^2
// We solve u^2 - 24v^2 = 1 (u=5, v=1 is a solution).
// u = (-5q^2 - 120p^2 + 48*p*q) / (q^2 - 24p^2)
// v = (  q^2 +  24p^2 - 10*p*q) / (q^2 - 24p^2)

#include<stdio.h>
#define MAXP 1000
#define MAXI 1000
typedef long long int lli;

lli abs(lli a) {return (a < 0) ? -a: a;}

lli gcd(lli a, lli b) {
  while (b != 0) {
    lli tmp = b;
    b = a % b;
    a = tmp;
  }
  return a;
}


int main(int argc, char* argv[]) {
  lli total = MAXP / 3;
  for (lli p = 1; p < MAXI; p++)
    for (lli q = 1; q < MAXI; q++) {
      if (gcd(p, q) != 1) continue; // We should use Stern-Brocot instead
      lli p2 = p * p, q2 = q * q, pq = p * q;
      lli c = abs(8 * p2 + q2 - 6 * pq);
      lli b = abs(16 * pq - 3 * q2 - 24 * p2) - 3 * c;
      lli two_a = abs(q2 - 8 * p2) - b - c;
      if (two_a & 1) continue;
      lli a = two_a / 2;
      lli g = gcd(gcd(a, b), c);
      a /= g;
      b /= g;
      c /= g;
      if (0 <= a && a <= b && b <= c && c < a + b && a + b + c <= MAXP) {
        printf("%5lli %5lli %5lli %5lli\n", a, b, c, a+b+c);
        printf("%lli\n", ((b+a)*(c+a))%(b*c));
        total += MAXP / (a+b+c);
      }
    }
   for (lli p = 1; p < MAXI; p++)
    for (lli q = 1; q < MAXI; q++) {
      if (gcd(p, q) != 1) continue; // We should use Stern-Brocot instead
      lli p2 = p * p, q2 = q * q, pq = p * q;
      lli c = abs(24 * p2 + q2 - 10 * pq);
      lli b = abs(48 * pq - 5 * q2 - 120 * p2) - 5 * c;
      lli two_a = abs(q2 - 24 * p2) - b - c;
      if (two_a & 1) continue;
      lli a = two_a / 2;
      lli g = gcd(gcd(a, b), c);
      a /= g;
      b /= g;
      c /= g;
      if (0 <= a && a <= b && b <= c && c < a + b && a + b + c <= MAXP) {
        printf("%5lli %5lli %5lli %5lli\n", a, b, c, a+b+c);
        printf("%lli\n", ((b+a)*(c+a))%(b*c));
        total += MAXP / (a+b+c);
      }
    }
  printf("%lli\n", total);
  return 0;
}
