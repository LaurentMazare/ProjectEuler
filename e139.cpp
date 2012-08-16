#include<stdio.h>
#include<set>
#include<utility>
#define MAXL 100000000LL

using namespace std;

int main(int argc, char* argv[]) {
  set< long long int > all_pairs;
  for (int m = 1; m < 10000; m++) {
    for (int n = 1; n < m; n++) {
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
        if (cc % (max - min) == 0) {
          long long int p = (long long int)min * MAXL + (long long int)max;
          all_pairs.insert(p);
        }
      }
      if (a + b + c >= MAXL)
        break;
    }
  }
  printf("%d\n", all_pairs.size());
  return 0;
}
