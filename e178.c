#include<stdio.h>
#include<stdlib.h>

long long int* cache;
long long int f(int first_digit, int nb_digits, int mask) {
  int this_digit = 1 << first_digit;
  if (nb_digits == 1) {
    if (mask == 0 || mask == this_digit) return 1;
    else return 0;
  }
  int key = first_digit + 10 * nb_digits + 1000 * mask;
  if (cache[key] != -1) return cache[key];
  long long int res = 0;
  if (mask & this_digit)
    mask -= this_digit;
  if (first_digit > 0)
    res += f(first_digit-1, nb_digits-1, mask);
  if (first_digit < 9)
    res += f(first_digit+1, nb_digits-1, mask);
  cache[key] = res;
  return res;
}

int main(int argc, char* argv[]) {
  int cache_size = 10000000;
  cache = (long long int*)malloc(sizeof(long long int) * cache_size);
  for (int i = 0; i < cache_size; i++) cache[i] = -1;
  int digits = (1 << 10) - 1;
  long long int result = 0;
  for (int l = 10; l <= 40; l++)
    for (int i = 1; i < 10; i++) {
      long long int x = f(i, l, digits);
      result += x;
    }
  printf("%lli\n", result);
  return 0;
}
