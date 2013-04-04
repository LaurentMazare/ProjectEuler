#include <stdio.h>
#include <math.h>
int is_prime(int n) {
  int i, bound = 1+(int)sqrt(n);
  for (i=2; i<bound; i++) {
    if (n % i==0) return 0;
  }
  return 1;
}
int main(int argc, char* argv[]) {
  long long a = 1;
  int index = 0;
  long long bound = 1000 * 1000 * 1000;
  bound *= 10;
  while (1) {
    if (is_prime(++a)) {
      long long sqr_a = a*a;
      long long r = (2 * ++index * a) % sqr_a;
      if (r > bound) {
        printf("%i\n", 1+index);
        return 0;
      }
    }
  }
  return 0;
}

