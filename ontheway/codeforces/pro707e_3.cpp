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
  pair<int, int> next;
}p[maxn][maxn];

int i,j,n,m,k;

int q[maxn];

pair<int, int> start[maxn], ed[maxn];

bool off[maxn];

pair<int, int> que[maxn*10];

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

int xl,xr, yl,yr;

inline bool check_in(int a, int b) {
  return a>=xl && a<=xr && b >= yl && b<=yr;
}

inline bool check_in(pair<int,int>& a) {
  return check_in(X(a), Y(a));
}

LD make() {
  t = 0;
  LD ans = 0;
  int i;
  if (xr == n && yr == m && xl == 1 && yl ==1) {
    for1tr(i, k) {
      if(!off[i]) {
        ans += allsum[i];
      }
    }
    return ans;
  }
  if (xr<n) {
    forltr(i, yl, yr) {
      que[t++] = make_pair(xr, i);
    }
  }
  if (yr<m) {
    forltr(i, xl, xr) {
      que[t++] = make_pair(i, yr);
    }
  }
  if(xl>1 && (xl != xr || xr ==n)) {
    forltr(i, yl, yr) {
      que[t++] = make_pair(xl, i);
    }
  }
  if(yl>1 && (yl != yr || yr ==m)) {
    forltr(i, xl, xr) {
      que[t++] = make_pair(i, yl);
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
    seen[tpe] = true;
    point* last = &p[X(start[tpe])][Y(start[tpe])];
    point* now = &p[X(que[i])][Y(que[i])];
    bool inside = false;
    if(check_in(start[tpe])) {
      inside = check_in(last->next);
      ans += last->v;
    }
    while(i<t) {
      now = &p[X(que[i])][Y(que[i])];
      if(now->a != tpe) {
        break;
      }
      if(now == last) {
        i++;
        continue;
      }

      if (inside) {
        ans += now->sum - last->sum;
      } else {
        ans += now->v;
      }
      inside = check_in(now->next);
      last = now;
      i++;
    }
    if (inside) {
      if (check_in(ed[tpe])) {
        ans += allsum[tpe] - last->sum;
      } else {
      }
    }
  }
  for1tr(i, k) {
    if(!seen[i] && !off[i]) {
      if(check_in(start[i])) {
        ans += allsum[i];
      }
    }
  }
  return ans;
}

char buffer[1000];


int main() {
  scanf("%d %d %d", &n, &m, &k);
  int a,b,v,c,d;
  LD s1,s2,s3,s4;
  LD sum;
  point* last;
  for1tr(i, k) {
    scanf("%d", &q[i]);
    sum = 0;
    for1tr(j, q[i]) {
      scanf("%d %d %d", &a, &b, &v);
      if (j==1) {
        start[i] = make_pair(a,b);
      } else {
        last->next = make_pair(a,b);
      }
      p[a][b].presum = sum;
      sum += v;
      p[a][b].v = v;
      p[a][b].a = i;
      p[a][b].b = j;
      p[a][b].sum = sum;
      last = &p[a][b];
    }
    ed[i] = make_pair(a,b);
    allsum[i] = sum;
  }
  scanf("%d", &v);
  while(v--) {
    scanf(" %s", buffer);
    if(buffer[0] == 'A') {
      scanf("%d %d %d %d", &xl, &yl, &xr, &yr);
      s1 = make();
      printf("%lld\n", s1);
    } else {
      scanf("%d", &a);
      off[a] = !off[a];
    }
  }
  return 0;
}
