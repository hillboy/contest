#include <stdio.h>
#include <assert.h>
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
#define maxn 201000
static const long long int DIV = 1000000007;

#define fix(x) x=(x>=DIV?x-DIV:(x<0?x+DIV:x))

typedef long long int LD;

struct Reverse2 {
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

struct Cn {
  static const long long int div = 1000000007;
  // p[i]= i!
  LD p[maxn];
  // revp[i] * p[i] == 1 mod(div)
  LD revp[maxn];
  LD ans [maxn];
  int n;
  void init(int nn, Reverse2* r) {
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

int i,j,n,m,k,s;

pair<int, int> p[2100], one, ed;

#define da 21
#define db 22

LD q[maxn][db+1];

LD sum[db+1], ans[db+1];

bool has_last;

LD dis(pair<int, int>& a, pair<int, int>& b) {
  return cn.Cij(b.first-a.first, b.first-a.first + b.second - a.second);
}

void make() {
  int r;
  one = make_pair(1,1);
  for1tr(i, k) {
    mymemset(sum, 0);
    for1tr(j, i-1) if (p[j].second<=p[i].second) {
      for1tr(r, 22) {
        sum[r] += q[j][r] * dis(p[j], p[i]) % DIV;
        fix(sum[r]);
      }
    }
    q[i][22] = sum[21];
    for(j=21;j>1;j--) {
      q[i][j] = sum[j-1] - sum[j];
      fix(q[i][j]);
    }
    q[i][1] = dis(one, p[i]) - sum[1];
    fix(q[i][1]);
  }
  if(!has_last) {
    mymemset(sum, 0);
    for1tr(j, k) {
      for1tr(r, 22) {
        sum[r] += q[j][r] * dis(p[j], ed) % DIV;
        fix(sum[r]);
      }
    }
    ans[22]=sum[22];
    for(j=21;j;j--) {
      ans[j] = sum[j] - sum[j+1];
      fix(ans[j]);
    }
    ans[0] = dis(one, ed) - sum[1];
    fix(ans[0]);
  } else {
    for1tr(i, 22) {
      ans[i] = q[k][i];
    }
  }
  LD ans1 = 0, ans2 = dis(one, ed);
  for0r(i, 23) {
    printf("%d %d\n", i, s);
    ans1 += 1LL * s * ans[i] % DIV;
    fix(ans1);
    s = (s+1)/2;
  }
  ans2 = r2.reverse(ans2);
  printf("%d\n", (int)(ans1*ans2%DIV));
}

int main() {
  scanf("%d %d %d %d", &n, &m, &k, &s);
  int a,b;
  ed = make_pair(n,m);
  for1tr(i, k) {
    scanf("%d %d", &a, &b);
    p[i] = make_pair(a, b);
    if(p[i] == ed) {
      has_last = true;
    }
  }
  sort(&p[1], &p[1+k]);
  cn.init(maxn-1, &r2);
  make();
  return 0;
}
