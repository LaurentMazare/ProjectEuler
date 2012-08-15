#include<stdio.h>
#include<set>
#include<utility>

using namespace std;

int main(int argc, char* argv[]) {
  int nb = 0;
  set< pair< int, int > > all_pairs;
  for (int m = 0; m < 10000; m++) {
    for (int n = 0; n < m; n++) {
      int a = m * m - n * n;
      int b = 2 * m * n;
      int c = m * m + n * n;
      int aa = a;
      int bb = b;
      int cc = c;
      while (aa + bb + cc < 100000000) {
        aa += a;
        bb += b;
        cc += c;
        int min = aa < bb ? aa: bb;
        int max = aa < bb ? bb: aa;
        pair< int, int > p = make_pair(min, max);
        if (all_pairs.find(p) == all_pairs.end()) {
          all_pairs.insert(make_pair(min, max));
          if (cc % (max - min) == 0)
            nb++;
        }
      }
    }
  }
  printf("%d\n", nb);
  return 0;
}
