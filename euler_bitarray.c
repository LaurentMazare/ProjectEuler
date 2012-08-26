#include "euler_bitarray.h"

typedef char bitarray;
void bitarray_set(bitarray* b, int pos, int bit) {
  char mask = 1 << pos;
  if (!bit) mask = 0;
  b[pos/8] = b[pos/8] | mask;
}

int bitarray_get(bitarray* b, int pos) {
  char c = b[pos/8];
  char mask = 1 << pos;
  return (c & mask) != 0;
}

bitarray* bitarray_alloc(int size) {
  int nb_char = 1 + size / 8;
  bitarray* ba = (bitarray*)malloc(nb_char * sizeof(char));
  for (int i = 0; i < nb_char; i++)
    ba[i] = 0;
  return ba;
}


