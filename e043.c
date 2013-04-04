#include<stdio.h>

int is_pan(long long int l) {
  int digits[10];
  int i;
  for (i=0; i<10; i++) digits[i] = 0;
  while (l != 0) {digits[l%10]++; l/=10;}
  for (i=0; i<10; i++) if (digits[i]!=1) return 0;
  return 1;
}

int main(int argc, char* argv[]) {
  int d8d9d10;
  long long int sum = 0;
  int d[10];
  for (d8d9d10 = 17; d8d9d10 < 1000; d8d9d10 += 17) {
    d[9] = d8d9d10 % 10;
    d[8] = (d8d9d10 / 10) % 10;
    d[7] = (d8d9d10 / 100) % 10;
    for (d[6] = 0; d[6] < 10; d[6]++)
      if ((100*d[6]+10*d[7]+d[8]) % 13 == 0)
        for (d[5] = 0; d[5] < 10; d[5]++)
          if ((100*d[5]+10*d[6]+d[7]) % 11 == 0)
            for (d[4] = 0; d[4] < 10; d[4]++)
              if ((100*d[4]+10*d[5]+d[6]) % 7 == 0)
                for (d[3] = 0; d[3] < 10; d[3]++)
                  if ((100*d[3]+10*d[4]+d[5]) % 5 == 0)
                    for (d[2] = 0; d[2] < 10; d[2]++)
                      if ((100*d[2]+10*d[3]+d[4]) % 3 == 0)
                        for (d[1] = 0; d[1] < 10; d[1]++)
                          if ((100*d[1]+10*d[2]+d[3]) % 2 == 0)
                            for (d[0] = 0; d[0] < 10; d[0]++)
                            {
                              int i;
                              long long int l = 0;
                              for (i=0; i<10; i++) l = d[i] + l * 10; 
                              if (is_pan(l)) {
                                sum += l;
                              }
                            }
  }
  printf("%lli\n", sum);
  return 0;
}
