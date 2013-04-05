#include<stdio.h>
#include<stdlib.h>

#define N 20000000
#define P 15000000

int main(int argc, char* argv[]) {
  int* sum_f = (int*)malloc((N+1)*sizeof(int));
  int i;
  long long int result = 0;
  for (i = 2; i <= N; i++) sum_f[i]=0;
  for (i = 2; i <= N; i++)
    if (0 == sum_f[i]) {
      int j = 0;
      int tmp;
      while ((tmp = ++j * i) <= N) {
        int x = tmp;
        int res = 0;
        while (x % i == 0) { x/=i; res += i; }
        sum_f[tmp] += res;
      }
    }
  for( i = N - P + 1; i <= N; i++ ) result += sum_f[i];
  for( i = 2; i <= P; i++ ) result -= sum_f[i];
  printf("%lli\n", result);
  return 0;
}
