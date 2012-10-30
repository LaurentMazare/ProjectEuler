/* It seems that for p prime, F_n contains p^2 only for
 * n = k*p*z(p) where z(p) is the smallest k such that
 * p divides F_k.
 * Hence for all prime p, compute z(p) and sieve the k*z(p) */
#include "euler_math.h"
#include "euler_bitarray.h"
#define MAXP 100000000

int main(int argc, char* argv[]) {
  int nb_primes;
  int* primes = get_primes(MAXP, &nb_primes);
  bitarray* ba = bitarray_alloc(MAXP*2);
  
  for (int idx = 0; idx < nb_primes; idx++) {
    int p = primes[idx];
    int prev_f = 1;
    int f = 1;
    int z = 2;
    while (1) {
      z++;
      int tmp = f;
      f = (prev_f + f) % p;
      prev_f = tmp;
      if (z * p > MAXP*2) break;
      if (f == 0) break;
    }
    if (f == 0) {
      int zp = z * p;
      int k = zp;
      while (k < MAXP*2) { bitarray_set(ba, k, 1); k += zp; }
    }
  }
  int nb = 0;
  int f_index = 1;
  for (f_index = 1; f_index < MAXP*2; f_index++) {
    if (!bitarray_get(ba, f_index)) nb++;
    if (nb == MAXP) break;
  }
  printf("Index: %d\n", f_index);
  lli prev_f = 1;
  lli f = 1;
  double prev_fd = 1.0;
  double fd = 1.0;
  int nb_digits = 0;
  for (int i = 2; i < f_index; i++) {
    lli tmp = f;
    double tmp_d = fd;
    f = (f + prev_f) % 10000000000000000LL;
    fd += prev_fd;
    prev_f = tmp;
    prev_fd = tmp_d;
    while (fd >= 10.0) { nb_digits++; fd /= 10.0; prev_fd /= 10.0; }
  }
  printf("%lli,%.1fe%d\n", f, fd, nb_digits);
  return 0;
}
