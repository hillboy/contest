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

#define maxn 500010
#define maxm 1000100

int ind[maxn], last[maxm*2], e[maxm*2], t;

void adde(int a,int b) {
  t++;
  e[t]=b;
  last[t]=ind[a];
  ind[a]=t;
}

int i,j,n,m,k;

int p[maxn],pt;

void dfs(int a, int fa, int de) {
  int i;
  if (fa) {
    p[pt++] = de;
  }
  for(i=ind[a];i;i=last[i]) {
    if(e[i]!=fa) {
      dfs(e[i], a, de+1);
    }
  }
}

int main() {
  scanf("%d %d %d", &n, &k, &m);
  int a,b;
  forcnt(n-1) {
    scanf("%d %d", &a, &b);
    adde(a,b);
    adde(b,a);
  }
  dfs(1, 0, 0);
  sort(p, p+pt);
  int ans = 0 ;
  long long int sum = 0, num = 0;
  j=0;
  for0r(i, pt) {
    if(i && p[i] > p[i-1]) {
      sum += num;
    }
    num++;
    while(j<i && sum > m) {
      sum -= p[i] - p[j];
      j++;
      num--;
    }
    if(num > k) {
      ans = k;
    } else if(num > ans)
      ans = num;
  }
  printf("%d\n", ans);
  return 0;
}
