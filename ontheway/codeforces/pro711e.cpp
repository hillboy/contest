
#include <iostream>
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
#define sz(x) ((int)x.size())

typedef long long int LD;

static const long long int DIV = 1000003;

LD pow(LD a,LD n) {
  LD ans = 1, now = a;
  while(n) {
    if(n&1) {
      ans *= now; ans %= DIV;
    }
    now *= now;
    now%=DIV;
    n>>=1;
  }
  return ans;
}

struct Reverse2 {
  // ax + by = gcd(a,b)
  long long int extend_gcd(long long int a, long long int b,
                           long long int &x, long long int &y) {
    long long int ans,t;
    if(b==0){x=1;y=0;return a;}
    ans=extend_gcd(b,a%b,x,y);t=x;x=y;y=t-(a/b)*y;
    return ans;
  }

  // reverse(a) * a  == 1 (mod DIV)
  long long int reverse(LD a) {
    static long long int x,y,ans;
    ans=extend_gcd(a, DIV, x, y);
    if(x<0)
      return (x%DIV+DIV);
    return x;
  }
} r2;

int main() {
  printf("%lld\n", r2.reverse(2));
  return 0;
}
