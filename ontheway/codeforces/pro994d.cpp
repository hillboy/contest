#include<stdio.h>
#include<algorithm>
using namespace std;

int i,j,n,m;

#define maxn 100

struct point {
  int a,b;
  bool possible, knows;
  int knowsN;
  void input() {
    scanf("%d %d",&a, &b);
    if(a>b)
      swap(a,b);
  }
}p[maxn], q[maxn];

int main() {
  scanf("%d %d",&n, &m);
  for(i=1;i<=n;i++) {
    p[i].input();
  }
  for(i=1;i<=m;i++) {
    q[i].input();
  }
  for(i=1;i<=n;i++) {
    bool hasA = false, hasB = false;
    for(j=1;j<=m;j++) {
      if(p[i].a==q[j].a && p[i].b == q[j].b)
        continue;
      if(p[i].a == q[j].a || p[i].a == q[j].b)
        hasA = true;
      if(p[i].b == q[j].a || p[i].b == q[j].b)
        hasB = true;
    }
    if (hasA && hasB) {
      p[i].possible = true;
      printf("-1\n");
      return 0;
    } else
    if (hasA || hasB) {
      p[i].knows = true;
      if(hasA)
        p[i].knowsN = p[i].a;
      if(hasB)
        p[i].knowsN = p[i].b;
    }
  }
  for(i=1;i<=m;i++) {
    bool hasA = false, hasB = false;
    for(j=1;j<=n;j++) {
      if(q[i].a==p[j].a && q[i].b == p[j].b)
        continue;
      if(q[i].a == p[j].a || q[i].a == p[j].b)
        hasA = true;
      if(q[i].b == p[j].a || q[i].b == p[j].b)
        hasB = true;
    }
    if (hasA && hasB) {
      q[i].possible = true;
      printf("-1\n");
      return 0;
    } else
    if (hasA || hasB) {
      q[i].knows = true;
      if(hasA)
        q[i].knowsN = q[i].a;
      if(hasB)
        q[i].knowsN = q[i].b;
    }
  }
  int ans = -1;
  bool hasAns = true;
  bool hasP = false, hasQ = false;
  for(i=1;i<=n;i++) if(p[i].knows) {
    hasP = true;
    if(ans<0)
      ans=p[i].knowsN;
    else if (ans != p[i].knowsN) {
      hasAns = false;
    }
  }
  for(i=1;i<=m;i++) if(q[i].knows) {
    hasQ = true;
    if(ans<0)
      ans=q[i].knowsN;
    else if (ans != q[i].knowsN) {
      hasAns = false;
    }
  }
  if(hasAns) {
    printf("%d\n", ans);
    return 0;
  }
  if(hasP && hasQ) {
    printf("0\n");
    return 0;
  }
  printf("-1\n");
  return 0;
}
