#include<stdio.h>
#include<math.h>

int main(int argc, char* argv[]) {
  int a,b,c;
  int sum=0;
  a=1;
  while(sum<1000000) {
    for(b=1;b<=a;b++)
      for(c=1;c<=b;c++) {
        int b_c=b+c;
        double d=sqrt(a*a+b_c*b_c);
        if (floor(d)==d) sum++;
      }
    a++;
  }
  printf("%i %i\n",a-1,sum);
  return 0;
}

