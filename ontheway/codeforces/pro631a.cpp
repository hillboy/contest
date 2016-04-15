#include<stdio.h>
typedef long long int LD;

int main() {
  int n,i,j,a=0,b=0;
  LD ans = 0;
  scanf("%d", &n);
  for(i=1;i<=n;i++) {
    scanf("%d", &j);
    a|=j;
  }
  for(i=1;i<=n;i++) {
    scanf("%d", &j);
    b|=j;
  }
  ans=a;
  ans+=b;
  printf("%lld\n", ans);
}
