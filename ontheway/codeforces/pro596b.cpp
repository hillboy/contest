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
#define maxn 200100

int i,j,n,m;

LD q[maxn];

LD myabs(LD a) {
  return a<0?-a:a;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin >> n;
  LD now,ans=0,left=0;
  for1tr(i, n) {
    cin >> now;
    ans += myabs(left - now);
    left = now;
  }
  cout << ans << endl;
  return 0;
}
