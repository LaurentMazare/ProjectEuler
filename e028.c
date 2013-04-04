#include <stdio.h>

int main(int argc, char* argv[]) {
  int res = 1;
  int i = 0;
  int tmp = 1;
  for (i = 0; i < 500; i++) {
    tmp += (2 * i + 2);
    res += tmp;
    tmp += (2 * i + 2);
    res += tmp;
    tmp += (2 * i + 2);
    res += tmp;
    tmp += (2 * i + 2);
    res += tmp;
  }
  printf("res: %i\n", res);
  return 0;
}
