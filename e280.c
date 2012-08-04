#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[]) {
  double* e = (double*)malloc(sizeof(double) * 5*5*2048);
  double* old_e = (double*)malloc(sizeof(double) * 5*5*2048);
  for (int i = 0; i < 5 * 5 * 2048; i++) e[i] = 200.0;

  for (int iter = 0; iter < 2001; iter++) {
    for (int i = 0; i < 5 * 5 * 2048; i++) old_e[i] = e[i];
    for (int x = 0; x < 5; x++)
      for (int y = 0; y < 5; y++)
        for (int seeds = 0; seeds < 2048; seeds++) {
          double ee = 0;
          if (0b01111100000 != seeds) {
            if (x == 0 && !(seeds & (1 << 10)) && (seeds & (1 << y))) {
              int s = seeds - (1 << y) + (1 << 10);
              ee = old_e[x + 5 * y + 25 * s];
            }
            else if (x == 4 && (seeds & (1 << 10)) && !(seeds & (1 << (5+y)))) {
              int s = seeds - (1 << 10) + (1 << (y+5));
              ee = old_e[x + 5 * y + 25 * s];
            }
            else {
              double nb_dir = 0;
              ee = 0;
              if (y > 0) {
                nb_dir++;
                ee += old_e[x + 5 * (y-1) + 25 * seeds];
              }
              if (x > 0) {
                nb_dir++;
                ee += old_e[x - 1 + 5 * y + 25 * seeds];
              }
              if (x < 4) {
                nb_dir++;
                ee += old_e[x + 1 + 5 * y + 25 * seeds];
              }
              if (y < 4) {
                nb_dir++;
                ee += old_e[x + 5 * (y+1) + 25 * seeds];
              }
              ee = 1 + ee / nb_dir;
            }
          }
          e[x + 5 * y + 25 * seeds] = ee;
        }
    if (iter % 1000 == 0)
      printf("%-10d %.6f\n", iter, e[2 + 2 * 5 + 25 * 0b00000011111]);
  }
  return 0;
}
