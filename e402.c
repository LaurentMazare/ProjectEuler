#include<stdio.h>
#define MAXN 1234567890123LL
//#define MAXN 100

typedef long long int lli;
lli factors24[] = {1, 2, 3, 4, 6, 8, 12, 24};
lli m_array[24*24*24];

lli s(lli n, lli mod) {
  lli res = 0;
  for (lli a = 0; a < 24; ++a) {
    lli lambda_a = a == 0? n/24: (n+24-a)/24;
    for (lli b = 0; b < 24; ++b) {
      lli lambda_b = b == 0? n/24: (n+24-b)/24;
      lli lambda_ab = (lambda_a * lambda_b) % mod;
      for (lli c = 0; c < 24; ++c) {
        lli lambda_c = c == 0? n/24: (n+24-c)/24;
        lli lambda_abc = (lambda_ab * lambda_c) % mod;
        res = (res + m_array[24*24*a+24*b+c]*lambda_abc) % mod;
      }
    }
  }
  return res;
}

// Faster version of s when the previous value is known
lli s_rec(lli n, lli prev_s, lli mod) {
  lli prev_n = n - 1;
  lli ch = n % 24;
  lli lambdas[24];
  for (int x = 0; x < 24; ++x)
    lambdas[x] = x == 0? prev_n / 24: (prev_n+24-x)/24;
  lli res = prev_s + m_array[24*24*ch+24*ch+ch];
  for (int x = 0; x < 24; ++x) {
    lli lambda_x = lambdas[x];
    res = (res + lambda_x * (m_array[24*24*ch+24*ch+x] + m_array[24*24*ch+24*x+ch] + m_array[24*24*x+24*ch+ch])) % mod;
    for (int y = 0; y < 24; ++y) {
      lli tmp = m_array[24*24*ch + 24*x + y] + m_array[24*24*x + 24*ch + y] + m_array[24*24*x + 24*y + ch];
      res =  (res + tmp * lambda_x * lambdas[y]) % mod;
    }
  }
  return res;
}

lli find_fib_period_mod(lli mod) {
  lli u_prev = 0, u_n = 1, n = 2;
  while (1) {
    lli tmp = u_n;
    u_n = (u_n + u_prev) % mod;
    u_prev = tmp;
    if (u_n == 1 && u_prev == 0) break;
    n++;
  }
  return n-1;
}

lli find_sum_mod(int mod) {
  lli s1 = s(1, mod), s2 = s(2, mod), s3 = s(3, mod);
  lli prev_s = s3, i;
  int s_values[50000000];
  s_values[0] = 0;
  s_values[1] = s1;
  s_values[2] = s2;
  s_values[3] = s3;
  for (i = 4; i <= 50000000; ++i) {
    lli s_i = s_rec(i, prev_s, mod);
    s_values[i] = s_i;
    if (s_i == 0 && i % (24*mod) == 0) break;
    prev_s = s_i;
  }
  lli period = i;
  lli fib_period = find_fib_period_mod(period);
  lli sum = 0, fib_n = 1, fib_p = 0;
  for (lli n = 2; n < 2 + fib_period; ++n) {
    lli tmp = fib_n;
    fib_n = (fib_n + fib_p) % period;
    fib_p = tmp;
    lli nb_fib = (1 + (MAXN - n) / fib_period); // % mod;
    sum = (sum + s_values[fib_n] * nb_fib) % mod;
  }
  return sum % mod;
}
 
int main(int argc, char* argv[]) {
  for (lli a = 0; a < 24; ++a)
    for (lli b = 0; b < 24; ++b)
      for (lli c = 0; c < 24; ++c) {
        lli max_d = 0;
        for (lli i = 0; i < 8; ++i) {
          lli f24 = factors24[i];
          lli ok = 1;
          for (lli j = 1; j < f24; ++j)
            if ((j*j*j*j+a*j*j*j+b*j*j+c*j) % f24 != 0) {
              ok = 0;
              break;
            }
          if (ok) max_d = f24;
        }
        m_array[24*24*a+24*b+c] = max_d;
      }
  lli sum2 = find_sum_mod(512); //2^9
  lli sum5 = find_sum_mod(1953125); //5^9
  for (int i = 0;; ++i) { // Brute-force Chinese Remainder Theorem
    lli candidate = i * 1953125 + sum5;
    if (candidate % 512 == sum2) {
      printf("%lli\n", candidate);
      break;
    }
  }
  return 0;
}
