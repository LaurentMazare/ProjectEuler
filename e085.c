#include <stdio.h>
#include <stdlib.h>
int nb_rectangles(int x, int y) {
  int i, j;
  int sum = 0;
  for (i=0; i<=x; i++)
    for (j=0; j<=y; j++)
      sum+=(x-i)*(y-j);
  return sum;
}

int main(int argc, char* argv[]) {
  int i, j;
  int closest = 20000000;
  int surface = 0;
  for (i=1; i<=2000; i++) {
    for (j=1; j<=2000; j++) {
      int nb = nb_rectangles(i, j);
      if (nb>2500000) break;
      int dist = abs(nb-2000000);
      if (dist < closest) {
        closest = dist;
        surface = i*j;
      }
    }
  }

  printf("%i\n", surface);
  return 0;
}
