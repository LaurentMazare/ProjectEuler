#include<stdio.h>
#include<math.h>

int is_int(double d) {
  return (fabs (d - round(d)) < 1e-12);
}
double sqr(double d) {return d*d;}

int main(int argc, char* argv[]) {
  int n = 2;
  int nb_part = 0;
  int nb_perfect = 0;
  while (1) {
    double root = (sqr(2*n-1)-1.0)/4.0;
    if (is_int(root)) {
      nb_part++;
      if (is_int(log(n)/log(2))) nb_perfect++;
    }
    if (((double)nb_perfect) / nb_part < 1.0/12345.0 - 1e-15) {
      printf("%.0f\n", root);
      break;
    }
    n++;
  }
  return 0;
}
