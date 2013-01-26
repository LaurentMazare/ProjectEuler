#include<stdio.h>
#include<stdlib.h>
#define MAX(X,Y) ((X) < (Y) ? (Y): (X))

// Tree structure to store both the current max and the values
typedef struct tree {
  int k;
  int v;
  int max;
  struct tree* left;
  struct tree* right;
} tree;

// Create a zero initialized balanced tree
tree* zero_tree(int lo, int hi) {
  int k = (lo + hi) / 2;
  tree* node = (tree*)malloc(sizeof *node);
  node->k = k;
  node->v = node->max = 0;
  node->left = node->right = NULL;
  if (lo < k) node->left = zero_tree(lo, k-1);
  if (k < hi) node->right = zero_tree(k+1, hi);
  return node;
}

int update_tree(tree* t, int y, int acc_max) {
  if (t->k == y) {
    if (t->left != NULL) acc_max = MAX(acc_max, t->left->max);
    t->v = 1 + MAX(t->v, acc_max);
    t->max = MAX(t->max, t->v);
    return t->max;
  }
  int max;
  if (y < t->k) {
    max = update_tree(t->left, y, acc_max);
  }
  else {
    if (t->left != NULL) acc_max = MAX(acc_max, t->left->max);
    max = update_tree(t->right, y, MAX(acc_max, t->v));
  }
  return (t->max = MAX(max, t->max));
}

void free_t(tree* t) {
  if (t->left != NULL) free_t(t->left);
  if (t->right != NULL) free_t(t->right);
  free(t);
}
static int cmp(const void *p1, const void *p2) {
  int* pp1 = (int*)p1;
  int* pp2 = (int*)p2;
  if (*pp1 == *pp2) return (*(pp1+1) - *(pp2+1));
  return *pp1 - *pp2;
}

int s(int n) {
  if (n == 1) return 1;
  int two = 1;
  int three = 1;
  int points[2*(2*n+1)];
  for (int i = 0; i <= 2 * n; i++) {
    points[2*i] = two;
    points[2*i+1] = three;
    two = (2 * two) % n;
    three = (3 * three) % n;
  }
  qsort(points, 2*n+1, 2*sizeof(int), cmp);
  tree* root = zero_tree(0, n-1);
  for (int i = 0; i <= 2 * n; i++) {
    if (i > 0 && points[2*i] == points[2*(i-1)] && points[2*i+1] == points[2*i-1]) continue;
    update_tree(root, points[2*i+1], 0);
  }
  int res = root->max;
  free_t(root);
  return res;
}

int main(int argc, char* argv[]) {
  int total = 0;
  for (int k = 1; k <= 30; k++) {int r = s(k*k*k*k*k); printf("%d %d\n", k, r); total += r;}
  printf("%d\n", total);
  return 0;
}
