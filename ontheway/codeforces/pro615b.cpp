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

#define maxn 200010

int degree[maxn];

int ind[maxn], last[maxn*2], e[maxn*2],t;
int a,b;

int p[maxn];

void adde(int a,int b) {
  t++;
  last[t] = ind[a];
  e[t] = b;
  ind[a]=t;
}

int dfs(int a) {
  if(p[a])
    return p[a];
  int i, temp;
  for(i=ind[a];i;i=last[i]) {
    temp = dfs(e[i]);
    if(temp > p[a])
      p[a] = temp;
  }
  p[a]++;
  return p[a];
}

int main() {
  scanf("%d %d", &n, &m);
  for1tr(i, m) {
    scanf("%d %d", &a, &b);
    degree[a]++;degree[b]++;
    if(a>b) {
      adde(a, b);
    } else {
      adde(b, a);
    }
  }
  LD ans = 0, temp;
  for1tr(i, n) {
    temp = dfs(i);
    temp *= degree[i];
    if (temp > ans)
      ans = temp;
  }
  printf("%lld\n", ans);
  return 0;
}
