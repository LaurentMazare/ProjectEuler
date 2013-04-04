#include <stdio.h>
int cache[100][100];
int nb_sum(int low, int n) {
  int i;
  int nb = 0;
  if (n == 0) return 1;
  else if (n < low) return 0;
  else if (n == low) return 1;
  else if (cache[low][n] != -1) return cache[low][n];
  for (i=low; i<=n; i++) {
    int sum = nb_sum(i, n-i);
    nb += sum;
    }
  cache[low][n]=nb;
  return nb;
}

int main(int argc, char* argv[]) {
  int i, j;
  for (i=0; i<100; i++)
    for (j=0; j<100; j++)
      cache[i][j]=-1;
  printf("%i\n", nb_sum(1, 100)-1);
  return 0;
}
