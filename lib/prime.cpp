#include<stdio.h>
#include<algorithm>
using namespace std;
#define maxn 50000009

int noprime[maxn];
int q[maxn], t;
// Linear prime number sieves
void prepare() {
  int i, j;
  for(i=2;i<maxn;i++) {
    if(!noprime[i]) {
      q[++t]=i;
      noprime[i]=i;
    }
    for(j=1;j<=t;j++) {
      if(double(q[j])*i + 1e-9< maxn) {
        noprime[q[j]*i] = q[j];
      } else {
        break;
      }
      if(i%q[j]==0)
        break;
    }
  }
}

pair<int, int> p[maxn];

void make() {
  int i,j,n;
  for(i=1;i<=t;i++) {
    j=0;
    n=q[i]-1;
    while(n%2==0) {
      n/=2;
      j++;
    }
    p[i]=make_pair(j, q[i]);
  }
  sort(&p[1], &p[1+t]);
  j=0;
  for(i=t;i;i--) {
    j++;
    if(j>20) break;
    printf("%d %d %d %d %d\n", p[i].first, p[i].second, (1<<p[i].first), (p[i].second - 1) / (1<<p[i].first), (p[i].second - 1) % (1<<p[i].first));
  }
}
// 45 1231453023109121 35184372088832 35
// 31 75161927681 2147483648 35
// 21 23068673 2097152 11 0
// 20 28311553 1048576 27 0
// 20 26214401 1048576 25 0
// 20 13631489 1048576 13 0
// 20 7340033 1048576 7 0
// 19 40370177 524288 77 0
// 19 37224449 524288 71 0
// 19 36175873 524288 69 0
// 19 29884417 524288 57 0
// 19 21495809 524288 41 0
// 19 14155777 524288 27 0
// 19 5767169 524288 11 0
// 18 42729473 262144 163 0
// 18 41680897 262144 159 0
// 18 38535169 262144 147 0
// 18 35389441 262144 135 0
// 18 33292289 262144 127 0
// 18 27000833 262144 103 0
// 18 22806529 262144 87 0
// 18 16515073 262144 63 0
int main() {
  prepare();
  make();
}
