#include<stdio.h>

#define div 1000000007

int i,j,n,m;

int main() {
  scanf("%d %d", &n, &m);
  long long int T = 1, f=0, lastT;
  for(i=1;i<=n;i++) {
    lastT=T;
    T= ((lastT + lastT - f) % div + div)  * m %div;
    f = (lastT + f * (m-1)) % div;
  }
  printf("%lld\n", T);
  return 0;
}
