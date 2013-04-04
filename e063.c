#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[]) {
  int n, i;
  int nb = 0;
  for (n=1; n<190; n++) {
    for (i=1; i<10; i++) {
      double d = pow(i, n);
      double dec = 1+floor(log(d)/log(10));
      if (dec == n) {
        nb++;
      }
    }
  }
  printf("%i\n", nb);
  return 0;
}
