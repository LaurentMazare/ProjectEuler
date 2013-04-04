#include <stdio.h>

int main(int argc, char* argv[]) {
  long long sum = 0;
  int a = 0;
  for (a=3; a<=1000; a++) {
    int rmax = 2;
    int i = 0;
    int sqr_a = a*a;
    for (i=0; i<a; i++) {
      int r = (2 * (2*i+1) * a) % sqr_a;
      if (r > rmax) rmax = r;
    }
    sum+=rmax;
  }
  printf("%lli\n",sum);
  return 0;
}
