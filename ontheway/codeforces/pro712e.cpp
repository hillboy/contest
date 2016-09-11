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

double p[maxn], q[maxn];

double R[maxn];

int i,j,n,m;

void init(int a, int l, int r) {
  if (l==r) {
    p[a] = q[a] = R[l];
    return;
  }
  int mid = (l+r)/2;
  init(a*2, l, mid);
  init(a*2+1, mid+1, r);
  p[a] = p[a*2] * p[a*2+1] * ( 1/(1-q[a*2]*(1-p[a*2+1])));
  q[a] = q[a*2+1] + (1-q[a*2+1]) * q[a*2] * p[a*2+1] * ( 1/(1 - q[a*2]*(1-p[a*2+1])));
}

void modify(int a, int l, int r, int num, double now) {
  if (l==r) {
    p[a] = q[a] = now;
    return;
  }
  int mid = (l+r)/2;
  if(num<=mid)
    modify(a*2, l, mid, num, now);
  else
    modify(a*2+1, mid+1, r, num, now);
  p[a] = p[a*2] * p[a*2+1] * (1/(1-q[a*2]*(1-p[a*2+1])));
  q[a] = q[a*2+1] + (1-q[a*2+1]) * q[a*2] * p[a*2+1] * ( 1/(1 - q[a*2]*(1-p[a*2+1])));
}

int mymin(int a,int b) {
  return a<b?a:b;
}
int mymax(int a,int b) {
  return a>b?a:b;
}

void output(pair<double, double> a) {
  printf("(%lf, %lf)\n", a.first, a.second);
}
void output(double a, double b) {
  printf("(%lf, %lf)\n", a, b);
}

pair<double, double> ans(int a, int l, int r, int left, int right) {
  if(l==left && r == right) {
    return make_pair(p[a], q[a]);
  }
  int mid = (l+r)/2;
  if(left>mid) {
    return ans(a*2+1, mid+1, r, left, right);
  }
  if(right<=mid) {
    return ans(a*2, l, mid, left, right);
  }
  pair<double, double> ll = ans(a*2, l, mid, left, mymin(mid, right));
  pair<double, double> rr = ans(a*2+1, mid+1, r, mymax(mid+1, left), right);
  double pp = ll.first * rr.first * (1/(1-ll.second*(1-rr.first)));
  double qq = rr.second + (1-rr.second) * ll.second * rr.first * (1/(1 - ll.second*(1-rr.first)));
  return make_pair(pp, qq);

}

int main() {
  scanf("%d %d", &n, &m);
  int a,b,i;
  for1tr(i, n) {
    scanf("%d %d", &a, &b);
    R[i] = 1.0 * a / b;
  }
  init(1,1,n);
  while(m--) {
    scanf("%d", &a);
    if(a==1) {
      scanf("%d %d %d", &i, &a, &b);
      modify(1, 1, n, i, 1.0*a/b);
    } else {
      scanf("%d %d", &a, &b);
      auto answer = ans(1, 1, n, a, b);
      printf("%.8lf\n", answer.first);
    }
  }
  return 0;
}

