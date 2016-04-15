#include<stdio.h>
#include<algorithm>
#include<map>
using namespace std;
int i,j,n,m;

map<pair<int,int>, int> p;

struct point {
  int a,b;
}q[2011];

bool cmp(const point& a, const point& b) {
  if(a.a==b.a)
    return a.b < b.b;
  return a.a < b.a;
}

long long int ans;

int main() {
  scanf("%d", &n);
  for(i=1;i<=n;i++) {
    scanf("%d %d", &q[i].a, &q[i].b);
  }
  sort(&q[1], &q[1+n], cmp);
  for(i=1;i<=n;i++)
    for(j=i+1;j<=n;j++) {
      pair<int,int> v = make_pair(q[j].a-q[i].a, q[j].b-q[i].b);
      if(p.count(v)) {
        ans+=p[v]++;
      } else {
        p[v]=1;
      }
    }
  printf("%lld\n", ans/2);
  return 0;
}
