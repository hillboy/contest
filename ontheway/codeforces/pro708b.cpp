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
#define sz(x) ((int)x.size())

typedef long long int LD;

#define maxn 1000000

int a00, a01, a10, a11;
LD a0, a1;

// num = 0 is special. a could be 0 or 1.
LD get_a(LD num) {
  if (num==0) {
    return 0;
  }
  LD a = 2;
  while(a*(a-1)/2 < num) {
    a++;
  }
  if(a*(a-1)/2 == num) {
    return a;
  }
  return -1;
}


int main() {
  scanf("%d %d %d %d", &a00, &a01, &a10, &a11);
  a0 = get_a(a00);
  a1 = get_a(a11);
  if(a0 < 0 || a1 < 0) {
    printf("Impossible\n");
    return 0;
  }
  if(a0*a1==0) {
    if(a10 + a01 == 0) {
      if(a0 + a1 ==0) {
        printf("0\n");
        return 0;
      } else {
        while(a0--) {
          printf("0");
        }
        while(a1--) {
          printf("1");
        }
      }
      return 0;
    } else {
      if(a0==0) {
        a0=1;
      }
      if(a1==0) {
        a1=1;
      }
    }
  }
  //printf("%lld %lld\n", a0, a1);
  if(a0*a1 != a10 + a01) {
    printf("Impossible\n");
    return 0;
  }
  int zero_after = a10 / a1;
  int zero_mid = a10 % a1;
  int zero_before = a0 - zero_after;
  if(zero_mid) {
    zero_before--;
  }
  forcnt(zero_before) {
    printf("0");
  }
  forcnt(zero_mid) {
    printf("1");
  }
  if(zero_mid) {
    printf("0");
  }
  forcnt(a1 - zero_mid) {
    printf("1");
  }
  forcnt(zero_after) {
    printf("0");
  }
  return 0;
}
