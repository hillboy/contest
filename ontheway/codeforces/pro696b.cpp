#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<map>
#include<set>
#include<vector>
#include<map>
#include<string>
using namespace std;
#define maxn 1001000

#define forlr(x,l,r) for(x=l;x<(int)r;++x)
#define for1(x,y) forlr(x,0,y)
#define forn(x) for1(x,n)
#define sz(x) (int)x.size()


int i,j,n,m;

vector<int> child[maxn];

int fa[maxn];
int sum[maxn];

double ans[maxn];

void dfs1(int a) {
  int i,now;
  sum[a]=1;
  for1(i,sz(child[a])) {
    now = child[a][i];
    dfs1(now);
    sum[a]+=sum[now];
  }
}

void dfs2(int a) {
  int i,now;
  if(a==0) {
    ans[a]=1;
  } else {
    ans[a]=ans[fa[a]] + 1 + (sum[fa[a]] - sum[a] - 1)/2.0;
  }
  for1(i,sz(child[a])) {
    now = child[a][i];
    dfs2(now);
  }
}

int main() {
  scanf("%d", &n);
  for1(i, n-1) {
    scanf("%d", &j);
    child[j-1].push_back(i+1);
    fa[i+1] = j-1;
  }
  dfs1(0);
  dfs2(0);
  for1(i, n) {
    printf("%.8lf ", ans[i]);
  }
  return 0;
}
