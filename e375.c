#include "euler_math.h"
#define MAX_I 2000000000
// Blum Blum Shub RNG
lli current_s = 290797;
int next_s() {
  return (int)(current_s = (current_s * current_s) % 50515093);
}

// We keep two arrays, prev_min and prev_index
// prev_min: elements S_k such that there is no j between k and i 
// for which S_i is lower than S_k
// prev_index: related indexes in S (e.g. S_k -> k)
// E.g. if S = [6, 5, 12, 7], prev_min = [5, 7], prev_index = [1, 3]
int main(int argc, char* argv[]) {
  int prev_min[10000];
  int prev_index[10000];
  int nb_min = 0;
  lli res = 0;
  for (int i = 1; i <= MAX_I; i++) {
    int s = next_s();
    lli p_min = s;
    int p_index = i;
    for (int k = nb_min-1; k >= 0; k--) {
      if (prev_min[k] < s) {
        res += p_min * (p_index - prev_index[k]);
        p_index = prev_index[k];
        p_min = prev_min[k];
      }
      else nb_min--;
    }
    res += p_min * p_index;
    prev_min[nb_min] = s;
    prev_index[nb_min++] = i;
  }
  printf("Found %d minimums.\nM[%d] = %lli\n", nb_min, MAX_I, res);
  return 0;
}
