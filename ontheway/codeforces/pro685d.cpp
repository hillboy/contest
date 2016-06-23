#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<map>
#include<set>
using namespace std;

#define maxn 100100

#define forlr(x,l,r) for(x=l;x<(int)r;++x)
#define for1(x,y) forlr(x,0,y)
#define forn(x) for1(x,n)

int i,j,n,m, ynum;

struct point {
  int xx,yy;
  bool ed;
  void output() {
    printf("(%d %d %d)\n", xx,yy,ed);
  }
} p[maxn*2];

bool cmp(const point& a, const point& b) {
  if(a.xx==b.xx && a.ed != b.ed) {
    return a.ed;
  }
  return a.xx < b.xx;
}

set<int> yset;

int ally[maxn*2],t;

long long ans[maxn];
int num[maxn*2], lastx[maxn*2];

int main() {
  scanf("%d %d", &n, &m);
  forn(i) {
    scanf("%d %d", &p[i].xx, &p[i].yy);
    p[i].xx-=m-1;
    p[i].yy-=m-1;
    if(yset.insert(p[i].yy).second) {
      ally[t++]=p[i].yy;
    }
    if(yset.insert(p[i].yy+m).second) {
      ally[t++]=p[i].yy+m;
    }
    p[i+n]=p[i];
    p[i+n].xx+=m;
    p[i+n].ed = true;
  }
  sort(ally,ally+t);
  n+=n;
  sort(p,p+n,cmp);
  i=0;
  int l,r,k;
  while(i<n) {
    j=i;
    while(j<n&&p[i].xx == p[j].xx) {
      l=lower_bound(ally, ally+t, p[j].yy)-ally;
      r=lower_bound(ally, ally+t, p[j].yy+m)-ally;
      if(p[j].ed) {
        forlr(k,l,r) {
          ans[num[k]]+=(long long)(p[i].xx-lastx[k])*(ally[k+1]-ally[k]);
          num[k]--;
          lastx[k]=p[i].xx;
        }
      } else {
        forlr(k,l,r) {
          ans[num[k]]+=(long long)(p[i].xx-lastx[k])*(ally[k+1]-ally[k]);
          num[k]++;
          lastx[k]=p[i].xx;
        }
      }
      j++;
    }
    i=j;
  }
  forlr(i, 1, n/2+1) {
    printf("%I64d ", ans[i]);
  }
  return 0;
}
