#include "euler_math.h"

int main(int argc, char* argv[]) {
  llu limit = 10000000000000000LL;
  int nb_perfect = 0;
  for (llu mm = 1; 1; mm++) {
    llu mm2 = mm * mm;
    if (mm2 > 100000000LL)
      break;
    for (llu nn = 1; nn < mm; nn++) {
      llu nn2 = nn * nn;
      if (mm2 + nn2 > 100000000LL)
        break;
      llu m = mm2 - nn2;
      llu n = 2 * mm * nn;
      llu m2 = m * m;
      llu n2 = n * n;
      llu a = (m2 < n2) ? n2 - m2: m2 - n2;
      llu b = 2 * m * n;
      llu c = m2 + n2;
      if (a + b + c > limit)
        break;
      if ((a % 3 == 0 || b % 3 == 0) && (a % 7 == 0 || b % 7 == 0) && (a % 8 == 0 || b % 8 == 0))
        continue;
      nb_perfect++;
    }
  }
  printf("Found %i triangles.\n", nb_perfect);
  return 0;
}
