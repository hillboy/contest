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
#define maxn 100100

int i,j,n,m;

int p[maxn];

bool cap[maxn];

LD sum, sum_c, sq_sum_c;

int main() {
  scanf("%d %d", &n, &m);
  for1tr(i, n) {
    scanf("%d", &p[i]);
    sum += p[i];
  }
  for1tr(i, m) {
    scanf("%d", &j);
    sum_c += p[j];
    sq_sum_c += 1LL * p[j] * p[j];
    cap[j] = 1;
  }
  LD ans = sum * sum_c - (sum_c * sum_c + sq_sum_c)/2;
  for1tr(i, n-1) {
    if (!cap[i] && ! cap[i+1]) {
      ans += 1LL * p[i] * p[i+1];
    }
  }
  if (!cap[1] && ! cap[n]) {
    ans += 1LL * p[1] * p[n];
  }
  printf("%lld\n", ans);

  return 0;
}
