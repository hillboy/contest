#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include <map>
#include <string>
#include <math.h>
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

#define maxn 1000000

int i,j,n,m;

int ind[maxn], last[maxn], e[maxn], t;

void adde(int a,int b){
  t++;
  e[t]=b;
  last[t]=ind[a];
  ind[a]=t;
}

int sum[maxn], max_sub[maxn];

bool ans[maxn];

void dfs1(int a, int fa) {
  int i;
  sum[a]=1;
  for(i=ind[a];i;i=last[i]) {
    if(e[i]!=fa) {
      dfs1(e[i], a);
      sum[a] += sum[e[i]];
      if(max_sub[e[i]] > max_sub[a]) {
        max_sub[a] = max_sub[e[i]];
      }
    }
  }
  if(sum[a] <=m ) {
    max_sub[a] = sum[a];
  }
}

void dfs2(int a, int fa, int up_sub) {
  int i;
  int up_sum = n - sum[a];

  ans[a] = 1;

  for(i=ind[a];i;i=last[i]) {
    if(e[i]!=fa) {
      if (sum[e[i]] > m) {
        if(sum[e[i]] - max_sub[e[i]] > m) {
          ans[a] = 0;
        }
      }
    }
  }
  if(up_sum > m) {
    if(up_sum - up_sub > m) {
      ans[a]= 0;
    }
  }
  if(up_sum <=m) {
    up_sub = up_sum;
  }
  pair<int, int> max1, max2;
  max1 = make_pair(up_sub, -1);
  max2 = make_pair(0, -1);
  for(i=ind[a];i;i=last[i]) {
    if(e[i]!=fa) {
      if (max_sub[e[i]] > max2.first) {
        max2.first = max_sub[e[i]];
        max2.second = e[i];
        if(max2.first > max1.first) {
          swap(max2, max1);
        }
      }
    }
  }
  for(i=ind[a];i;i=last[i]) {
    if(e[i]!=fa) {
      if(e[i] == max1.second) {
        dfs2(e[i], a, max2.first);
      } else {
        dfs2(e[i], a, max1.first);
      }
    }
  }
}

int main() {
  scanf("%d", &n);
  m=n/2;
  int a,b;
  for0r(i, n-1) {
    scanf("%d %d", &a, &b);
    adde(a,b);
    adde(b,a);
  }
  dfs1(1, 0);
  dfs2(1,0,0);
  for1tr(i, n) {
    printf("%d ", ans[i]);
  }
  return 0;
}

