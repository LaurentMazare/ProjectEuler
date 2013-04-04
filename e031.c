#include <stdio.h>
int cache[8][201];
int nb_coins(int low, int x) {
  int nb = 0;
  if (cache[low][x]!=-1) return cache[low][x];
  if (x == 0) nb = 1;
  if (low <= 0 && x >= 1) nb += nb_coins(0, x-1);
  if (low <= 1 && x >= 2) nb += nb_coins(1, x-2);
  if (low <= 2 && x >= 5) nb += nb_coins(2, x-5);
  if (low <= 3 && x >= 10) nb += nb_coins(3, x-10);
  if (low <= 4 && x >= 20) nb += nb_coins(4, x-20);
  if (low <= 5 && x >= 50) nb += nb_coins(5, x-50);
  if (low <= 6 && x >= 100) nb += nb_coins(6, x-100);
  if (low <= 7 && x >= 200) nb += nb_coins(7, x-200);
  cache[low][x]=nb;
  return nb;
}
int main(int argc, char* argv[]) {
  int i, j;
  for (i=0; i<201; i++) for (j=0; j<8; j++) cache[j][i]=-1;
  printf("%i\n", nb_coins(0, 200));
  return 0;
}
