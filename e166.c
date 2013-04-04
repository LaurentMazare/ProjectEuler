#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[]) {
  int nb = 0;

  for (int i0 = 0; i0 < 10; i0++)
    for (int i1 = 0; i1 < 10; i1++)
      for (int i2 = 0; i2 < 10; i2++)
        for (int i3 = 0; i3 < 10; i3++) {
          int sum = i0 + i1 + i2 + i3; // first line
          for (int i4 = 0; i4 < 10; i4++)
            for (int i5 = 0; i5 < 10; i5++)
              for (int i6 = 0; i6 < 10; i6++) {
                int i7 = sum -i4 - i5 - i6; // second line
                if (i7 < 0 || i7 > 9) continue;
                for (int i8 = 0; i8 < 10; i8++) {
                  int i12 = sum - i0 - i4 - i8; // first column
                  if (i12 < 0 || i12 > 9) continue;
                  int i9 = sum - i12 - i3 - i6; // second diag
                  if (i9 < 0 || i9 > 9) continue;
                  for (int i10 = 0; i10 < 10; i10++) {
                    int i11 = sum - i8 - i9 - i10; // third line
                    if (i11 < 0 || i11 > 9) continue;
                    int i13 = sum - i1 - i5 - i9; // second column
                    if (i13 < 0 || i13 > 9) continue;
                    int i14 = sum - i2 - i6 - i10; // third column
                    if (i14 < 0 || i14 > 9) continue;
                    int i15 = sum - i3 - i7 - i11; // fourth column
                    if (i15 < 0 || i15 > 9) continue;
                    if (sum != i12 + i13 + i14 + i15) continue; // fourth line
                    if (sum != i0 + i5 + i10 + i15) continue; // first diag
                    nb++;
                  }
                }
              }
        }
  printf("%i\n", nb);
  return 0;
}
