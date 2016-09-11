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

char s[maxn];

int main() {
  scanf("%s", s);

  for(i=0;s[i];i++) {
    switch (s[i]) {
      case 'L' : 
        n++;
        break;
      case 'R':
        n--;
        break;
      case 'U':
        m++;
        break;
      case 'D':
        m--;
        break;
    }

  }
    if (n<0) n=-n;
    if(m<0) m=-m;
    if((n+m) % 2) {
      printf("-1\n");
    } else 
      printf("%d\n", (n+m)/2);
  return 0;
}
