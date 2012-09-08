#include "euler_math.h"
#define MAXL 1000000
#define MAXALPHA 21
#define MAXBETA 15

int pow_int(int x, int n) {
  if (n == 0) return 1;
  if (n == 1) return x;
  if (n % 2 == 0) {
    int tmp = pow_int(x, n/2);
    return tmp*tmp;
  }
  return x * pow_int(x, n-1);
}

char*** cache;
int aux(int x, int alpha, int beta) {
  if (x == 0) return 1;
  int two_alpha = 1 << alpha;
  if (two_alpha > x) return 0;
  if (cache[x][alpha][beta] != -1)
    return cache[x][alpha][beta];
  int res = aux(x, alpha+1, beta);
  if (res < 2)
    for (int i = 0; i <= beta; i++) {
      int s = two_alpha * pow_int(3, i);
      if (s > x) break;
      res += aux(x - s, alpha + 1, i - 1);
      if (res >= 2) break;
    }
  res = res > 2 ? 2: res;
  cache[x][alpha][beta] = res;
  return res;
}

int p(int x) {
  return aux(x, 0, MAXBETA-1);
}

int main(int argc, char* argv[]) {
  int nb_primes;
  int* primes = get_primes(MAXL, &nb_primes);
  cache = malloc(MAXL * sizeof(char**));
  for (int i = 0; i < MAXL; i++) {
    cache[i] = malloc(MAXALPHA * sizeof(char*));
    for (int j = 0; j < MAXALPHA; j++) {
      cache[i][j] = malloc(MAXBETA * sizeof(char));
      for (int k = 0; k < MAXBETA; k++) cache[i][j][k] = -1;
    }
  }
  printf("%d\n", cache[5][0][15]);
  printf("%d\n", p(17));
  long long int sum = 0;
  for (int i = 0; i < nb_primes; i++)
    if (p(primes[i]) == 1) sum += primes[i];
  printf("%lli\n", sum);
  return 0;
}
