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
#define maxn 501000

int p[maxn];

set<int> q;

int i,j,n,m;

int main() {
  scanf("%d", &n);
  for0r(i, n){
    scanf("%d", &j);
    p[m]=j;
    m++;
    push_heap(p, p+m);
    q.insert(j);
  }
  int o;
  while(1) {
    if(p[0]==1)
      break;
    j=p[0]/2;
    o=0;
    while(j) {
      if(q.find(j)==q.end()) {
        o=j;
        break;
      }
      j/=2;
    }
    if(o) {
      q.erase(p[0]);
      q.insert(o);
      pop_heap(p,p+m);
      p[m-1]=j;
      push_heap(p, p+m);
    } else {
      break;
    }
  }
  for0r(i,n) {
    printf("%d ", p[i]);
  }
  return 0;
}
