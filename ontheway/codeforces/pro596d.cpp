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

typedef long long int LD;
#define maxn 2010

int i,j,n,h;
double p;

int x[maxn];

double q[maxn][maxn][4];
bool checked[maxn][maxn][4];

double mymin(double a, double b) {
  return a<b?a:b;
}

double make(int l, int r, int state) {
  if(checked[l][r][state])
    return q[l][r][state];
  checked[l][r][state]=true;
  if(l==r) {
    // left
    if((state&1) && x[l] - x[l-1] < h) {
      if(state&2) {
        q[l][r][state] = mymin(x[l+1] - x[l], h);
      } else {
        assert(x[l+1] - x[l] >=h);
        q[l][r][state] = mymin(x[l+1] - x[l] - h, h);
      }
      //printf("%d %d %d %lf\n", l, r, state, q[l][r][state]);
      return q[l][r][state];
    }
    // right
    if(!(state&2) && x[r+1] - x[r] < h) {
      if(!(state&1)) {
        q[l][r][state] = mymin(x[l] - x[l-1], h);
      } else {
        assert(x[l] - x[l-1] >=h);
        q[l][r][state] = mymin(x[l] - x[l-1] - h, h);
      }
      //printf("%d %d %d %lf\n", l, r, state, q[l][r][state]);
      return q[l][r][state];
    }
    double left_space = x[l] - x[l-1], right_space = x[r+1] - x[r];
    if (state&1) {
      left_space -= h;
    }
    if (!(state & 2)) {
      right_space -=h;
    }
    assert(left_space>=0);
    assert(right_space>=0);
    q[l][r][state]= p * mymin(left_space,h) + (1-p) * mymin(right_space,h);
    //printf("%d %d %d %lf\n", l, r, state, q[l][r][state]);
    return q[l][r][state];
  }

  q[l][r][state]=0;

  // push left
  if((state&1) && x[l] - x[l-1] < h) {
    q[l][r][state] = make(l+1, r, state) + mymin(x[l+1] - x[l], h);
    return q[l][r][state];
  }

  // push right
  if(!(state&2) && x[r+1] - x[r] < h) {
    q[l][r][state] = make(l, r-1, state) + mymin(x[r] - x[r-1], h);
    return q[l][r][state];
  }

  // neither side being pushed. pick with 0.5
  //

  double left_space = x[l] - x[l-1], right_space = x[r+1] - x[r];
  if (state&1) {
    left_space -= h;
  }
  if (!(state & 2)) {
    right_space -=h;
  }

  // pick left
  q[l][r][state] +=
      (p) * (mymin(left_space, h) + make(l+1, r, (state&2)))
      + (1-p) * (make(l+1, r, (state&2) | 1) + mymin(x[l+1]-x[l], h));

  // pick right
  q[l][r][state] +=
      (p) * (make(l, r-1, (state&1)) + mymin(x[r]-x[r-1], h))
      + (1-p) * (mymin(right_space, h) + make(l, r-1, (state&1) | 2));
  //printf("%d %d %d %lf\n", l, r, state, q[l][r][state]);

  q[l][r][state]/=2;

  //printf("%d %d %d %lf\n", l, r, state, q[l][r][state]);
  return q[l][r][state];
}


int main() {
  scanf("%d %d %lf", &n, &h, &p);
  for1tr(i,n) {
    scanf("%d", &x[i]);
  }
  sort(&x[1], &x[n+1]);
  x[0] = -1000000000;
  x[n+1] = 1000000000;

  double ans = make(1, n, 2);
  printf("%.10lf\n", ans);
  return 0;
}
