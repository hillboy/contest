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

#define maxn 201000

pair<int, int> edges[maxn*2];
vector<pair<int, int>> es, et, ans;

int fa[maxn], sum[maxn];

int s,t,ds,dt;

int i,j,n,m;

bool has_st;

int findfa(int a) {
  if(fa[a]==a)
    return a;
  return fa[a] = findfa(fa[a]);
}

int bs[maxn], bt[maxn];

int que[maxn],qt;

bool merge(int a, int b) {
  a = findfa(a); b= findfa(b);
  if(a==b)
    return false;
  if(sum[a] > sum[b])
    swap(a,b);
  sum[b]+=sum[a];
  fa[a] = b;
  return true;
}

int main() {
  scanf("%d %d", &n, &m);
  int a, b;
  for0r(i, m) {
    scanf("%d %d", &a, &b);
    if(a>b)
      swap(a,b);
    edges[i] = make_pair(a,b);
  }
  scanf("%d %d %d %d", &s, &t, &ds, &dt);
  if(s>t) {
    swap(s, t);
    swap(ds, dt);
  }
  for1tr(i, n) {
    sum[i] = 1;
    fa[i]=i;
  }
  for0r(i, m) {
    if(edges[i].first != s && edges[i].first != t && edges[i].second != s && edges[i].second != t) {
      if(merge(edges[i].first, edges[i].second)) {
        ans.push_back(edges[i]);
      }
    } else if(edges[i].first == s && edges[i].second == t) {
      has_st = true;
    } 
  }
  for0r(i, m) {
    if(edges[i].first != s && edges[i].first != t && edges[i].second != s && edges[i].second != t) {
    } else if(edges[i].first == s && edges[i].second == t) {
    } else if(edges[i].first == s || edges[i].second == s) {
      bs[findfa(edges[i].first + edges[i].second - s)] = i + 1;
    } else {
      bt[findfa(edges[i].first + edges[i].second - t)] = i + 1;
    }
  }

  bool ok = true;
  for1tr(i, n) {
    if(i==s || i ==t)
      continue;
    if(findfa(i) == i) {
      if(bs[i] == 0 && bt[i] == 0) {
        ok=false;
        break;
      }
      if(bs[i] && bt[i] ==0) {
        ans.push_back(edges[bs[i]-1]);
        ds --;
      }
      if(bs[i] ==0 && bt[i]) {
        ans.push_back(edges[bt[i]-1]);
        dt --;
      }
    }
  }
  bool oo = true;
  for1tr(i, n) {
    if(i==s || i ==t)
      continue;
    if(findfa(i) == i) {
      if(bs[i] && bt[i]) {
        if(oo) {
          ans.push_back(edges[bt[i]-1]);
          ans.push_back(edges[bs[i]-1]);
          ds--;
          dt--;
          oo=false;
        } else {
          if(dt>0) {
            ans.push_back(edges[bt[i]-1]);
            dt --;
          } else {
            ans.push_back(edges[bs[i]-1]);
            ds --;
          }
        }
      }
    }
  }
  if(oo) {
    if(has_st) {
      ans.push_back(make_pair(s,t));
      ds--;dt--;
    } else {
      ok = false;
    }
  }
  if (ds < 0 || dt < 0) {
    ok = false;
  }
  if(ok) {
    printf("Yes\n");
    for0r(i, sz(ans)) {
      printf("%d %d\n", ans[i].first, ans[i].second);
    }
  } else {
    printf("No\n");
  }
  return 0;
}
