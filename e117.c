#include <stdio.h>
long long cache[51];
long long nb_rec(int len) {
  long long res = 0;
  int i;
  if (cache[len] != -1) return cache[len];
  for (i=0; i<=len-2; i++) {
    res += 1 + nb_rec(len - i - 2);
    if (i!=len-2) {
      res += 1 + nb_rec(len-i-3);
      if (i!=len-3)
        res += 1 + nb_rec(len-i-4);
    }
  }
  cache[len] = res;
  return res;
}

int main(int argc, char* argv[]) {
  int i;
  for (i=0;i<51;i++) cache[i]= -1;
  printf("%lli\n", nb_rec(50)+1);
  return 0;
}
