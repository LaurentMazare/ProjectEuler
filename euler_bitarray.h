#ifndef __EULER_BITARRAY_H__
#define __EULER_BITARRAY_H__
#include<stdio.h>
#include<stdlib.h>

/* Very naive bitarray library using chars */
typedef char bitarray;

/* bitarray_set(ba, p, b) sets the bit from ba at
 * position p to b (either 0 or 1). */
void bitarray_set(bitarray*, int, int);

/* bitarray_get(pa, p) returns the bit from ba at
 * position p. */
int bitarray_get(bitarray*, int);

/* bitarray_alloc(s) allocates a new bitarray of
 * size s initialized to 0.*/
bitarray* bitarray_alloc(int);

#endif
