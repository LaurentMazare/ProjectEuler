#include <stdio.h>
#include <stdlib.h>

int rad(int n) {
  int i = 1;
  int res = 1;
  while (n != 1) {
    if (n % ++i == 0) {
      res *= i;
      while (n % i == 0) n/=i;
    }
  }
  return res;
}
#define SIZE 100000
#define TARGET 10000
typedef struct pair {
  int k;
  int rad;
} pair;
int compar(const void* v1, const void* v2) {
  pair* p2 = (pair*)v2;
  pair* p1 = (pair*)v1;
  return p1->rad - p2->rad;
}
int main(int argc, char* argv[]) {
  pair* rads = (pair*)malloc(SIZE*sizeof(pair));
  int i;
  for(i=0;i<SIZE;i++) {
    rads[i].k=i+1;
    rads[i].rad=rad(i+1);
  }
  qsort(rads, SIZE, sizeof(pair), &compar);
  printf("%i\n", rads[TARGET-1].k);
  return 0;
}
