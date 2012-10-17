#include "euler_math.h"
#define INIT_S 14025256

// This Blum-Blum-Shup sequence has periodicity 2534198
// The sum of digits in one period is 80846691
lli current_s = INIT_S;
int next_s() {
  int prev_s = current_s;
  current_s = (current_s * current_s) % 20300713;
  return prev_s;
}

int main(int argc, char* argv[]) {
  int period = 80846691;
  int* p = malloc((period+1) * sizeof *p);
  for (int i = 0; i <= period; i++) p[i] = 0;
  int to_scan = 100;
  int* sum_digits = malloc(to_scan * sizeof *sum_digits);
  for (int i = 0; i < to_scan; i++) sum_digits[i] = 0;
  int num_digits = 0;
  for(int i = 0; i <= 2534198 + to_scan; i++) { // Higher limit to be on the safe side
    int s = next_s();
    int ss = 0; // Will contain the reverse of s in basis 10
    while (s != 0) {
      ss = 10 * ss + s % 10;
      s /= 10;
    }
    while (ss != 0) {
      int dgt = ss % 10;
      for (int index = 0; index < to_scan; index++) {
        if (index > num_digits) continue;
        sum_digits[index] += dgt;
        if (sum_digits[index] <= period && p[sum_digits[index]] == 0) p[sum_digits[index]] = index + 1;
      }
      ss /= 10;
      num_digits += 1;
    }
  }
  lli total = 0;
  lli max_l = 2000000000000000LL;
  for (int i = 1; i <= period; i++) {
    lli nb = ((period + max_l - i) / period);
    total += p[i] * nb;
  }
  printf("Total: %lli\n", total);
  return 0;
}
