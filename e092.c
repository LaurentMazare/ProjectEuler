#include <stdio.h>
#define SIZE 10000000
#define CACHE_SIZE 1000
int next(int x) {
  int i = 0;
  while (x != 0) {
    int d = x%10;
    i += d * d;
    x/=10;
  }
  return i;
}
int main(int argc, char* argv[]) {
  int i;
  int nb=0;
  int cache[CACHE_SIZE];

  for(i=1; i<CACHE_SIZE; i++) {
    cache[i]=0;
  }
  for(i=1; i<SIZE; i++) {
    int x = i;
    int ok = 0;
    while (!ok) {
      if (x==1) ok=1;
      else if (x==89) ok=89;
      else if (x < CACHE_SIZE && cache[x]) ok=cache[x];
      else x = next(x);
    }
    if (i < CACHE_SIZE) cache[i]=ok;
    if (89==ok) nb++;
  }
  printf("%i\n", nb);

  return 0;
}
