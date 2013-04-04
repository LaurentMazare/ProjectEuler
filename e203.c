#include<stdio.h>
#include<math.h>
long long numbers[10000];
int nb = 0;

int square_free(long long i) {
  long long j = 0;
  long long n = (int)sqrt(i);
  for (j = 2; j <= n; j++) {
    if (i % (j*j) == 0) return 0;
  }
  return 1;
}


void add(long long l) {
  int i;
  for (i=0;i<nb;i++) if(numbers[i]==l) return;
  numbers[nb++]=l;
}

int main(int argc, char* argv[]) {
  long long row[100], previous_row[100];
  int current_row;
  int i;
  long long sum = 0;
  add(1);
  for (current_row=1;current_row<=51;current_row++) {
    row[0]=1;
    row[current_row-1]=1;
    for (i=1;i<current_row-1;i++) {
      row[i]=previous_row[i-1]+previous_row[i];
      add(row[i]);
    }
    for (i=0;i<current_row;i++) previous_row[i]=row[i];
  }
  for (i=0;i<nb;i++) if (square_free(numbers[i])) sum+=numbers[i];
  printf("%lli\n", sum);
  return 0;
}

