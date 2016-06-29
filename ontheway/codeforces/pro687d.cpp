#include<stdio.h>

#include<string.h>
#include<algorithm>
#include<map>
#include<set>
#include<vector>
#include<map>
using namespace std;

#define maxn 1010

#define forlr(x,l,r) for(x=l;x<(int)r;++x)
#define for1(x,y) forlr(x,0,y)
#define forn(x) for1(x,n)

int edges[maxn*maxn][3];

int i,j,n,m,q;

int L, R;

map<pair<int, int>, int> ans;

bool color[maxn];
int fa[maxn],sum[maxn];

struct Edge {
 int a, b, w, id;
} ee[maxn*maxn];

bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
  return a.second < b.second;
}
bool cmp2(const Edge& a, const Edge& b) {
  return a.w > b.w;
}

int findfa(int a) {
  if(a==fa[a])
    return a;
  int ans = findfa(fa[a]);
  color[a]=color[a]^color[fa[a]];
  return fa[a]=ans;
}

bool merge(int a, int b) {
  int aa=findfa(a), bb=findfa(b);
  if(aa==bb) {
    if(color[a]==color[b])
      return false;
    return true;
  }
  if(sum[aa]>sum[bb]) {
    swap(aa,bb);
  }
  fa[aa]=bb;
  if (color[a]==color[b])
    color[aa]=!color[aa];
  sum[bb]+=sum[aa];
  return true;
}


int make() {
  forlr(i, 1, n+1) {
    fa[i]=i;
    sum[i]=1;
    color[i]=0;
  }
  int ans = -1;
  for1(i,m) {
    if(ee[i].id >= L && ee[i].id <= R) {
      if(!merge(ee[i].a, ee[i].b)) {
        ans = ee[i].w;
        return ans;
      }
    }
  }
  return ans;
}

int main() {
  scanf("%d %d %d", &n, &m, &q);
  for1(i, m) {
    scanf("%d %d %d", &edges[i][0], &edges[i][1], &edges[i][2]);
    ee[i].a = edges[i][0];
    ee[i].b = edges[i][1];
    ee[i].w = edges[i][2];
    ee[i].id = i+1;
  }
  sort(ee, ee+m, cmp2);
  while(q--) {
    scanf("%d %d", &L, &R);
    if(!ans.count(make_pair(L, R))) {
      ans[make_pair(L,R)] = make();
    }
    printf("%d\n", ans[make_pair(L,R)]);
  }
  return 0;
}
