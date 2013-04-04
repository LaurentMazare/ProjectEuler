#include <stdio.h>
int buffer[10];
int cache[10000];
int cache_size = 0;
void add_cache(int n) {cache[cache_size++]=n;}
int in_cache(int n) {int i; for(i=0; i<cache_size; i++) {if (n == cache[i]) return 1;} return 0;}
int is_palindromic(int x) {
  int i = 0;
  int j;
  while (x != 0) {
    buffer[i++] = x % 10;
    x /= 10;
  }
  for (j=0; j < i; j++) {
    if (buffer[j] != buffer[i-j-1]) return 0;
  }
  return 1;
}

int main(int argc, char* argv[]) {
  int low, up;
  long long result = 0;
  for (low = 1; low < 10000; low++) {
    int sum = low * low;
    for (up = low + 1; up < 10000; up++) {
      sum += up * up;
      if (sum > 10000 * 10000) break;
      if (!in_cache(sum) && is_palindromic(sum)) {
        add_cache(sum);
        result += sum;
      }
    }
  }
  printf("%lli\n", result);
  return 0;
}
