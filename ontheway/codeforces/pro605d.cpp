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

//  ios_base::sync_with_stdio(false);


int i,j,n,m;

#define maxn 100100

struct ID_map {
  map<int, int> mp;
  int id;
  void init(int *p, int n) {
    sort(p, p+n);
    id = 0;
    mp.clear();
    int i;
    for0r(i, n) {
      if(i==0 || p[i] != p[i-1])
        mp[p[i]] = id++;
    }
  }
  int get(int a) {
    return mp[a];
  }
  int get_ceil(int a) {
    auto ii = mp.lower_bound(a+1);
    if(ii==mp.begin())
      return -1;
    ii--;
    return ii->second;
  }
} x_id, y_id;


struct Point {
  int a,b,c,d;
  int num;
  void output() {
    printf("%d %d %d %d\n", a,b,c,d);
  }
  bool killed;
  bool last;
  Point* trace;
} p[maxn], *current_node, *last_node;

int pt;

bool cmp(const Point& a, const Point& b) {
  return a.a < b.a;
}

int temp_p[maxn];

Point *q[maxn*20];
int qt;

struct TreeNode {
  int start, end;
  int current;
  int lasty = -1;
} tree[maxn*20];

bool cmp2(Point* a, Point* b) {
  return a->b < b->b;
}

void maketree(int a, int l, int r) {
  if(l==r) {
    tree[a].current = tree[a].start = qt;
    while(pt < n && x_id.get(p[pt].a) == l) {
      q[qt++]= &p[pt++];
    }
    tree[a].end = qt;
    sort(&q[tree[a].start], &q[tree[a].end], cmp2);
    return;
  }
  int mid = (l+r)/2;
  maketree(a*2, l, mid);
  maketree(a*2+1, mid+1, r);
  tree[a].current = tree[a].start = qt;
  int lp = tree[a*2].start, rp = tree[a*2+1].start;
  while(lp <tree[a*2].end || rp < tree[a*2+1].end) {
    if(lp==tree[a*2].end) {
      q[qt++]=q[rp++];
      continue;
    }
    if(rp==tree[a*2+1].end) {
      q[qt++]=q[lp++];
      continue;
    }
    if (q[lp]->b < q[rp]->b) {
      q[qt++]=q[lp++];
    } else {
      q[qt++]=q[rp++];
    }
  }
  tree[a].end = qt;
  return;
  printf("%d (%d %d) (%d %d)\n", a, l, r, tree[a].start, tree[a].end);
  int i;
  forlr(i, tree[a].start, tree[a].end) {
    q[i]->output();
  }
}

Point *que[maxn];
int t;

inline int mymin(int a,int b) { return a<b?a:b;}
inline int mymax(int a,int b) { return a>b?a:b;}

bool explore(int a, int l, int r, int left, int right, int y) {
  if(l==left && r==right) {
    if(y<=tree[a].lasty) {
      return false;
    }
    tree[a].lasty = y;
    while(tree[a].current < tree[a].end) {
      auto& now = q[tree[a].current];
      if(now->b > y) {
        break;
      }
      if(!now->killed) {
        now->killed=true;
        now->trace = current_node;
        if(now->last) {
          last_node = now;
          return true;
        }
        que[t++] = now;
      }
      tree[a].current++;
    }
    return false;
  }
  int mid = (l+r)/2;
  bool ans = false;
  if(left<=mid) {
    ans |= explore(a*2, l, mid, left, mymin(mid, right), y);
  }
  if(right>mid) {
    ans |= explore(a*2+1, mid+1, r, mymax(mid+1, left), right, y);
  }
  return ans;
}

void output(Point* a) {
  if(a->trace) {
    output(a->trace);
  }
  printf("%d ", a->num);
}

void make() {
  int ii=0, step=0,i, lastii;
  step = 1;
  int ceil = x_id.get_ceil(0);
  if(ceil < 0) {
    printf("-1\n");
    return;
  }
  if(explore(1,0, x_id.id -1, 0, 0, 0)) {
    printf("%d\n", step);
    printf("%d\n", n);
    return;
  }
  while(ii<t) {
    step++;
    i=t-1;
    lastii = ii;
    ii=t;
    forlr(i, lastii, ii) {
      int ceil = x_id.get_ceil(que[i]->c);
      if(ceil >=0) {
        current_node = que[i];
        if(explore(1, 0, x_id.id-1, 0, ceil, que[i]->d)) {
          printf("%d\n", step);
          output(last_node);
          return;
        }
      }
    }
  }
  printf("-1\n");
  return;
}

int main() {
  scanf("%d", &n);
  for0r(i, n) {
    scanf("%d %d %d %d", &p[i].a, &p[i].b, &p[i].c, &p[i].d);
    temp_p[i] = p[i].a;
    p[i].num = i+1;
    if(i==n-1) {
      p[i].last = true;
    }
  }
  x_id.init(temp_p, n);
  sort(p, p+n, cmp);
  maketree(1, 0, x_id.id-1);
  make();
  return 0;
}
