#include<stdio.h>
#include<stdlib.h>

#define MAX 1000000

int main(int argc, char* argv[]) {
  int* sum_div = (int*)malloc(MAX*sizeof(int));
  char* already_seen = (char*)malloc(MAX*sizeof(char));
  int i;
  int longest_size = -1;
  int longest_elt = 0;
  for (i = 1; i < MAX; i++) { sum_div[i]=0; already_seen[i]=0; }
  for (i = 1; i < MAX; i++) {
    int j = 1;
    int tmp;
    while ((tmp = ++j * i) < MAX) sum_div[tmp] += i;
  }
  for (i = 2; i < MAX; i++) {
    int tmp = sum_div[i];
    int size = 0;
    int j;
    for (j = 1; j < MAX; j++) { already_seen[j]=0; }
    already_seen[i] = 1;
    while (tmp < MAX && !already_seen[tmp]) {
      already_seen[tmp] = 1;
      size++;
      tmp = sum_div[tmp];
    }
    if (longest_size < size && tmp == i) { longest_size = size; longest_elt = i; }
    if (i % 100 == 0) printf("%i %i %i\n", i, longest_size, longest_elt);
  }
  printf("%i (%i)\n", longest_elt, longest_size);

  return 0;
}
