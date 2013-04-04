#include<stdio.h>
#include<stdlib.h>

int a(int x) {
  int i = 1;
  int val = 1;
  while (1) {
    val = (val * 10 + 1) % x;
    i++;
    if (val == 0) break;
  }
  return i;
}

int main(int argc, char* argv[]) {
  int x = 999999;
  int max = 0;
  while (1) {
    x += 2;
    if (x % 5 == 0) continue;
    int aa = a(x);
    if (aa > 1000000) break;
    if (aa > max + 1000) max = aa;
  }
  printf("%i\n", x);
  return 0;
}
