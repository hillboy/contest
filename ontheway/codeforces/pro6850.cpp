#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<set>
#include<vector>
using namespace std;

#define for1(x,y) for(x=0;x<y;++x)
#define forn(x) for1(x,n)

#define maxn 10

int p[maxn];

int i,j,n,m;

int getDigit(long long int a) {
  long long int now = 7, ans=1;
  while(now<a) {
    now*=7;
    ans++;
  }
  return ans;
}

set<pair<int,int>> checked;


int main() {
  for1(i,7) {
    p[i]=i;
  }
  scanf("%d %d", &n, &m);
  if(n==1&&m==1) {
    printf("%d\n", 0);
    return 0;
  }
  int nn=getDigit(n), mm=getDigit(m);
  long long int a,b;
  if(nn+mm>7) {
    printf("%d\n", 0);
    return 0;
  }
  int ans = 0;
  while(1) {
    a=0,b=0;
    for1(i,nn) {
      a=a*7;
      a=a+p[i];
    }
    for1(i,mm) {
      b=b*7;
      b=b+p[nn+i];
    }
    if(checked.insert(make_pair(a,b)).second) {
      if(a<n && b < m) {
        ans++;
      }
    }
    if(!std::next_permutation(p, p+7))
      break;
  }
  printf("%d\n", ans);
  return 0;
}
