#include<stdio.h>
#include<stdlib.h>
#include "euler_math.h"

int triple_center(int i, int x, char* line_m, char* line, char* line_p) {
  if (!line[i])
    return 0;
  int nb_neighbors = line_p[i] + line_p[i+1];
  if (i > 0)
    nb_neighbors += line[i-1] + line_p[i-1] + line_m[i-1];
  if (i < x-1)
    nb_neighbors += line_m[i] + line[i+1];
  if (i < x-2)
    nb_neighbors += line_m[i+1];
  return (nb_neighbors >= 2);
}

llu s(llu x, int* primes, int nb_primes) {
  llu start = 1 + (x * (x-1LL)) / 2LL;
  char* line_mm = resieve(1 + ((x-3LL) * (x-2LL)) / 2LL, x - 2, primes, nb_primes);
  char* line_m = resieve(1 + ((x-1LL) * (x-2LL)) / 2LL, x - 1, primes, nb_primes);
  char* line = resieve(start, x, primes, nb_primes);
  char* line_p = resieve(1 + ((x+1LL) * x) / 2LL, x + 1, primes, nb_primes);
  char* line_pp = resieve(1 + ((x+1LL) * (x+2LL)) / 2LL, x + 2, primes, nb_primes);
  llu sum = 0;
  for (llu i = 0; i < x; i++) {
    char in_triple = 0;
    if (line[i]) {
      if (triple_center(i, x, line_m, line, line_p) ||
          triple_center(i, x+1, line, line_p, line_pp) ||
          triple_center(i+1, x+1, line, line_p, line_pp))
        in_triple = 1;
      else if (i >= 0 && (triple_center(i-1, x, line_m, line, line_p) ||
                          triple_center(i-1, x-1, line_mm, line_m, line) ||
                          triple_center(i-1, x+1, line, line_p, line_pp)))
        in_triple = 1;
      else if (i < x-1 && (triple_center(i, x-1, line_mm, line_m, line) ||
                           triple_center(i+1, x, line_m, line, line_p)))
        in_triple = 1;
      else if (i < x-2 && triple_center(i+1, x-1, line_mm, line_m, line))
        in_triple = 1;
    }
    if (in_triple)
      sum += start + i;
  }
  return sum;
}

int main(int argc, char* argv[]) {
  int nb_primes;
  int* primes = get_primes(10000000, &nb_primes);
  printf("8: %llu\n", s(8, primes, nb_primes));
//  printf("9: %llu\n", s(9, primes, nb_primes));
  printf("10000: %llu\n", s(10000, primes, nb_primes));
  printf("Result: %llu\n", s(5678027, primes, nb_primes)+s(7208785, primes, nb_primes));
  return 0;
}
