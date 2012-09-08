#include "euler_bitarray.h"
#define MAXL 2000000000

int main(int argc, char* argv[]) {
  bitarray* b1 = bitarray_alloc(MAXL+1);
  bitarray* b2 = bitarray_alloc(MAXL+1);
  bitarray* b3 = bitarray_alloc(MAXL+1);
  bitarray* b7 = bitarray_alloc(MAXL+1);

  for (int x = 1; x * x < MAXL; x++)
    for (int y = 1; y < 100000; y++) {
      long long int x2 = x * x;
      long long int y2 = y * y;
      if (x2 + y2 < MAXL)
        bitarray_set(b1, x2 + y2, 1);
      else
        break;
      if (x2 + 2*y2 < MAXL)
        bitarray_set(b2, x2 + 2*y2, 1);
      if (x2 + 3*y2 < MAXL)
        bitarray_set(b3, x2 + 3*y2, 1);
      if (x2 + 7*y2 < MAXL)
        bitarray_set(b7, x2 + 7*y2, 1);
    }
  int nb = 0;
  for (int x = 0; x < MAXL; x++)
    if (bitarray_get(b1, x) && bitarray_get(b2, x) && bitarray_get(b3, x) && bitarray_get(b7, x))
      nb++;
  printf("%d\n", nb);
  return 0;
}
