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

char s[1000];

int i,j,n,m;

int f(int a) {
  if(a<0)a=-a;
  if (a+a>26)
    return 26-a;
  return a;
}

int main() {
  scanf("%s", s);
  char a = 'a';
  int ans = 0;
  for(i=0;s[i];i++) {
    ans += f(s[i] -a);
    a=s[i];
  }
  printf("%d\n", ans);
  return 0;
}
