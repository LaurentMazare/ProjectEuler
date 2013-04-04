#include<stdio.h>

int main(int argc, char* argv[]) {
  long long res[51];
  int i;
  res[0]=1;
  for (i=1;i<51; i++) {
    int j;
    res[i]=res[i-1];
    if (i>=3) res[i]++;
    for (j=3; j<i; j++) {
      res[i]+=res[i-j-1];
    }
  }
  printf("%lli\n", res[50]);
  return 0;
}
