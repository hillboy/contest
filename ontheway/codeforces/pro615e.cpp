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


LD n;

LD makelv() {
  LD l = 1, r = 1000000000, mid;
  LD now;
  while(l<=r) {
    mid = (l+r)/2;
    now = mid*(mid+1)*3;
    if(now>=n) {
      r = mid - 1;
    } else {
      l = mid+1;
    }
  }
  return l;
}

int di[6][2] = {
  {-1,2},
  {-2,0},
  {-1, -2},
  {1, -2},
  {2, 0},
  {1, 2}
};


int main() {
  ios_base::sync_with_stdio(false);
  cin >> n;
  if (n==0) {
    printf("0 0\n");
    return 0;
  }
  LD lv = makelv();
  LD num = n - (lv*(lv-1))*3;

  LD x = 2 * (lv),  y = 0;
  int i;
  LD next = 0, pre=0;
  for(i=0;i<6;i++) {
    next += lv;
    if(num<=next) {
      cout << x + di[i][0] * (num-pre) << " " << y + di[i][1] * (num-pre) << endl;
      return 0;
    }
    x += di[i][0] * lv;
    y += di[i][1] * lv;
    pre=next;
  }

  return 0;
}
