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

int i,j,n,m,x,y,z;

char s[maxn];

int main() {
  scanf("%d %d", &x, &y);
  
  if(y+y>x) {
    printf("3\n");
    return 0;
  }
  int a,b,c;
  a=b=c=y;
  while(c<x) {
    n++;
    c=a+b-1;
    swap(c,a);
    swap(b,c);
  }
  printf("%d\n", n);
  return 0;
  m = -1;
  for(j=y;j<x;j++) {
    a=b=c=x;
    c = j;
    n=1;
    while(a>y) {
      i = b/2;
      if(i<y)
        i=y;
      if (i+c<=b)
        i=b-c+1;
      swap(a,b);
      swap(b,c);
      c=i;
      if(i>b)
        swap(b,c);
      n++;
    }
    if (m<0||n < m) {
      m=n;
    }
  }
  printf("%d\n", m);
  return 0;
}
