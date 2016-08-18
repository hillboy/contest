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

int i,j,n,m;

#define maxn 500010
#define maxm 1000100

int ind[maxn], last[maxm*2], e[maxm*2], t;

void adde(int a,int b) {
  t++;
  e[t]=b;
  last[t]=ind[a];
  ind[a]=t;
}

vector<int> nxt[2];
vector<int> pp;

int ha[maxn];

int que[maxn],qt;

int nt;

struct Myset {
  int ind[maxn];
  int last[maxn];
  int e[maxn];
  int t;
  int n;
  void inc() {
    n++;
  }
  void add(int b) {
    add(n,b);
  }
  void add(int a,int b) {
    t++;
    last[t]=ind[a];
    e[t]=b;
    ind[a]=t;
  }
  void output() {
    printf("%d\n", n);
    int num;
    for1tr(i,n) {
      num = 0;
      for(j=ind[i];j;j=last[j]) {
        num++;
      }
      printf("%d", num);
      for(j=ind[i];j;j=last[j]) {
        printf(" %d", e[j]);
      }
      printf("\n");
    }
  }
} myset;

void make2(set<int>& p) {
  while(p.size()) {
    pp.clear();
    nxt[nt].push_back(*p.begin());
    p.erase(p.begin());
    myset.inc();
    while(nxt[nt].size()) {
      for(auto i : nxt[nt]) {
        myset.add(i);
      }
      vector<int>& nextnext = nxt[1-nt];
      for (auto ii : nxt[nt]) {
        for( i = ind[ii]; i; i = last[i]) {
          if(p.count(e[i])) {
            pp.push_back(e[i]);
            p.erase(e[i]);
          }
        }
        for (auto jj : p) {
          nextnext.push_back(jj);
        }
        p.clear();
        p.insert(pp.begin(), pp.end());
        pp.clear();
      }
      nxt[nt].clear();
      nt = 1 - nt;
    }
  }
}

void make() {
  int depth=0;
  for1tr(i, n) {
    que[i]=i;
  }
  qt=n;
  while(qt) {
    myset.inc();
    int lastnext=0;
    myset.add(que[qt]);
    qt--;
    while(myset.ind[myset.n] != lastnext) {
      i=myset.ind[myset.n];
      while(i!=lastnext) {
        depth++;
        for( j = ind[myset.e[i]]; j; j = last[j]) {
          ha[e[j]]++;
        }
        i=myset.last[i];
      }

      lastnext = myset.ind[myset.n];
      i=1;
      while(i<=qt) {
        if(ha[que[i]]!=depth) {
          myset.add(que[i]);
          swap(que[i], que[qt]);
          qt--;
        } else {
          i++;
        }
      }
    }
  }
}

int main() {
  scanf("%d %d", &n, &m);
  int a,b;
  while(m--) {
    scanf("%d %d", &a, &b);
    adde(a,b);adde(b,a);
  }
  make();
  myset.output();
  return 0;
}
