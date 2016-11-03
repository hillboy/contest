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

#define maxn 201000

int i,j,n,m,k;

int p[maxn];

int ans;

int fa[maxn],sum[maxn];

int findfa(int a) {
  if(fa[a]==a)
    return a;
  return fa[a] = findfa(fa[a]);
}

void merge(int a,int b) {
  a=findfa(a);
  b=findfa(b);
  if(a==b)
    return;
  if(sum[a]>sum[b])
    swap(a,b);
  sum[b]+=sum[a];
  fa[a]=b;
}

map<int, int> q[maxn];

int main() {
  scanf("%d %d %d", &n, &m, &k);
  for1tr(i, n) {
    scanf("%d", &p[i]);
    fa[i]=i;
    sum[i]=1;
  }
  forcnt(m) {
    scanf("%d %d", &i, &j);
    merge(i,j);
  }
  for1tr(i,n) {
    j = findfa(i);
    q[j][p[i]]++;
  }
  for1tr(i,n) if(findfa(i) == i) {
    int nowmax=0;
    for(auto& j : q[i]) {
      if(j.second>nowmax)
        nowmax = j.second;
    }
    ans+=sum[i] - nowmax;
  }
  printf("%d\n", ans);
  return 0;
}
