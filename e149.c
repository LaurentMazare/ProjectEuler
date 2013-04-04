#include <stdio.h>
#include <stdlib.h>
#define MAX(a,b) ((a) > (b) ? (a) : (b)) 


int main(int argc, char* argv[]) {
  long long *s = (long long int*)malloc(4000000*sizeof(long long));
  long long k;
  for (k=1; k<=4000000; k++) {
    if (k <= 55)
      s[k-1] = (100003 - 200003*k + 300007*k*k*k) % 1000000 - 500000;
    else
      s[k-1] = (s[k-25] + s[k-56] + 1000000) % 1000000 - 500000;
  }

  int i;
  int j;
  int mode;
  long long max_sub=0;
  for (mode=0; mode<4; mode++) {
    for (i=0; i<2000; i++) {
      long long tmp_max=0;
      long long tmp_max_right=0;
      for (j=0; j<2000; j++) {
        long long m;
        if (0==mode) m = s[i+2000*j];
        else if (1==mode) m = s[j+2000*i];
        else if (2==mode) m = s[(i+j)%2000+2000*j];
        else if (3==mode) m = s[(i+2000-j)%2000+2000*j];
        tmp_max_right = MAX(0, tmp_max_right+m);
        tmp_max = MAX(tmp_max, tmp_max_right);
      }
      max_sub=MAX(max_sub, tmp_max);
    }
  }
  printf("%lli\n", max_sub);
  return 0;
}
