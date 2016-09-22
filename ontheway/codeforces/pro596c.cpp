#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>
using namespace std;

#define forlr(i,l,r) for(i=l;i<r;i++)
#define forrl(i,r,l) for(i=r-1;i>=l;i--)
#define for0r(i,r) forlr(i,0,r)

#define forltr(i,l,r) for(i=l;i<=r;i++)
#define for1tr(i,r) forltr(i,1,r)
#define forrtl(i,r,l) for(i=r;i>=l;i--)

#define forcnt(n) for(int cnt=n; cnt; cnt--)

#define X(x) (x).first
#define Y(x) (x).second

#define mymemset(x, val) memset(x, val, sizeof(x))
#define sz(x) ((int)x.size())

typedef long long int LD;
#define maxn 200100

int i,j,n,m;

struct point {
  int a,b;
}p[maxn];

pair<int, int> q[maxn];

int ans[maxn][2];

map<pair<int, int>, int> id;


bool cmp(const point& a, const point& b) {
  if(a.b-a.a != b.b-b.a) {
    return a.b-a.a < b.b-b.a;
  }
  if(a.a!=b.a)
    return a.a<b.a;
  return a.b<b.b;
}

int main() {
  scanf("%d", &n);
  for1tr(i,n) {
    scanf("%d %d", &p[i].a, &p[i].b);
  }
  sort(&p[1], &p[1+n],cmp);
  for1tr(i,n) {
    scanf("%d", &q[i].first);
    q[i].second = i;
  }
  sort(&q[1], &q[n+1]);
  for1tr(i,n) {
    if (q[i].first != p[i].b - p[i].a) {
      printf("NO\n");
      return 0;
    }
    ans[q[i].second][0]=p[i].a;
    ans[q[i].second][1]=p[i].b;
    id[make_pair(p[i].a, p[i].b)] = q[i].second;
  }
  for1tr(i, n) {
    j = id[make_pair(p[i].a, p[i].b)];

    if(p[i].a>0) {
      if(id[make_pair(p[i].a-1, p[i].b)] > j) {
        printf("NO\n");
        return 0;
      }
    }
    if(p[i].b>0) {
      if(id[make_pair(p[i].a, p[i].b-1)] > j) {
        printf("NO\n");
        return 0;
      }
    }
  }

  printf("YES\n");
  for1tr(i,n) {
    printf("%d %d\n", ans[i][0], ans[i][1]);
  }
  return 0;
}
