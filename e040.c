#include<stdio.h>

int main(int argc, char* argv[]) {
  int digits[2000000];
  int tmp_d[10];
  int nb_d;
  int nb_digits = 0;
  int n = 0;
  while (1) {
    int tmp = ++n;
    nb_d=0;
    while (tmp!=0) {tmp_d[nb_d++]=tmp%10;tmp/=10;}
    for(;nb_d!=0;nb_d--) digits[nb_digits++]=tmp_d[nb_d-1];
    if (nb_digits>=1000000) break;
  }
  printf("%i\n",digits[0]*digits[9]*digits[99]*digits[999]*digits[9999]*digits[99999]*digits[999999]);
  return 0;
}
