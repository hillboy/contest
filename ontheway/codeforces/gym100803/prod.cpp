#include<stdio.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define eps (1e-9)

int d,n,bo;

int m, i,j;

pair<int, int> p[20];

bool solve(double a,double b, double c, double& x1, double& x2) {
  double delta=b*b-4*a*c;
  if(delta<0 && delta+eps>=0)
    delta=0;
  if(delta<0)
    return false;
  delta=sqrt(delta);
  x1=(-b+delta)/2;
  x2=(-b-delta)/2;
  return true;
}

bool work(double k, double dis) {
  if(k<dis)
    return false;
  double vx = (sqrt(k+dis) - sqrt(k-dis))/2;
  double vy = (sqrt(k+dis) + sqrt(k-dis))/2;
  if(vx<0)
    return false;
  int i;
  double x,y;
  for(i=1;i<=n;i++) {
    x=p[i].first;
    x-= int(x/dis) * dis;
    y = x*(-x + dis)/2/vx/vx;
    if(y<p[i].second)
      return false;
  }
  return true;
}

double solvebo(int a) {
  double dis = d*1.0/(a+1);
  double l = 0, r = 1e20, mid;
  int iter;
  for(iter = 0 ; iter < 1000;iter++) {
    mid=(l+r)/2;
    if(work(mid, dis)) {
      r=mid;
    } else {
      l=mid;
    }
  }
  return l;
}

void make() {
  int i;
  double ans = solvebo(0), temp;
  for(i=1;i<=bo;i++) {
    temp=solvebo(i);
    if(temp<ans)
      ans=temp;
  }
  printf("%.8lf\n", sqrt(ans));
}

int main() {
  scanf("%d %d %d", &d, &n, &bo);
  int a,b;
  for(i=1;i<=n;i++) {
    scanf("%d %d", &a, &b);
    p[i]=make_pair(a,b);
  }
  make();
  return 0;
}
