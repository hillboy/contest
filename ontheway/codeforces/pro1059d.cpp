#include<stdio.h>
#include<cmath>
#include<algorithm>
using namespace std;

#define maxn 100100
#define maxm 1e30

int i,j,n,m;

struct point {
  double x,y;
} p[maxn];

pair<double, double> q[maxn];

bool checkit(double a) {
  for(i=1;i<=n;i++) {
    if(p[i].y>=2*a)
      return false;
    double k = sqrt(a*a - (p[i].y-a)*(p[i].y-a));
    q[i].first = p[i].x-k;
    q[i].second = p[i].x+k;
  }
  sort(&q[1], &q[n+1]);
  double minx = 1e100;
  for(i=1;i<=n;i++) {
    if(q[i].first > minx)
      return false;
    if(q[i].second <minx)
      minx = q[i].second;
  }
  return true;
}

void make() {
  double l = 0, r = 1e15, mid;

  int i;
  for(i=1;i<=100;i++) {
    mid=(l+r)/2;
    if(checkit(mid)) {
      r = mid;
    } else {
      l=mid;
    }
  }
  printf("%.10lf\n", l);
}

int main() {
  scanf("%d", &n);
  bool pos = false, neg = false;
  for(i=1;i<=n;i++) {
    scanf("%lf %lf", &p[i].x, &p[i].y);
    if(p[i].y>0) pos = true;
    else neg = true;
  }
  if(neg && pos) {
    printf("-1\n");
    return 0;
  }
  if(neg) {
    for(i=1;i<=n;i++)
      p[i].y=-p[i].y;
  }
  make();
  return 0;
}
