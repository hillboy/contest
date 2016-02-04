#include<stdio.h>
#include<algorithm>
using namespace std;
#define maxn 10000000
typedef long long int LD;


LD A, B;

LD p[maxn], sum[maxn];

int i,j,n,m;

// returns area * 2
double area2TOa(LD a) {
  int i;
  LD nowleft = 0, nowright;
  double ans = 0;
  for(i=1;i<=n;i++) {
    nowright = nowleft + p[i];
    if(a>=nowleft && a <= nowright) {
      ans+=(a-nowleft)*(a-nowleft);
      return ans;
    }
    ans+=p[i]*p[i];
    nowleft +=  p[i];
  }
  return ans;
}

LD totalArea(LD a) {
  return a/sum[n] * area2TOa(sum[n]) + area2TOa(a%sum[n]);
}

int main() {
  int ii,nn;
  scanf("%d", &nn);
  for(ii=1;ii<=nn;ii++) {
    printf("Case #%d: ", ii);
    scanf("%d %lld %lld", &n, &A, &B);
    for(i=1;i<=n;i++) {
      scanf("%lld", &p[i]);
      sum[i] = sum[i-1]+p[i];
    }
    double ans = totalArea(B) - totalArea(A);
    ans /= (B-A) * 2;
    printf("%.9lf\n", ans);
  }
  
  return 0;
}
