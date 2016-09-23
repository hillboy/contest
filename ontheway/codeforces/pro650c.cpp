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

int i,j,n,m;

vector<pair<int, int> > p;

#define maxn 1000100

int x[maxn],y[maxn], lastx[maxn], lasty[maxn];

map<pair<int, int>, int> ans;

int fa[maxn], sum[maxn];

int findfa(int a) {
  if(fa[a]==a)
    return a;
  return fa[a]=findfa(fa[a]);
}

bool merge(int a,int b) {
  a=findfa(a),b=findfa(b);
  if(a==b)
    return false;
  if(sum[a]>sum[b])
    swap(a,b);
  sum[b]+=sum[a];
  fa[a]=b;
  return true;
}

int encode(int a, int b) {
  return (a-1)*m+b;
}

void decode(int now, int&a, int&b) {
  a=(now-1)/m+1;
  b=(now-1)%m+1;
}

int color[maxn];

int mymax(int a, int b) {
  return a>b?a:b;
}

int main() {
  scanf("%d %d", &n, &m);
  int now;
  for1tr(i, n) {
    for1tr(j, m) {
      scanf("%d", &now);
      p.push_back(make_pair(now, encode(i,j)));
    }
  }
  for1tr(i,n*m) {
    sum[i]=1;
    fa[i]=i;
  }
  sort(p.begin(), p.end());
  int a,b;
  for (auto& ii : p) {
    decode(ii.second, a,b);
    if(x[a] && lastx[a] ==ii.first) {
      merge(x[a], ii.second);
    } else {
      x[a]=ii.second;
      lastx[a] = ii.first;
    }
    if(y[b] && lasty[b] ==ii.first) {
      merge(y[b], ii.second);
    } else {
      y[b] = ii.second;
      lasty[b] = ii.first;
    }
  }
  mymemset(lastx, 0);
  mymemset(lasty, 0);
  mymemset(x, 0);
  mymemset(y, 0);
  for (auto& ii : p) {
    decode(ii.second, a,b);
    if(x[a] && lastx[a] < ii.first) {
      color[findfa(ii.second)] = mymax(
          color[findfa(ii.second)],
          color[findfa(x[a])] + 1);

    }
    x[a]=ii.second;
    lastx[a] = ii.first;

    if(y[b] && lasty[b] < ii.first) {
      color[findfa(ii.second)] = mymax(
          color[findfa(ii.second)],
          color[findfa(y[b])] + 1);
    } 
    y[b] = ii.second;
    lasty[b] = ii.first;
  }
  for1tr(i,n) {
    for1tr(j,m) {
      printf("%d ", color[findfa(encode(i,j))]+1);
    }
    printf("\n");
  }
  return 0;
}
