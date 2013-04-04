#include<stdio.h>
#include<stdlib.h>

#define MAXP 1000000

int main(int argc, char* argv[]) {
  int* solutions = (int*)malloc(MAXP*sizeof(int));
  for (int x = 0; x < MAXP; x++) solutions[x] = 0;
  for (long long int x = 1; x < 10000000; x++) {
    long long int low = 0;
    long long int up = x;
    while (up - low > 1) {
      long long int mid = (low + up) / 2;
      long long int fmid = 3 * mid * mid + 2 * mid * x - x * x;
      if (fmid > 0) up = mid;
      else low = mid;
    }
    long long int a = low;
    while (1) {
      long long int l = 3 * a * a + 2 * a * x - x * x;
      if (l >= MAXP) break;
      if (l >= 0) solutions[l]++;
      a++;
    }
  }
  int nb = 0;
  for (int x = 0; x < MAXP; x++) if (solutions[x] == 10) nb++;
  printf("%i\n", nb);
  return 0;
}
