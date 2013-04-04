#include<stdio.h>
int sqr(int x) {return x*x;}
#define MAX 50
int main(int argc, char* argv[]) {
  int x1, y1, x2, y2;
  int nb=0;
  for(x1=0;x1<=MAX;x1++)
    for(x2=x1;x2<=MAX;x2++)
      for(y1=0;y1<=MAX;y1++) {
        int min_y2 = 0;
        if (x1==x2) min_y2 = y1;
        for (y2=min_y2;y2<=MAX;y2++) {
          int d1 = sqr(x1) + sqr(y1);
          int d2 = sqr(x2) + sqr(y2);
          int d3 = sqr(x1-x2) + sqr(y1-y2);
          if (d1 != 0 && d2 != 0 && d3 != 0)
            if (d1 == d2 + d3 || d2 == d1 + d3 || d3 == d1 + d2) nb++;
        }
      }
  printf("%i\n", nb);
  return 0;
}
