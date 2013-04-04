#include<stdio.h>

long long int add(long long int v, int x) {
  if (x == 10)
    return v * 100 + 10;
  return v*10 + x;
}

int main(int argc, char* argv[]) {
  int elem[10];
  long long int max = 0;
  for (elem[0] = 1; elem[0] <= 10; elem[0]++)
    for (elem[1] = 1; elem[1] < 10; elem[1]++) 
      for (elem[2] = 1; elem[2] < 10; elem[2]++)
        for (elem[3] = 1; elem[3] < 10; elem[3]++)
          for (elem[4] = 1; elem[4] < 10; elem[4]++)
            for (elem[5] = 1; elem[5] < 10; elem[5]++) {
              int sum = elem[0] + elem[1] + elem[2];
              elem[6] = sum - elem[2] - elem[3];
              elem[7] = sum - elem[3] - elem[4];
              elem[8] = sum - elem[4] - elem[5];
              elem[9] = sum - elem[5] - elem[1];
              int digits[11];
              int ok = 1;
              if (elem[0] >= elem[6] || elem[0] >= elem[7] || elem[0] >= elem[8] || elem[0] >= elem[9])
                continue;
              for (int i = 1; i <= 10; i++) digits[i] = 0;
              for (int i = 0; i < 10; i++) {
                if (elem[i] < 1 || elem[i] > 10) { ok = 0; break; }
                digits[elem[i]]++;
              }
              if (ok) {
                for (int i = 1; i <= 10; i++)
                  if (digits[i] != 1) { ok = 0; break;}
                for (int i = 1; i <= 5; i++)
                  if (elem[i] == 10) { ok = 0; break;}
                if (ok) {
                  long long int v = 0;
                  v = add(v, elem[0]);
                  v = add(v, elem[1]);
                  v = add(v, elem[2]);
                  v = add(v, elem[6]);
                  v = add(v, elem[2]);
                  v = add(v, elem[3]);
                  v = add(v, elem[7]);
                  v = add(v, elem[3]);
                  v = add(v, elem[4]);
                  v = add(v, elem[8]);
                  v = add(v, elem[4]);
                  v = add(v, elem[5]);
                  v = add(v, elem[9]);
                  v = add(v, elem[5]);
                  v = add(v, elem[1]);
                  if (v > max) max = v;
                }
              }
            }
  printf("%lli\n", max);
  return 0;
}
