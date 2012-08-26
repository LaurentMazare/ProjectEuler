#include "euler_bitarray.h"
#define MAXL 1001

int key(int x, int y, int z) {
  int key;
  if (z <= y && y <= x)
    key = x * MAXL * MAXL + y * MAXL + z;
  else if (z <= x && x <= y)
    key = y * MAXL * MAXL + x * MAXL + z;
  else if (x <= y && y <= z)
    key = z * MAXL * MAXL + y * MAXL + x;
  else if (x <= z && z <= y)
    key = y * MAXL * MAXL + z * MAXL + x;
  else if (y <= z && z <= x)
    key = x * MAXL * MAXL + z * MAXL + y;
  else // if (y <= x && x <= z)
    key = z * MAXL * MAXL + x * MAXL + y;
  return key;
}

int main(int argc, char* argv[]) {
  bitarray* ba = bitarray_alloc(MAXL * MAXL * MAXL);
  long long int nb = 0;
  for (int x = 1; x < MAXL; x++)
    for (int y = 0; y <= x; y++)
      for (int z = 0; z <= y; z++) {
        if ((x == y && y == z) ||
            (y == 0 && z == 0) ||
            (x == y && z == 0)) {
          bitarray_set(ba, key(x, y, z), 1);
          continue;
        }
        int all_winning = 1;
        for (int i = 1; i <= x; i++) {
          if (!bitarray_get(ba, key(x-i, y, z)) ||
              (i <= y && (!bitarray_get(ba, key(x, y-i, z)) ||
                          !bitarray_get(ba, key(x-i, y-i, z)))) ||
              (i <= z && (!bitarray_get(ba, key(x, y, z-i)) ||
                          !bitarray_get(ba, key(x-i, y, z-i)) ||
                          !bitarray_get(ba, key(x, y-i, z-i)) ||
                          !bitarray_get(ba, key(x-i, y-i, z-i))))) {
            all_winning = 0;
            break;
          }
        }
        bitarray_set(ba, key(x, y, z), !all_winning);
        if (all_winning) nb += x + y + z;
      }
  printf("Found %lli losing configurations!\n", nb);
  return 0;
}
