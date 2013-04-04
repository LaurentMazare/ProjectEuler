#include<stdio.h>
#include<stdlib.h>

// See http://fr.wikipedia.org/wiki/Fonction_partage_d'un_entier
#define SIZE 1000000
#define MOD 1000000
int main(int argc, char* argv[]) {
  int* p = (int*)malloc(SIZE*sizeof(int));
  int n;
  p[0]=1;
  for(n = 1; n < SIZE; n++) {
    int k = 1;
    int sum = 0;
    while(1) {
      int index = n - (k * (3 * k - 1) ) / 2;
      int sign = 1;
      if (k % 2 == 0) sign = -1;
      if (index < 0 )
        break;
      sum = (sum + MOD + sign * p[index]) % MOD;
      k++;
    }
    k = -1;
     while(1) {
      int index = n - (k * (3 * k - 1) ) / 2;
      int sign = 1;
      if (k % 2 == 0) sign = -1;
      if (index < 0 )
        break;
      sum = (sum + MOD + sign * p[index]) % MOD;
      k--;
    }
    p[n] = sum;
    if (sum == 0) {
      printf("%i\n", n);
      break;
    }
  }
  return 0;
}

