#include<stdio.h>
#include<set>
#define MAX_P 120000
using namespace std;
typedef long long int lli;

int main(int argc, char* argv[]) {
  int is_torricelli[MAX_P+1];
  set<int>* squares[MAX_P+1];
  for (int i = 0; i <= MAX_P; i++) {
    is_torricelli[i] = 0;
    squares[i] = new set<int>();
  }
  for (lli m = 1; m <= 1000; m++)
    for (lli n = 1; n < m; n++) {
      lli p = 2*m*n + n*n; // Similar to the pythagorean triple generation
      lli q = m*m - n*n;
      for (int k = 1; k*p <= MAX_P && k*q <= MAX_P; k++) {
        squares[k*p]->insert(k*q);
        squares[k*q]->insert(k*p);
      }
    }
  for (int p = 1; p <= MAX_P; p++) {
    set<int>::iterator s_it, s_it2;
    for (s_it = squares[p]->begin(); s_it != squares[p]->end(); ++s_it) {
      int q = *s_it;
      for (s_it2 = squares[q]->begin(); s_it2 != squares[q]->end(); ++s_it2) {
        int r = *s_it2;
        if (p+q+r <= MAX_P && squares[r]->find(p) != squares[r]->end()) is_torricelli[p+q+r] = 1;
      }
    }
  }
  lli total = 0;
  for (int i = 0; i <= MAX_P; i++) if (is_torricelli[i]) total += i;
  printf("%lli\n", total);
  return 0;
}

