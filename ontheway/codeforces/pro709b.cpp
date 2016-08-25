#include <stdio.h>
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

#define maxn 100100

int mymin(int a,int b) {
  return a<b?a:b;
}

typedef long long int LD;

int i,j,n,m,b,d;

int p[maxn];

int getdis(int* p) {
  if(m<=p[0]) {
    return p[n-1] - m;
  }
  if(m>=p[n-1]) {
    return m-p[0];
  }
  return mymin(p[n-1]-m, m-p[0]) + p[n-1]-p[0];
}

int main() {
  scanf("%d %d", &n, &m);
  for0r(i, n) {
    scanf("%d", &p[i]);
  }
  sort(p, p+n);
  n--;
  if(n)
    printf("%d\n", mymin(getdis(p), getdis(&p[1])));
  else
    printf("0\n");
  
  return 0;
}
