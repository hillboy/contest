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

typedef int LD;
#define maxn 1001000

struct BitTree {
  int c[maxn];
  inline int lowbit(int x) {
    return x & (-x);
  }
  void modify(int pos, LD x) {
    while (pos < maxn) {
      c[pos] ^= x;
      pos += lowbit(pos);
    }
  }
  LD sum(int end) {
    LD sum = 0;
    while (end) {
      sum ^= c[end];
      end -= lowbit(end);
    }
    return sum;
  }
}tree;

int p[maxn], sum[maxn];

int i,j,n,m;

int ans[maxn];

vector<pair<int, int>> q[maxn];

map<int, int> last;

void make() {
  for(i=n;i;i--) {
    auto  ii = last.find(p[i]);
    if(ii != last.end()) {
      tree.modify(ii->second, p[i]);
      ii->second = i;
    } else {
      last[p[i]] = i;
    }
    tree.modify(i, p[i]);
    for0r(j, sz(q[i])) {
      ans[q[i][j].second] = tree.sum(q[i][j].first) ^ sum[q[i][j].first] ^ sum[i-1];
    }
  }
}

int main() {
  scanf("%d",&n);
  for1tr(i, n) {
    scanf("%d", &p[i]);
    sum[i] = sum[i-1] ^ p[i];
  }
  scanf("%d", &m);
  int a,b;
  for1tr(i, m) {
    scanf("%d %d", &a, &b);
    q[a].push_back(make_pair(b, i));
  }
  make();
  for1tr(i, m) {
    printf("%d\n", ans[i]);
  }
  return 0;
}
