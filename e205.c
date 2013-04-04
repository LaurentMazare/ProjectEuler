#include <stdio.h>

int main(int argc, char* argv[]) {
  int p1, p2, p3, p4, p5, p6, p7, p8, p9;
  int c1, c2, c3, c4, c5, c6;
  long long total = 0;
  long long win = 0;
  double prob;
  for (p1 = 1; p1 <= 4; p1++)
  for (p2 = 1; p2 <= 4; p2++)
  for (p3 = 1; p3 <= 4; p3++)
  for (p4 = 1; p4 <= 4; p4++)
  for (p5 = 1; p5 <= 4; p5++)
  for (p6 = 1; p6 <= 4; p6++)
  for (p7 = 1; p7 <= 4; p7++)
  for (p8 = 1; p8 <= 4; p8++)
  for (p9 = 1; p9 <= 4; p9++)
  for (c1 = 1; c1 <= 6; c1++)
  for (c2 = 1; c2 <= 6; c2++)
  for (c3 = 1; c3 <= 6; c3++)
  for (c4 = 1; c4 <= 6; c4++)
  for (c5 = 1; c5 <= 6; c5++)
  for (c6 = 1; c6 <= 6; c6++) {
    total++;
    if (p1+p2+p3+p4+p5+p6+p7+p8+p9>c1+c2+c3+c4+c5+c6) win++;
  }
  prob=win;
  prob/=total;
  printf("%.7f\n", prob);
  return 0;
}

