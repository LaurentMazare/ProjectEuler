#include<stdio.h>
#include<set>
#include<utility>

using namespace std;
typedef unsigned long long int llu;

llu gcd(llu a, llu b) {
while (b != 0) {
  llu t = b;
  b = a % b;
  a = t;
}
return a;
}

int main(int argc, char* argv[]) {
  set< pair<llu, llu> > all[20];
  set< pair<llu, llu> > all_bis;

  all[1].insert(make_pair(1, 1));
  all_bis.insert(make_pair(1, 1));
  for (int i = 2; i < 20; i++) {
    for (int j = 1; j < i/2 + 1; j++) {
      set< pair<llu, llu> >::const_iterator sit1(all[j].begin()), send1(all[j].end());
      for(; sit1!=send1; ++sit1) {
        set< pair<llu, llu> >::const_iterator sit2(all[i-j].begin()), send2(all[i-j].end());
        for(; sit2!=send2; ++sit2) {
          llu den = sit1->first * sit2->second + sit2->first * sit1->second;
          llu num = sit1->second * sit2->second;
          llu g = gcd(den, num);
          all[i].insert(make_pair(den / g, num / g));
          all_bis.insert(make_pair(den / g, num / g));
          if (i == 3)
            printf("%llu %llu\n", den/g, num/g);
          den = sit1->first * sit2->first;
          num = sit1->first * sit2->second + sit1->second * sit2->first;
          g = gcd(den, num);
          all[i].insert(make_pair(den / g, num / g));
          all_bis.insert(make_pair(den / g, num / g));
          if (i == 3)
            printf("%llu %llu\n", den/g, num/g);
        }
      }
    }
    printf("%d %d %llu\n", i, all[i].size(), all_bis.size());
  }
  return 0;
}
