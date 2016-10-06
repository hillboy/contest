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
#define maxn 211

int i,j,n,m;

int di[maxn];

int p[maxn][maxn];
int pp[maxn][maxn];

bool checked[maxn];

int q[maxn], t;
int ans;

int output[maxn*maxn][2], ot;

void dfs1(int a) {
  checked[a]=1;
  if(di[a]&1)
    q[t++]=a;
  int b;
  for1tr(b, n) {
    if(p[a][b] &&!checked[b]) {
      dfs1(b);
    }
  }
}

void dfs2(int a) {
  int b;
  for1tr(b, n) {
    if(p[a][b]) {
      p[b][a] = p[a][b] = 0;
      dfs2(b);
      output[ot][0] = a;
      output[ot][1] = b;
      ot++;
    }
    if(pp[a][b]) {
      pp[b][a] = pp[a][b] = 0;
      dfs2(b);
    }
  }
}


int main() {
  int nn;
  scanf("%d", &nn);
  int a,b;
  while(nn--) {
    scanf("%d %d", &n, &m);
    mymemset(di, 0);
    mymemset(p, 0);
    mymemset(pp, 0);
    mymemset(checked, 0);
    for1tr(i, m) {
      scanf("%d %d", &a, &b);
      p[a][b]=p[b][a] = 1;
      di[a]++;
      di[b]++;
    }
    ans=0;
    ot=0;
    for1tr(a, n) {
      if(!checked[a]) {
        t=0;
        dfs1(a);
        ans+=t;
        for(i=0;i<t;i+=2) {
          pp[q[i]][q[i+1]]=pp[q[i+1]][q[i]] = 2;
        }
        dfs2(a);
      }
    }
    printf("%d\n", n - ans);
    for0r(i, ot) {
      printf("%d %d\n", output[i][0], output[i][1]);
    }

  }
  return 0;
}
