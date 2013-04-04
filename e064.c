#include<stdio.h>
#include<math.h>
#define MAXP 10000
#define DEBUG 0

int main(int argc, char* argv[]) {
  int nb = 0;
  int states[MAXP];
  for(int i = 1; i <= MAXP; i++) {
    int len = 0;
    states[0] = 0;
    states[1] = 1;
    states[2] = (int)sqrt(i);
    if(states[2]*states[2]==i) continue;
    if(DEBUG) printf("%d: ", i);
    while(1) {
      int old_m = states[3*len];
      int old_d = states[3*len+1];
      int old_a = states[3*len+2];
      len++;
      int m = states[3*len] = old_d * old_a - old_m;
      int d = states[3*len+1] = (i - m * m) / old_d;
      int a = states[3*len+2] = (int)((sqrt(i)+(double)m)/(double)d);
      int k;
      for(k = 0; k < len; k++) if(states[3*k] == m && states[3*k+1] == d && states[3*k+2] == a) break;
      if (k != len) break;
      if(DEBUG) printf("%d, ", a);
    }
    if(DEBUG) printf("\n");
    if(len%2==0) nb++;
  }
  printf("Nb: %d\n", nb);
  return 0;
}
