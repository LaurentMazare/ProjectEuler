#include "euler_math.h"

int main(int argc, char* argv[]) {
  int_list** il = get_prime_factors(100);
  for (int i = 1; i <= 100; i++) {
    printf("%d: ", i);
    il_print(il[i]);
  }
  return 0;
}
