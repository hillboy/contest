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

#define maxn 2001000

#define DIV 1000000007



struct Reverse {
  static const long long int div = 1000000007;
  // ax + by = gcd(a,b)
  long long int extend_gcd(long long int a, long long int b,
                           long long int &x, long long int &y) {
    long long int ans,t;
    if(b==0){x=1;y=0;return a;}
    ans=extend_gcd(b,a%b,x,y);t=x;x=y;y=t-(a/b)*y;
    return ans;
  }

  // reverse(a) * a  == 1 (mod div)
  long long int reverse(LD a) {
    static long long int x,y,ans;
    ans=extend_gcd(a, div, x, y);
    if(x<0)
      return (x%div+div);
    return x;
  }
} r2;


// O(1) for C(n,a) after O(n) preprocessing
struct Cn {
  static const long long int div = 1000000007;
  // p[i]= i!
  LD p[maxn];
  // revp[i] * p[i] == 1 mod(div)
  LD revp[maxn];
  LD ans [maxn];
  int n;
  void init(int nn, Reverse* r) {
    n = nn;
    int i;
    p[0] = revp[0] = 1;
    for(i=1;i<=n;i++) {
      p[i] = (p[i-1] * i) % div;
      revp[i] = r->reverse(p[i]);
    }

    for(i=0;i<=n;i++) {
      ans[i]= CC(i);
    }
  }
  LD CC(int a) {
    LD ans = p[n];
    ans *= revp[a];
    ans %= div;
    ans *= revp[n-a];
    ans %= div;
    return ans;
  }
  // pick i out of j
  LD Cij(int i, int j) {
    if(i>j)
      return 0;
    LD ans = p[j];
    ans *= revp[i];
    ans %= div;
    ans *= revp[j-i];
    ans %= div;
    return ans;
  }
  LD C(int a) {
    return ans[a];
  }
} cn;

int a,b,n,m,i,j;

LD p[maxn], sum[maxn];

LD make(int n, int C, int k) {
  LD ans = 0;
  int d = -1;
  int i;
  for(i=0;i<=k;i++) {
    if (n-i*C + k - (i+1) < k-1) {
      break;
    }
    d*=-1;
    ans += d * cn.Cij(i, k) * cn.Cij(k-1, n-i*C + k - (i+1)) % DIV;
    if (ans>=DIV) ans -= DIV;
    if(ans<0)
      ans+=DIV;
  }
  return ans;
}

void prepare() {
  int i;
  p[0]=1;
  sum[0]=1;
  for(i=1;i<=2*n*m;i++) {
    p[i] = make(i, 2*m, n);
    sum[i] = p[i] + sum[i-1];
    if(sum[i] >= DIV) 
      sum[i] -= DIV;
  }
}

int main() {
  cn.init(maxn-1, &r2);
  scanf("%d %d %d %d", &a, &b, &m, &n);
  prepare();
  LD ans = 0;
  for(i=0;i<=2*n*m;i++) {
    j = i +a - b - 1;
    if (j>=0) {
      if(j>2*n*m)
        j=2*n*m;
      ans += p[i] * sum[j] % DIV;
      if(ans>=DIV)
        ans-=DIV;
    }
  }
  printf("%d\n", (int) ans);
  return 0;
}
