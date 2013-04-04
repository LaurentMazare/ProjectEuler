#include <stdio.h>
#include <math.h>

int nb_of_triangles(int p) {
  int a, b, c;
  int nb = 0;
  for (a = 1; a <= 1 + p / 3; a++)
    for (b = 1 + a; b <= 1 + (p -  a) / 2; b++) {
      c = p - a - b;
      if (c * c == a * a + b * b) nb++;
    }
  return nb;
}

int main(int argc, char* argv[]) {
  int i;
  int max = 0;
  int max_i = 0;
  for (i = 1; i <= 1000; i++) {
    int nb = nb_of_triangles(i);
    if (nb > max) {max = nb; max_i = i;}
  }
  printf("max: %i\n", max_i);
  return 0;
}
