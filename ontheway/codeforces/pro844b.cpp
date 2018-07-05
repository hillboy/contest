#include <iostream>
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

int i,j,n,m,k;

#define maxn 100

int row[maxn], col[maxn];

int main() {
  scanf("%d %d", &n, &m);
  forltr(i, 1, n) {
    forltr(j, 1, m) {
      scanf("%d", &k);
      if(k) {
        row[i]++;
        col[j]++;
      }
    }
  }
  long long int ans = 0;
  forltr(i, 1, n) {
    ans+= (1LL << row[i]) - 1;
    ans+= (1LL << (m-row[i])) - 1;
  }
  forltr(i, 1, m) {
    ans+= (1LL << col[i]) - 1;
    ans+= (1LL << (n-col[i])) - 1;
  }
  ans -= n*m;
  printf("%lld\n", ans);
  return 0;
}
