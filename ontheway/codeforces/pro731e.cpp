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

int p[maxn], q[maxn], sum[maxn];

int i,j,n,m;

int main() {
  scanf("%d", &n);
  for1tr(i, n) {
    scanf("%d", &p[i]);
    sum[i] = sum[i-1] + p[i];
  }
  int last = p[n];
  for(i=n-1;i;i--) {
    q[i] = sum[i] + last;
    if ( -q[i] > last)
      last = -q[i];
    last += p[i];
  }
  printf("%d\n", q[1]);
  return 0;
}
