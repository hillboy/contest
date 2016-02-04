#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;
#define maxn 2010000
typedef long long int LD;

#define div 1000000007

LD sqr(LD a) {
  return a*a%div;
}

LD mul(LD a, LD b) {
  return a*b%div;
}

LD pl(LD a, LD b) {
  return (a+b) % div;
}

void fx(LD& a) {
  a%=div;
}


struct point {
  LD ans;
  LD n;
  LD sum;
  LD sqsum;
  LD h;
  LD lastpos;
  void update_sqsum(LD dis) {
      sqsum += mul(n, sqr(dis));
      fx(sqsum);
      sqsum += mul(2, mul(sum, dis));
      fx(sqsum);
  }
  void update_sum(LD dis) {
    sum += mul(dis, n);
    fx(sum);
  }
  void update(LD dis) {
    update_sqsum(dis);
    update_sum(dis);
    ans += sqsum;
    lastpos += dis;
    n++;
    fx(ans);
  }
} p[maxn];

pair<int, int> ps[maxn];

int i,j,n,m,t;

LD ans;

void make() {
  t=0;
  LD dis;
  ans=0;
  for(i=0;i<n;i++) {
    if(t==0 || p[t-1].h > ps[i].second) {
      p[t].ans=0;
      p[t].n=1;
      p[t].sum=0;
      p[t].sqsum=0;
      p[t].h=ps[i].second;
      p[t].lastpos=ps[i].first;
      t++;
    } else if(p[t-1].h == ps[i].second) {
      dis= ps[i].first - p[t-1].lastpos;
      p[t-1].update(dis);
    } else {
      while(t && p[t-1].h < ps[i].second) {
        t--;
        ans+=p[t].ans;
        fx(ans);
      }
      i--;
    }
  }
  while(t) {
    t--;
    ans+=p[t].ans;
    fx(ans);
  }
}

int main() {
  int ii,nn;
  scanf("%d", &nn);
  int a,b;
  for(ii=1;ii<=nn;ii++) {
    printf("Case #%d: ", ii);
    scanf("%d", &n);
    for(i=0;i<n;i++) {
      scanf("%d %d", &a, &b);
      ps[i]=make_pair(a,b);
    }
    sort(ps, ps+n);
    make();
    printf("%lld\n", ans);
  }
  return 0;
}
