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

#define maxn 10010

struct point {
  double x,y;
  point(double a, double b) : x(a) , y(b){};
  point() : x(0) , y(0){};
  double dis() {
    return sqrt(x*x + y*y);
  }
} p[maxn];


int i,j,n,m,u,v;


point del(point a,point b) {
  return point(b.x - a.x, b.y - a.y);
}

double cross(point a,point b) {
  return 1.0*a.x*b.y - 1.0*a.y*b.x;
}

// c on the right of a->b
bool right(point a,point b,point c) {
  return cross(del(a,b), del(a,c)) < 0;
}

bool touch() {
  point o(0,0), c(m*1.0/u*v, m);
  for1tr(i,n) {
    if(cross(p[i], c) * cross(p[i+1],c) < 0)
      return true;
  }
  return false;
}

double rightway() {
  int r=1;
  double ans = 0;
  point o(0,0), c(m*1.0/u*v, m);
  for1tr(i,n) {
    if(cross(p[r], p[i]) < 0) {
      r = i;
    }
  }
  ans += p[r].x / v;
  i = r+1;
  if (i>n)
    i=1;
  while(i!=r) {
    if(right(p[i-1], point(p[i-1].x + v, p[i-1].y + u) , p[i])) {
      ans += (p[i].x - (p[i-1<1?n:i-1]).x) / v;
    } else {
      i--;
      if(i<1)i=n;
      break;
    }
    i++;
    if (i>n)
      i=1;
  }
  ans += (m-p[i].y)/u;
  return ans;
}



int main() {
  scanf("%d %d %d %d", &n, &m, &v, &u);
  for1tr(i, n) {
    scanf("%lf %lf", &p[i].x, &p[i].y);
  }
  p[n+1]=p[1];
  p[0] = p[n];
  if(!touch()) {
    printf("%.10lf\n", m*1.0/u);
    return 0;
  }
  double r = rightway();
  printf("%.10lf\n", r);
  return 0;
}
