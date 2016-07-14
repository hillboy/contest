#include<iostream>
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

typedef long long int LD;


map<pair<LD, LD>, LD> all;

void addw(LD a, LD b, LD w) {
  if(all.count(make_pair(a,b))) {
    all[make_pair(a,b)] += w;
  } else {
    all[make_pair(a,b)] = w;
  }
}

LD getw(LD a, LD b) {
  if(all.count(make_pair(a,b))) {
    return all[make_pair(a,b)];
  } else {
    return 0;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  int n;
  cin >> n;
  int tpe;
  LD v,u,w,now,ans;
  while(n--) {
    cin >> tpe;
    if(tpe == 1) {
      cin >> v >> u >> w;
      while(v!=u) {
        if(v>u) {
          swap(v,u);
        }
        now = u / 2;
        addw(now, u, w);
        u=now;
      }
    } else {
      cin >> v >> u;
      ans=0;
      while(v!=u) {
        if(v>u) {
          swap(v,u);
        }
        now = u / 2;
        ans+=getw(now,u);
        u=now;
      }
      cout << ans << endl;
    }
  }
  return 0;
}
