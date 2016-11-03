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

#define maxn 501000

int i,j,n,m;

vector<int> p[maxn];

int sum[1000010];

int main() {
  scanf("%d %d", &n, &m);
  int a;
  for1tr(i, n) {
    scanf("%d", &j);
    forcnt(j) {
      scanf("%d", &a);
      p[i].push_back(a-1);
    }
  }
  for1tr(i, n-1) {
    j=0;
    while(j<sz(p[i]) && j < sz(p[i+1]) && p[i][j] == p[i+1][j])
      j++;
    if(j==sz(p[i])) {
      sum[0]++;
      sum[m]--;
      continue;
    }
    if(j==sz(p[i+1])) {
      printf("-1\n");
      return 0;
    }
    if(p[i][j] < p[i+1][j]) {
      sum[0]++;
      sum[m-p[i+1][j]] --;
      sum[m-p[i][j]]++;
      sum[m]--;
    } else {
      sum[m-p[i][j]]++;
      sum[m-p[i+1][j]]--;
    }
  }
  int now = 0;
  for(i=0;i<=m;i++) {
    now+=sum[i];
    if(now>=n-1) {
      printf("%d\n", i);
      return 0;
    }
  }
  printf("-1\n");
  return 0;
}
