#include<stdio.h>
#define SIZE 1000

int main(int argc, char* argv[]) {
  long long res[SIZE];
  int i;
  res[0]=1;
  for (i=1;i<SIZE; i++) {
    int j;
    res[i]=res[i-1];
    if (i>=50) res[i]++;
    for (j=50; j<i; j++) {
      res[i]+=res[i-j-1];
    }
    if (res[i]>=1000000) {
      printf("%i\n", i);
      return 0;
    }
  }
  return 0;
}
