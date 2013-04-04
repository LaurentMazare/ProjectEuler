#include <stdio.h>
int fact(int n) {
 int res = 1;
 while (n) {
   res *= n--;
 } 
 return res;
}

int next(int x) {
  int res = 0;
  while (x != 0) {
    res += fact(x%10);
    x/=10;
  }
  return res;
}

#define MAXL 100
int length(int n) {
  int previous[MAXL];
  int nb = 1;
  previous[0]=n;
  while (1) {
    int i;
    n = next(n);
    for (i=0;i<nb;i++) if(previous[i]==n) break;
    if (i!=nb) break;
    previous[nb++]=n;
  }
  return nb;
}

int main(int argc, char* argv[]) {
  int n, res = 0;
  int nb = 0;
  for (n=1; n<=1000000; n++) {
    if (length(n)==60) res = ++nb;
  }
  printf("%d\n", res);
  return 0;
}
