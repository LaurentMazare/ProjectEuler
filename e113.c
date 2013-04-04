#include <stdio.h>
#define MAXL 100
long long cache_i[10][MAXL+2];
long long cache_d[10][MAXL+2];
long long inc(int first, int length) {
  int i;
  long long res = 0;
  if (length == 1) return 1;
  if (cache_i[first][length]!=-1) return cache_i[first][length];
  for (i=first; i<=9; i++) {
    res += inc(i, length-1);
  }
  cache_i[first][length]=res;
  return res;
}
long long dec(int first, int length) {
  int i;
  long long res = 0;
  if (length == 1) return 1;
  if (cache_d[first][length]!=-1) return cache_d[first][length];
  for (i=0; i<=first; i++) {
    res += dec(i, length-1);
  }
  cache_d[first][length]=res;
  return res;
}

int main(int argc, char* argv[]) {
  long long res ;
  long long res2 = 0;
  int i, j;
  for (i=0; i<10; i++)
    for (j=0; j<=MAXL+1; j++) {
      cache_i[i][j]=-1;
      cache_d[i][j]=-1;
    }
  res = inc(0, MAXL+1);
  for (i=1; i<=MAXL+1; i++) res2 +=(dec(9, i)-1);
  
  printf("%lli\n", res + res2 - MAXL * 9 - 1);
  return 0;
}
