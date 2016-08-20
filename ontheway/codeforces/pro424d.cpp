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

#define maxn 311

int i,j,n,m,t,r, tp,tu,td;

int p[maxn][maxn];

int su[maxn][maxn], sd[maxn][maxn];

int up[maxn], down[maxn];

int T(int l, int r) {
  if(l==r) return tp;
  if(l<r) return tu;
  return td;
}

pair<int,int> q[maxn];

int ans,ansi,ansj, ansr,ansrr;

int main() {
  scanf("%d %d %d", &n, &m, &t);
  scanf("%d %d %d", &tp, &tu, &td);
  for1tr(i,n) {
    for1tr(j,m) {
      scanf("%d", &p[i][j]);
      if(j>1) {
        su[i][j]=su[i][j-1] + T(p[i][j-1], p[i][j]);
        sd[i][j]=sd[i][j-1] + T(p[i][j], p[i][j-1]);
      }
    }
  }
  ans = 1000000000;
  int rr,rrr;
  for1tr(i,n-2) {
    for1tr(r, m) {
      up[r] = T(p[i+1][r], p[i][r]);
      down[r] = T(p[i][r], p[i+1][r]);
    }
   
    forltr(j, i+2, n) {
      for1tr(r, m) {
        up[r] += T(p[j][r], p[j-1][r]);
        down[r] += T(p[j-1][r], p[j][r]);
        q[r] = make_pair(down[r] + su[i][r] + sd[j][r], r);
      }
      sort(&q[1], &q[1+m]);
      for1tr(r, m-2) {
        // up[r] + q[rr] - su[i][r] - sd[j][r] <=t
        rrr = lower_bound(&q[1], &q[m+1], make_pair(t - (up[r] - su[i][r] - sd[j][r]), r)) - q;
        rr = rrr;
        while(rr<=m && q[rr].second < r + 2) {
          rr++;
        }
        if (rr<=m) {
          if(up[r] + q[rr].first - su[i][r] - sd[j][r] - t <  ans) {
            ans = up[r] + q[rr].first - su[i][r] - sd[j][r] - t;
            ansi = i;
            ansj = j;
            ansr = r;
            ansrr= q[rr].second;
          }
        }
        rr = rrr-1;
        while(rr && q[rr].second < r + 2) {
          rr--;
        }
        if(rr) {
          if(t - (up[r] + q[rr].first - su[i][r] - sd[j][r]) <  ans) {
            ans = t - (up[r] + q[rr].first - su[i][r] - sd[j][r]);
            ansi = i;
            ansj = j;
            ansr = r;
            ansrr= q[rr].second;
          }
        }
      }
    }
  }
  // printf("%d\n", ans);
  printf("%d %d %d %d\n", ansi, ansr, ansj, ansrr);
  return 0;
}
