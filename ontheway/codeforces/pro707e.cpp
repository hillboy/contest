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

#define maxn 2011


struct point {
  int a,b,v;
  LD sum, presum;
}p[maxn][maxn];

int i,j,n,m,k;

int q[maxn];

pair<int, int> start[maxn];

bool off[maxn];

pair<int, int> que[maxn*maxn];

int t;

LD allsum[maxn];

bool cmp(const pair<int, int>& a, const pair<int, int>& b ) {
  if (p[X(a)][Y(a)].a != p[X(b)][Y(b)].a) {
    return p[X(a)][Y(a)].a < p[X(b)][Y(b)].a;
  } else {
    return p[X(a)][Y(a)].b < p[X(b)][Y(b)].b;
  }
}

bool seen[maxn];

LD make(int x, int y) {
  if (x<1 || y < 1)
    return 0;
  t = 0;
  LD ans = 0;
  int i;
  if (x == n && y == m) {
    for1tr(i, k) {
      if(!off[i]) {
        ans += allsum[i];
      }
    }
    return ans;
  }
  if (x<n) {
    for1tr(i, y) {
      que[t++] = make_pair(x, i);
      que[t++] = make_pair(x+1, i);
    }
  }
  if (y<m) {
    for1tr(i, x) {
      que[t++] = make_pair(i, y);
      que[t++] = make_pair(i, y+1);
    }
  }
  sort(que, que+t, cmp);
  mymemset(seen, 0);
  i = 0;
  while (i<t) {
    int tpe = p[X(que[i])][Y(que[i])].a;
    while(i<t && off[tpe]) {
      i++;
      tpe = p[X(que[i])][Y(que[i])].a;
    }
    if(i>=t)
      break;
    point* last = &p[X(start[tpe])][Y(start[tpe])];
    point* now = &p[X(que[i])][Y(que[i])];
    bool inside = false;
    if (last->a <= x && last->b <= y) {
      inside = true;
      ans += last->v;
    }
    while(i<t) {
      now = &p[X(que[i])][Y(que[i])];
      if(now->a != tpe) {
        break;
      }
      if (now->a <=x && now->b <=y) {
        if (inside) {
          ans += now->sum - last->sum;
        } else {
          ans += now->v;
        }
        inside = true;
      } else {
        inside = false;
      }
      i++;
    }
    if (inside) {

    }
  }
  return ans;
}


int main() {
  scanf("%d %d %d", &n, &m, &k);
  int a,b,v;
  LD sum;
  for1tr(i, k) {
    scanf("%d", &q[i]);
    sum = 0;
    for1tr(j, q[i]) {
      scanf("%d %d %d", &a, &b, &v);
      if (j==1) {
        start[i] = make_pair(a,b);
      }
      p[a][b].presum = sum;
      sum += v;
      p[a][b].v = v;
      p[a][b].a = i;
      p[a][b].b = j;
      p[a][b].sum = sum;
    }
    allsum[i] = sum;
  }
  return 0;
}
