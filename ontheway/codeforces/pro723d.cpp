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
#define maxn 52

char s[maxn][maxn];

int checked[maxn][maxn];

int now;

int lake_size[maxn*maxn];

int i,j,n,m,k;

int di[4][2] = {
  {-1, 0},
  {1, 0},
  {0,1},
  {0, -1}
};

bool killed[maxn*maxn];

void make(int a, int b) {
  if(s[a][b] == 0) {
    lake_size[now] = -1;
    return;
  }
  if(checked[a][b])
    return;
  if(s[a][b] =='*')
    return;
  checked[a][b] = now;
  if(lake_size[now] >=0)
    lake_size[now]++;
  int i;
  for0r(i, 4) {
    make(a+di[i][0], b + di[i][1]);
  }
}

int main() {
  scanf("%d %d %d", &n, &m, &k);
  int i,j;
  for1tr(i, n) {
    scanf("%s", &s[i][1]);
  }
  for1tr(i,n) {
    for1tr(j, m) {
      if (s[i][j] =='.' && !checked[i][j]) {
        now++;
        make(i,j);
      }
    }
  }
  vector<pair<int, int>> all;
  for1tr(i, now) {
    if(lake_size[i] >0) {
      all.push_back(make_pair(lake_size[i], i));
    }
  }
  sort(all.begin(), all.end());
  int ans = 0;
  for0r(i, sz(all)-k) {
    ans += all[i].first;
    killed[all[i].second] = true;
  }
  printf("%d\n", ans);
  for1tr(i,n) {
    for1tr(j, m) {
      if(checked[i][j] && !killed[checked[i][j]]) {
        printf(".");
      } else 
        printf("*");
    }
    printf("\n");
  }
  
  return 0;
}
