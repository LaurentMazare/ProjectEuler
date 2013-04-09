// Very brute force approach based on the notations from:
// http://en.wikipedia.org/wiki/Square_root_of_a_2_by_2_matrix
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXTAU 10000000
#define MAX_F 10000000
typedef long long int lli;

lli gcd(lli a, lli b) {
  while (b != 0) {
    lli tmp = b;
    b = a % b;
    a = tmp;
  }
  return a;
}

int * factors;

int nb_divs(lli n) {
  int res = 1;
  if (n >= MAX_F) {
    for (lli i = 1; i <= n; ++i) if (n % i == 0) ++res;
  }
  else {
    while (n != 1) {
      int p = factors[n];
      int nb_p = 0;
      while (n % p == 0) {n /= p; nb_p++;}
      res *= (1 + nb_p);
    }
  }
  return res;
}

int main(int argc, char* argv[]) {
  factors = malloc(MAX_F * sizeof *factors);
  for (int i = 0; i < MAX_F; ++i) factors[i] = i;
  for (int i = 2; i < MAX_F; ++i)
    if (factors[i] == i) {
      int j = i;
      while (j < MAX_F) {factors[j] = i; j += i;}
    }
  lli total = 0;
  for (lli tau = 1; tau < MAXTAU; ++tau) {
    for (lli t1 = 1; t1*t1 <= tau; ++t1) {
      lli two_s = tau - t1 * t1;
      if (two_s & 1 || two_s == 0) continue;
      lli s = two_s / 2;
      lli delta = s * s;
      lli t2_2 = tau + two_s;
      lli t2 = (lli)sqrt(t2_2);
      if (t2 * t2 != t2_2) continue;
      lli g = gcd(t1, t2);
      lli lcm = (t1 * t2) / g;
      lli max_ad = (1+tau/2) * (tau/2);
      for (lli beta_gamma = 1;; ++beta_gamma) {
        lli a_times_d = delta + beta_gamma * lcm * lcm;
        if (max_ad < a_times_d) break;
        // Solve a, d
        lli delta = tau * tau - 4 * a_times_d;
        if (delta < 0) continue;
        lli sqrt_delta = (lli)sqrt(delta);
        if (sqrt_delta*sqrt_delta != delta || sqrt_delta % 2 != tau % 2) continue;
        lli a = (tau - sqrt_delta) / 2;
        lli d = (tau + sqrt_delta) / 2;
        if (s < a && s < d && (a+s) % t2 == 0 && (a-s) % t1 == 0 && (d+s) % t2 == 0 && (d-s) % t1 == 0) {
          lli mult = a == d ? 1: 2;
          total += nb_divs(beta_gamma) * mult;
        }
      }
    }
  }
  printf("%lli\n", total);
}
