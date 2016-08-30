#include <iostream>
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
#define div 1000000007

#define maxn 200010

int i,j,n,m;

int visited[maxn];

LD myabs(LD a) {
  return a<0?-a:a;
}

vector<pair<int, int> > edges[maxn];

LD ans = 1;

int cir;

LD mypow(LD a,LD n) {
  LD ans = 1, now = a;
  while(n) {
    if(n&1) {
      ans *= now; ans %= div;
    }
    now *= now;
    now%=div;
    n>>=1;
  }
  return ans;
}

bool used[maxn];

void dfs(int a,int depth, int laste) {
  visited[a]=depth;
  int i;
  for(i=0; i< sz(edges[a]); i++) {
    if(!visited[edges[a][i].first]) {
      used[edges[a][i].second] = true;
      dfs(edges[a][i].first, depth+1, edges[a][i].second);
    } else {
      if(!used[edges[a][i].second]) {
        used[edges[a][i].second] = true;
        ans *= (mypow(2, myabs(visited[edges[a][i].first] - depth)+1) - 2 + div)%div;
        cir += myabs(visited[edges[a][i].first] - depth)+1;
        ans %= div;
      }
    }
  }
}


int main() {
  scanf("%d", &n);
  for1tr(i, n) {
    scanf("%d", &j);
    edges[i].push_back(make_pair(j, i));
    edges[j].push_back(make_pair(i, i));
  }
  for1tr(i,n) {
    if(!visited[i]) {
      dfs(i, 1, -1);
    }
  }
  ans *= mypow(2, n - cir);
  ans %= div;
  printf("%d\n", (int)ans);
  return 0;
}
