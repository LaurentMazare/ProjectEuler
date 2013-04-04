#include<stdio.h>
#include<math.h>
#define BOUND 10000
#define e 2.71828182846

int gcd(int m, int n) {
  while(m > 0) {
    if( n > m ) { int t = m; m = n; n = t; }
    m -= n;
  }
  return n;
}

int m(int n) {
  double where_max = n / e;
  int low = (int)where_max;
  int up = low + 1;
  int k;
  double v_low = (low*log((double)n / low));
  double v_up = (up*log((double)n / up));
  if (v_low > v_up) k = low;
  else k = up;
  k /= gcd(k,n);
  while (k%2 == 0) k /= 2;
  while (k%5 == 0) k /= 5;
  return (k!=1);
}

int main(int argc, char* argv[]) {
  int n;
  int sum = 0;
  for (n = 5; n <= BOUND; n++) {
    if (m(n))
      sum += n;
    else
      sum -= n;
  }
  printf("%i\n", sum);
  return 0;
}
