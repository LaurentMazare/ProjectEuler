#include<stdio.h>

typedef long long int lli;
lli center = 1 << 23;

lli quadtree(lli x0, lli y0, lli width) {
  lli dist = center * center;
  lli x1 = x0 + width - 1;
  lli y1 = y0 + width - 1;
  lli x0_2 = (x0 - center) * (x0 - center);
  lli x1_2 = (x1 - center) * (x1 - center);
  lli y0_2 = (y0 - center) * (y0 - center);
  lli y1_2 = (y1 - center) * (y1 - center);
  if (width < (1 << 24) &&
      (x0_2 + y0_2 <= dist) == (x0_2 + y1_2 <= dist) &&
      (x0_2 + y0_2 <= dist) == (x1_2 + y1_2 <= dist) &&
      (x0_2 + y0_2 <= dist) == (x1_2 + y0_2 <= dist))
    return 2;
  lli res = 1;
  lli x_center = x0 + width/2;
  lli y_center = y0 + width/2;
  res += quadtree(x0, y0, width/2);
  res += quadtree(x0, y_center, width/2);
  res += quadtree(x_center, y0, width/2);
  res += quadtree(x_center, y_center, width/2);
  return res;
}

int main(int argc, char* argv[]) {
  printf("%lli\n", quadtree(0, 0, 1 << 24));
  return 0;
}
