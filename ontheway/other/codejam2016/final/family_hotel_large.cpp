#include<stdio.h>
#include<algorithm>
#include<map>
#define maxn 10000009
#define div 1000000007
using namespace std;

#define forlr(x,l,r) for(x=l;x<(int)r;++x)
#define for1(x,y) forlr(x,0,y)
#define forn(x) for1(x,n)
#define fix1(x) if(x>=div) { x-= div;}
#define fix2(x) if(x<0) { x+= div;}
#define fix3(x) x%=div; fix2(x);

typedef long long int LD;

int i,j,n,m,k;

LD p[maxn], g[maxn], sp[maxn];

struct point {
  LD a,b;
};
// ax + by = gcd(a,b)
long long int extend_gcd(long long int a, long long int b,
                         long long int &x, long long int &y) {
  long long int ans,t;
  if(b==0){x=1;y=0;return a;}
  ans=extend_gcd(b,a%b,x,y);t=x;x=y;y=t-(a/b)*y;
  return ans;
}
struct Reverse {
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
  // p[i]= i!
  LD p[maxn];
  // revp[i] * p[i] == 1 mod(div)
  LD revp[maxn];
  LD rev[maxn];
  int n;
  void init(int nn, Reverse* r) {
    n = nn;
    int i;
    p[0] = revp[0] = 1;
    for(i=1;i<=n;i++) {
      p[i] = (p[i-1] * i) % div;
      revp[i] = r->reverse(p[i]);
      rev[i] = r->reverse(i);

    }
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
  // pick i out of j
  LD Pij(int i, int j) {
    if(i>j)
      return 0;
    LD ans = p[j];
    ans *= revp[i];
    ans %= div;
    ans *= revp[j-i];
    ans %= div;
    return ans;
  }
} cn;

void prepare() {
  cn.init(maxn-1, &r2);
  p[2] = sp[2] = 1 ;
  forlr(i, 3, maxn) {
    p[i] = (sp[i-2] +1) * cn.p[i-2];
    fix3(p[i]);
    sp[i] = sp[i-1] + p[i]*cn.revp[i-1];
    fix3(sp[i]);
  }
};

LD G(int n) {
  LD ans = cn.p[n-1] - p[n];
  fix2(ans);
  return ans;
}

void make() {
  LD ans = cn.Cij(k-1, n-1);
  ans *= G(k);
  ans %= div;
  ans *= G(n-k+1);
  ans %= div;
  LD base = cn.p[n-1];
  ans = base - ans;
  fix2(ans);
  LD x,y,ha;
  ha = extend_gcd(base, -div, x, y);
  if(ha<0) {
    x=-x;
    y=-y;
    ha=-ha;
  }
  x%=div;
  x*=ans;
  fix3(x);
  printf("%lld\n", x);
}

int main() {
  prepare();
  int nn,ii;
  scanf("%d", &nn);
  forlr(ii, 1, nn+1) {
    printf("Case #%d: ", ii);
    scanf("%d %d", &n, &k);
    make();
  }
  return 0;
}
