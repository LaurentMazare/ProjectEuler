#include<stdio.h>
long long cache[20][10][10];
long long aux(int length, int prev_1, int prev_2) {
  int i;
  long long res = 0;
  if (prev_1+prev_2>9) return 0;
  if (length == 0) return 1;
  if (cache[length][prev_1][prev_2]!=-1) return cache[length][prev_1][prev_2];
  for(i=0;i<=9-prev_1-prev_2;i++) res += aux(length-1,prev_2,i);
  cache[length][prev_1][prev_2]=res;
  return res;
}

int main(int argc, char* argv[]) {
  long long nb=0;
  int i,j,k;
  for(i=0;i<20;i++) for(j=0;j<10;j++) for(k=0;k<10;k++) cache[i][j][k]=-1;
  for(i=1;i<10;i++)
    for(j=0;j<10;j++)
      nb+=aux(18,i,j);
  printf("%lli\n", nb);
  return 0;
}
