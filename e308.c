#include<stdio.h>
typedef long long int lli;

int main(int argc, char* argv[]) {
  lli nb_primes = 0, idx = 0;
  lli i2 = 1, i3 = 0, i5 = 0, i7 = 0, i11 = 0, i13 = 0, i17 = 0, i19 = 0, i23 = 0, i29 = 0;
  while (1) {
    if (!i2 && !i3 && !i13 && !i17 && !i19 && !i23 && !i29 && i11 == 1) {
      // We want to try dividing i5 by i7 in a fast forward way
      if (i5 % i7 != 0) {
        idx += 6*i5 + 2*(1 + i5/i7);
        i7--;
        continue;
      }
    }
    if (i13 > 0 && i7 > 0) {i13--; i7--; i17++;}
    else if (i5 > 0 && i17 > 0) {i5--; i17--; i2++; i3++; i13++;}
    else if (i3 > 0 && i17 > 0) {i3--; i17--; i19++;}
    else if (i2 > 0 && i19 > 0) {i2--; i19--; i23++;}
    else if (i3 > 0 && i11 > 0) {i3--; i11--; i29++;}
    else if (i29 > 0) {i29--; i7++; i11++;}
    else if (i23 > 0) {i23--; i5++; i19++;}
    else if (i19 > 0) {i19--; i7++; i11++;}
    else if (i17 > 0) {i17--;}
    else if (i13 > 0) {i13--; i11++;}
    else if (i11 > 0) {i11--; i13++;}
    else if (i2 > 0) {i2--; i3++; i5++;}
    else if (i7 > 0) {i7--;}
    else {i5++; i11++;}
    idx++;
    if (!i3 && !i5 && !i7 && !i11 && !i13 && !i17 && !i19 && !i23 && !i29) {
      printf("%lli %lli\n", idx, i2);
      if (++nb_primes == 10001) break;
    }
  }
  return 0;
}
