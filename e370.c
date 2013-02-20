#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#define MAXP 25000000000000LL
typedef long long unsigned int llu;
// Generate the Farey sequence
int main(int argc, char* argv[]) {
  llu res = 0;
  llu m = 1;
  llu prev_n = 1;
  llu n = 1;
  llu prev_m = 0;
  llu order = floor(sqrt(MAXP/3));
  while (m * m < m*n + n*n) {
    res += MAXP / ((m + n) * (m + n) - m * n);
    llu x = (order + prev_n) / n;
    llu tmp_m = x * m - prev_m;
    llu tmp_n = x * n - prev_n;
    prev_m = m, prev_n = n;
    m = tmp_m, n = tmp_n;
  }
  printf("%llu\n", res);
  return 0;
}
