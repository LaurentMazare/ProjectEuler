#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[]) {
  double cache[10000];
  int cache_size = 0;
  int a, b;
  for (a=2; a<=100; a++)
    for(b=2; b<=100; b++) {
      int i;
      double d = log(a)*b;
      for (i=0; i<cache_size; i++) {
        if (fabs(d-cache[i])<1e-10) break;
      }
      if (i==cache_size) cache[cache_size++]=d;
    }
  printf("%i\n", cache_size);

  return 0;
}
