#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<map>
#include<set>
#include<vector>
#include<map>
#include<string>
using namespace std;
#define maxn 1001000

#define forlr(x,l,r) for(x=l;x<(int)r;++x)
#define for1(x,y) forlr(x,0,y)
#define forn(x) for1(x,n)
#define sz(x) (int)x.size()

typedef long long int LD;

int i,j,n,m;

LD gcd(LD a,LD b) {
  if(a>b)
    return gcd(b,a);
  if(a==0)
    return b;
  return gcd(b%a,a);
}

typedef pair<LD,LD> La;

La add(La a, La b) {
  LD k = a.second*b.second / gcd(a.second, b.second);
  a.first *= k/a.second;
  b.first *= k/b.second;
  return make_pair(a.first + b.first, k);
}


La a,b;

int main() {
  a=make_pair(1,2);
  b=make_pair(1,4);
  La now;
  for1(i, 30) {
    now = add(a,b);
    now.second *= 2;
    printf("%lld/%lld\n", now.first, now.second);
    swap(a,b);
    b=now;
  }
  return 0;
}
