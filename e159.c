#include<stdio.h>
#include<stdlib.h>

#define max(x,y) (x>y)?(x):(y)
#define MAX_N 1000000

int drs(int x) {
  int sum = x;
  while (sum >= 10) {
    int tmp_sum = sum;
    sum = 0;
    while (tmp_sum != 0) { sum += tmp_sum % 10; tmp_sum /= 10; }
  }
  return sum;
}

int main(int argc, char* argv[]) {
  int* mdrs = (int*)malloc(MAX_N * sizeof(int));
  int i;
  long long int sum = 0;
  for (i = 2; i < MAX_N; i++) mdrs[i] = drs(i);
  for (i = 2; i < MAX_N; i++) {
    int j = 1;
    int index;
    sum += mdrs[i];
    while ((index = ++j * i) < MAX_N) {
      mdrs[index] = max(mdrs[index], drs(j) + mdrs[i]);
    }
  }
  printf("%lli\n", sum);
  return 0;
}
