#include<stdio.h>

#include<string.h>
#include<algorithm>
#include<map>
#include<set>
#include<vector>
#include<map>
using namespace std;

#define maxn 1010000

#define forlr(x,l,r) for(x=l;x<(int)r;++x)
#define for1(x,y) forlr(x,0,y)
#define forn(x) for1(x,n)

typedef long long int LD;

int noprime[maxn];
int q[maxn], t;

// Linear prime number sieves
void prepare() {
  int i, j;
  for(i=2;i<maxn;i++) {
    if(!noprime[i]) {
      q[++t]=i;
      noprime[i]=i;
    }
    for(j=1;j<=t;j++) {
      if(double(q[j])*i + 1e-9< maxn) {
        noprime[q[j]*i] = q[j];
      } else {
        break;
      }
      if(i%q[j]==0)
        break;
    }
  }
}

LD gcd(LD a, LD b) {
  if(a>b)
    return gcd(b,a);
  if(a==0)
    return b;
  return gcd(b%a,a);
}

int i,j,n,m;


int p[maxn];

int main() {
  prepare();
  scanf("%d %d", &n, &m);
  bool ok=false;
  for1(i, n) {
    scanf("%d", &j);
    LD k = 0;
    for(k=1;(LD)q[k]*q[k]<=j;k++) {
      int now = 0;
      while(j%q[k]==0) {
        j/=q[k];
        now++;
      }
      if(now>p[q[k]])
        p[q[k]]=now;
    }
    if(j>1 && p[j]==0)
      p[j]=1;
  }
  ok=true;
  LD k = 0;
  ok=true;
  for(k=1;(LD)q[k]*q[k]<=m;k++) {
    int now = 0;
    while(m%q[k]==0) {
      m/=q[k];
      now++;
    }
    if(p[q[k]]<now)
      ok=false;
  }
  if(m>1&&p[m]==0) {
    ok=false;
  }
  if(ok){
    printf("Yes\n");
  } else {
    printf("No\n");
  }
  return 0;
}
