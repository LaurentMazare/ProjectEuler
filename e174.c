#include<stdio.h>
#include<math.h>
#define MAX 1000000
int main(int argc, char* argv[]) {
  int nb_squares[MAX+1];
  int i;
  int out;
  for (i=1;i<=MAX;i++) nb_squares[i]=0;
  for (out=3;out<=2+MAX/4;out++) {
    int width=1;
    while (1) {
      int in = out-2*width;
      int nb = out*out-in*in;
      if (nb>MAX || in <= 0) break;
      nb_squares[nb]++;
      width++;
    }
  }
  i=0;
  out=0;
  for(i=1;i<=MAX;i++)
    if (nb_squares[i]>=1 && nb_squares[i]<=10) out++;
  printf("%i\n", out);

  return 0;
}
