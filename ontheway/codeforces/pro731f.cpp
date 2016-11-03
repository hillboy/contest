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

int i,j,n,m,k;

bool has_p[maxn];

int p[maxn];

int main() {
  scanf("%d", &n);
  for1tr(i, n) {
    scanf("%d", &p[i]);
    has_p[p[i]] = 1;
  }
  sort(&p[1], &p[1+n]);
  LD ans = 0, now, max_ans = 0;
  int l,r;
  for1tr(i, maxn) {
    if(!has_p[i])
      continue;
    l=lower_bound(&p[1], &p[1+n], i) - p;
    ans=0;
    for(j=2;i*j<maxn;j++) {
      r = lower_bound(&p[1], &p[1+n], i*j) - p;
      now = i*(j-1);
      now*= r-l;
      ans+=now;
      l = r;
    }
    now = i*(j-1);
    now*= n+1-l;
    ans+=now;
    if(ans>max_ans)
      max_ans = ans;
  }
  printf("%lld\n", max_ans);
  return 0;
}
