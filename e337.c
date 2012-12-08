// Use a Fenwick tree to store the sum of the sequences number
// starting from n and above
#include "euler_math.h"
#define MOD_P 100000000
#define MAX_P 20000000

// Initializes a Fenwick tree of given size
int* ft_init(int size) {
  int* ft = malloc(size * sizeof *ft);
  for (int i = 0; i < size; i++) ft[i] = 0;
  return ft;
}

// Add to_add to the k-th element
void add(int k, int to_add, int* ft, int size) {
    for (; k < size; k |= k + 1) ft[k] = (ft[k] + to_add) % MOD_P;
}
 
// Get the sums of element up to index (included)
int get_sum(int idx, int* ft) {
  int res = 0;
  for (; 0 <= idx; idx = (idx&(idx+1)) - 1) res = (res + ft[idx]) % MOD_P;
  return res;
}

int sum_between(int idx1, int idx2, int* ft) {
  return (MOD_P + get_sum(idx2, ft) - get_sum(idx1-1, ft)) % MOD_P;
}
 
int main(int argc, char* argv[]) {
  int* ft = ft_init(MAX_P+1);
  for (int i = MAX_P; i > 6; i--) {
    int phi = phi_int(i);
    int nb_seq = 1 + sum_between(phi+1, i-1, ft);
    add(phi, nb_seq, ft, MAX_P+1);
  }
  printf("%d\n", 1+sum_between(phi_int(6) + 1, 5, ft));
  return 0;
}
