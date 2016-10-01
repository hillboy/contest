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
#define maxn 100100

int i,j,n;

LD m;

int p[maxn];
int q[maxn];

int fa[maxn],sum[maxn];
LD sum2[maxn];

int findfa(int a) {
  if(a==fa[a])
    return a;
  return fa[a]=findfa(fa[a]);
}

bool merge(int a,int b) {
  a = findfa(a), b=findfa(b);
  if(a==b)
    return false;
  if(sum[a]>sum[b])
    swap(a,b);
  sum[b]+=sum[a];
  sum2[b]+=sum2[a];
  fa[a]=b;
  return true;
}

bool checked[maxn];

LD ans[maxn];


int main() {
  scanf("%d", &n);
  for1tr(i,n) {
    scanf("%d", &p[i]);
    fa[i]=i;
    sum[i]=1;
  }
  for1tr(i,n) {
    scanf("%d", &q[i]);
  }
  m=0;
  for(i=n;i;i--) {
    ans[i]=m;
    checked[q[i]]=true;
    sum2[q[i]]=p[q[i]];
    if(p[q[i]] > m)
      m=p[q[i]];
    if(checked[q[i]+1]) {
      if(merge(q[i], q[i]+1)) {
        if(sum2[findfa(q[i])] > m) {
          m = sum2[findfa(q[i])];
        }
      }
    }
    if(checked[q[i]-1]) {
      if(merge(q[i], q[i]-1)) {
        if(sum2[findfa(q[i])] > m) {
          m = sum2[findfa(q[i])];
        }
      }
    }
  }
  for1tr(i,n) {
    printf("%lld\n", ans[i]);
  }

  return  0;
}
