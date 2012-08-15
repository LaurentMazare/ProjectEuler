#include<stdio.h>
#include<set>
#include<utility>
#define MAXL 100000000LL

using namespace std;

int main(int argc, char* argv[]) {
  int nb = 0;
  set< long long int > all_pairs;
  for (int m = 0; m < 10000; m++) {
    for (int n = 0; n < m; n++) {
      int a = m * m - n * n;
      int b = 2 * m * n;
      int c = m * m + n * n;
      int aa = a;
      int bb = b;
      int cc = c;
      while (aa + bb + cc < MAXL) {
        aa += a;
        bb += b;
        cc += c;
        int min = aa < bb ? aa: bb;
        int max = aa < bb ? bb: aa;
        long long int p = (long long int)min * MAXL + (long long int)max;
        if (all_pairs.find(p) == all_pairs.end()) {
          all_pairs.insert(p);
          if (cc % (max - min) == 0)
            nb++;
        }
      }
      if (a + b + c >= MAXL)
        break;
    }
  }
  printf("%d\n", nb);
  return 0;
}
