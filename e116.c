#include <stdio.h>
long long cache[3][51];
long long nb_rec(int n, int len) {
  long long res = 0;
  int i;
  if (cache[n-2][len] != -1) return cache[n-2][len];
  for (i=0; i<=len-n; i++) {
    res += 1 + nb_rec(n, len - i - n);
  }
  cache[n-2][len] = res;
  return res;
}

int main(int argc, char* argv[]) {
  int i;
  for (i=0;i<51;i++) {cache[0][i]= -1; cache[1][i]=-1; cache[2][i]=-1;}
  printf("%lli\n", nb_rec(2, 50)+nb_rec(3, 50)+nb_rec(4,50));
  return 0;
}
