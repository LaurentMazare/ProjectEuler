#include<stdio.h>
#include<stdlib.h>

#define MAX 10000000

int nb_digits(int x) {
  int res = 0;
  while (x != 0) { x /= 10; res++; }
  return res;
}

int main(int argc, char* argv[]) {
  char* is_prime =(char*)malloc(MAX*sizeof(char));
  int nb_primes = 0;
  int perms[10];
  for (int i = 2; i < MAX; i++) is_prime[i] = 1;
  for (int i = 2; i < MAX; i++)
    if (is_prime[i]) {
      int j = 1;
      int tmp;
      nb_primes++;
      while ((tmp = ++j * i) < MAX) is_prime[tmp] = 0;
  }
  int* primes = (int*)malloc(nb_primes*sizeof(int));
  nb_primes = 0;
  for (int i = 2; i < MAX; i++)
    if (is_prime[i])
      primes[nb_primes++] = i;
  for (int i = 0; i < nb_primes; i++) {
    int p = primes[i];
    int nb = nb_digits(p);
    int two = 1 << (nb - 1);
    for(int j = 1; j < two; j++) {
      int perm = 0;
      for(int k = 0; k < 10; k++) {
        int generated = 0;
        int ten = 1;
        int pp = p;
        int jj = j;
        while(pp!=0) {
          int digits = pp % 10;
          if (jj % 2 == 0 ) // && pp >= 10)
            digits = k;
          generated = generated + digits * ten;
          pp /= 10;
          ten *= 10;
          jj /= 2;
        }
        if (is_prime[generated]) perms[perm++] = generated;
      }
      if (perm == 8 && nb_digits(perms[0]) == nb_digits(perms[1])) {
        printf("%i\n", perms[0]);
        return 0;
      }
    }
  }
  return 0;
}
