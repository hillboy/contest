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

#define maxn 111

int i,j,r,rr,n,m,k;

int color[maxn], cost[maxn][maxn];

LD p[maxn][maxn][maxn];

void update(LD& a, LD b) {
  if(b<0)
    return;
  if(a<0 || a>b)
    a=b;
}

int main() {
  scanf("%d %d %d", &n, &m, &k);
  for0r(i, n) {
    scanf("%d", &color[i]);
  }
  for0r(i, n) {
    for1tr(j, m) {
      scanf("%d", &cost[i][j]);
    }
  }
  mymemset(p, -1);
  if(color[0]) {
    p[0][1][color[0]] = 0;
  } else {
    for1tr(i, m) {
      p[0][1][i] = cost[0][i];
    }
  }
  for1tr(i, n-1) {
    for1tr(j, k) {
      if(color[i]) {
        p[i][j][color[i]] = p[i-1][j][color[i]];
        for1tr(r, m) {
          if(r!=color[i])
            update(p[i][j][color[i]], p[i-1][j-1][r]);
        }
      } else {
        for1tr(r, m) {
          p[i][j][r] = p[i-1][j][r];
          for1tr(rr,m) {
            if (rr!=r) {
              update(p[i][j][r], p[i-1][j-1][rr]);
            }
          }
          if (p[i][j][r]>=0) {
            p[i][j][r] += cost[i][r];
          };
        }
      }
    }
  }
  LD ans = -1;
  for1tr(i, m) {
    update(ans, p[n-1][k][i]);
  }
  printf("%lld\n", ans);
  return 0;
}
