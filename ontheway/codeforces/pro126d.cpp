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
#define mymemset(x, val) memset(x, val, sizeof(x))

#define forcnt(n) for(int cnt=n; cnt; cnt--)

#define X(x) (x).first
#define Y(x) (x).second

typedef long long int LD;

#define maxn 88

LD p[maxn],s[maxn];

LD f[maxn][3];

bool ff[maxn];

int i,j;

LD n;

void prepare() {
  p[1]=1;p[2]=2;
  s[1]=1;s[2]=3;
  forlr(i,3,maxn) {
    p[i]=p[i-1]+p[i-2];
    s[i]=s[i-1]+p[i];
  }

  // f[1]=f[2]=1;
  // forlr(i, 3, maxn) {
  //   f[i]=1 + f[i-2];
  // }
  // f[n] = (n+1)/2
}


int main() {
  ios_base::sync_with_stdio(false);
  prepare();
  int m;
  cin >> m;
  while (m--) {
    cin >> n;
    i = maxn-1;
    j = -1;
    mymemset(ff, 0);
    while(n) {
      if(n>=p[i]) {
        ff[i]=1;
        n-=p[i];
      }
      i--;
    }
    mymemset(f, 0);
    f[0][0]=1;
    forlr(i, 1, maxn) {
      if(ff[i]) {
        f[i][0] = f[i-1][0] + f[i-1][2];
        f[i][1] = f[i-1][2];
        f[i][2] = 0;
      } else {
        f[i][0] = f[i-1][0];
        f[i][1] = f[i-1][0] + f[i-1][2];
        f[i][2] = f[i-1][1];
      }
    }
    cout << f[maxn-1][0] << endl;
  }
  return 0;
}
