#include<set>
#include<stdio.h>
#define MIN(X,Y) ((X) < (Y) ? (X): (Y))
#define MAX(X,Y) ((X) < (Y) ? (Y): (X))
#define MAX_P 100000000
using namespace std;

int gcd(int a, int b) {
  if (b == 0) return a;
  return gcd(b, a%b);
}

int main(int argc, char* argv[]) {
  int total = 0;
  set<pair <int, int> > all;
  for (int mode = 0; mode < 3; mode++) {
    for (int x = 2; x < 14000; x++) {
      int x2 = x * x;
      for (int y = 1; y < x; y++) {
        if (gcd(x, y) != 1) continue; // Yes, Stern-Brocot tree would be better
        int y2 = y * y;
        int a, b, c;
        if (mode == 0) { // Pythagorean triple
          if (x % 2 == y % 2) continue;
          a = x2 + y2;
          b = x2 - y2;
          c = 2 * x * y;
        }
        else if (mode == 1) { // Rectangle with a 60 degree angle
          a = x2 - x * y + y2;
          b = 2 * x * y - y2;
          c = x2 - y2;
        }
        else {
          a = x2 + x * y + y2;
          b = 2 * x * y + y2;
          c = x2 - y2;
        }
        if (a % 3 == 0 && b % 3 == 0 && c % 3 == 0) {
          a /= 3; b /= 3; c /= 3;
        }
        int perim = a + b + c;
        if (perim > 3 * MAX_P) break;
        if (perim > MAX_P) continue;
        pair<int, int> p = pair<int, int>(MIN(b, c), MAX(b, c));
        if (all.find(p) == all.end()) {
          total += MAX_P / perim;
          all.insert(p);
        }
      }
    }
    all.clear();
  }
  printf("%i\n", total);
  return 0;
}
