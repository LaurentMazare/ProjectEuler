#include<stdio.h>
#include<stdlib.h>
#define WIDTH 32
#define HEIGHT 10
long long int pow2(long long int x) {
  return (1 << x);
}
int main(int argc, char* argv[]) {
  long long int w1[WIDTH];
  long long int* configs[WIDTH];
  long long int i;
  long long int nb_configs;
  long long int result = 0;
  long long int* results[HEIGHT];
  w1[1]=w1[2]=w1[3]=1;
  configs[1] = (long long int*)malloc(sizeof(long long int)); configs[1][0]=pow2(1);
  configs[2] = (long long int*)malloc(sizeof(long long int)); configs[2][0]=pow2(2);
  configs[3] = (long long int*)malloc(sizeof(long long int)); configs[3][0]=pow2(1)+pow2(3);
  for(i=4; i<WIDTH; i++) {
    long long int j;
    w1[i] = w1[i-2]+w1[i-3];
    configs[i] = (long long int*)malloc(w1[i]*sizeof(long long int));
    for(j=0; j<w1[i-2]; j++)
      configs[i][j] = configs[i-2][j]+pow2(i);
    for(j=0; j<w1[i-3]; j++)
      configs[i][w1[i-2]+j] = configs[i-3][j]+pow2(i);
  }
  nb_configs = w1[WIDTH-1];
  for (i=0; i<nb_configs; i++) configs[WIDTH-1][i] -= pow2(WIDTH-1);

  for(i=0; i<HEIGHT; i++) {
    long long int j, k;
    result = 0;
    results[i]=(long long int*)malloc(nb_configs*sizeof(long long int));
    if (i==0)
      for (j=0; j<nb_configs; j++) results[i][j]=1;
    else
      for (j=0; j<nb_configs; j++) {
        results[i][j] = 0;
        for (k=0; k<nb_configs; k++)
          if ((configs[WIDTH-1][j] & configs[WIDTH-1][k]) == 0) results[i][j]+=results[i-1][k];
        result += results[i][j];
      }
  }
  printf("%lli\n", result);
  return 0;
}
