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

int i,j,n,m;

#define maxn 200010

map<int, int> p;

LD mypow(LD a,LD n) {
  LD ans = 1, now = a;
  while(n) {
    if(n&1) {
      ans *= now; ans %= 1000000007;
    }
    now *= now;
    now%=1000000007;
    n>>=1;
  }
  return ans;
}

struct Reverse2  {
  // ax + by = gcd(a,b)
  long long int extend_gcd(long long int a, long long int b,
                           long long int &x, long long int &y) {
    long long int ans,t;
    if(b==0){x=1;y=0;return a;}
    ans=extend_gcd(b,a%b,x,y);t=x;x=y;y=t-(a/b)*y;
    return ans;
  }

  // reverse(a) * a  == 1 (mod 1000000007)
  long long int reverse(LD a) {
    static long long int x,y,ans;
    ans=extend_gcd(a, 1000000007, x, y);
    if(x<0)
      return (x%1000000007+1000000007);
    return x;
  }
} r2;

int main() {
  scanf("%d", &n);
  forcnt(n) {
    scanf("%d", &i);
    if(p.count(i)) {
      p[i] ++;
    } else {
      p[i] = 1;
    }
  }
  bool even = false;
  for(auto ii = p.begin();ii!=p.end();ii++) {
    if(ii->second % 2 ==1) {
      even = true;
    }
  }
  LD ans = 1;

  if (p.size() == 1) {
    auto ii =p.begin();
    ans = ans * mypow(ii->first, (1LL * ii->second) *(ii->second+1)/2 )% 1000000007;
    printf("%d\n", (int)ans);
    return 0;
  }

  for(auto ii = p.begin();ii!=p.end();ii++) {
    if(even) {
      ans *= mypow(ii->first, ii->second);
    } else {
      ans *= mypow(ii->first, (ii->second)/2);
    }
    ans %= 1000000007;
  }
 
  for(auto ii = p.begin();ii!=p.end();ii++) {
    if(even && ii->second % 2 ==1) {
      even = false;
      ans = mypow(ans, (ii->second+1)/2);
    } else {
      ans = mypow(ans, ii->second+1);
    }
  }
  printf("%d\n", (int)ans);
  return 0;
  for(auto ii = p.begin();ii!=p.end();ii++) {
    ans = ans * mypow(ii->first, (1LL * ii->second) *(ii->second+1)/2 )% 1000000007;
  }
  printf("%d\n", (int)ans);

  return 0;
}
