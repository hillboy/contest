#include <stdlib.h>
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

int i,j,n,m,k,x,start;

#define maxn 100000

#define maxm 2000

#define randc 1000

bool checked[maxn];

int p[maxn], q[maxn];

void getn(int a) {
  while(a < 1 || a > n);
  printf("? %d\n", a);
  fflush(stdout);
  scanf("%d %d", &p[a], &q[a]);
}

int main() {
  srand(111);
  scanf("%d %d %d", &n, &start, &x);
  m = maxm - 1;
  getn(start);
  if (p[start] >= x) {
    printf("! %d\n", p[start]);
    return 0;
  }
  checked[start]=1;
  for0r(i, randc) {
    j=(1234567LL*rand())%n + 1;
    if (!checked[j]) {
      checked[j]=1;
      getn(j);
      m--;
    }
  }
  j=start;

  forltr(i, 1, n) if(checked[i]) {
    if (p[i] <= x && p[i] > p[j]) {
      j=i;
    }
  }
  while(p[j] < x && q[j] > 0 ) {
    j = q[j];
    if (checked[j]) {
      break;
    }
    getn(j);
  }
  if (p[j] >= x) {
    printf("! %d\n", p[j]);
  } else {
    printf("! -1\n");
  }
  return 0;
}
