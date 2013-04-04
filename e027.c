#include<stdio.h>
#include<stdlib.h>
#define MAX 1000

#define max(x,y) (x>y)?(x):(y)
#include <math.h>

int is_prime(int i) {
  int j = 0;
  int n = (int)sqrt(i);
  if (i < 2) return 0;
  for (j = 2; j <= n; j++) {
    if (i % j == 0) return 0;
  }
  return 1;
}


int main(int argc, char* argv[]) {
  int a, b;
  int longest = -1;
  int where = 0;
  for (a=1-MAX; a < MAX; a++)
    for (b=max(0, -1 - a); b < MAX; b++) {
      int j = 0;
      while (is_prime(j*j+a*j+b)) j++;
      if (j > longest) {
        longest = j;
        where = a * b;
      }

    }
  printf("%i\n", where);
  return 0;
}
