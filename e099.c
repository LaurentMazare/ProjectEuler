#include <stdio.h>
#include <math.h>

int main(int argc, char*argv) {
  int index;
  int i=0;
  double current_max = 0;
  FILE*f = fopen("base_exp.txt", "r");
  int i1, i2;
  while (fscanf(f, "%i,%i\n", &i1, &i2)!=EOF) {
    double d1 = i1, d2 = i2;
    double v = d2 * log(d1);
    i++;
    if (current_max < v) {
      current_max = v;
      index = i;
    }
  }
  fclose(f);
  printf("%i\n", index);
  return 0;
}
