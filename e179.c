#include<stdio.h>
#include<stdlib.h>
#define MAX 10000000
int main(int argc, char* argv[]) {
  int* nb_divs = (int*)malloc((MAX+1)*sizeof(int));
  int i;
  int nb = 0;
  for (i=2; i<=MAX; i++) {
    int n=0;
    int tmp;
    while ( (tmp = (++n)*i) < MAX + 1) nb_divs[tmp]++;
  }
  for (i=2; i<MAX; i++)
    if (nb_divs[i] == nb_divs[i+1]) nb++;
  printf("%i\n", nb);
  return 0;
}
