#include<stdio.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define maxn 1001000
#define eps (1e-9)


double p[maxn], q[maxn];

double AA[maxn], BB[maxn];

int i,j,n,m;

bool solve(double a, double b, double c, double& x1, double& x2) {
  double delta = b*b - 4*a*c;
  if(delta < 0) {
    if(delta+eps > 0) 
      delta=0;
    else 
      return false;
  }
  delta=sqrt(delta);
//  printf("%lf %lf %lf %lf\n", a,b,c,delta);
  x1=(-b+delta)/2/a;
  x2=(-b-delta)/2/a;
  return true;
}

void test1() {
  double x1,x2;
  solve(1, -1, 0.25, x1, x2);
  printf("%lf %lf\n", x1, x2);
}

void fixneg(double& a) {
  if(a<0 && a+1e-9>=0)
    a=0;
}

bool solve(int i, double a,double b) {
  if(a>1+1e-6 || b> 1+1e-6)
    return false;
  if(i>n)
    return true;
  double A,B, x1,x2,y1,y2;
    A=AA[i];
    B=BB[i];
    bool ans = solve(1, -(a-b+A), B-b*A, x2, x1);
//    printf("%d\n", ans);
    y1=A-x1;
    y2=A-x2;
//    printf("(%lf %lf) (%lf %lf) \n", x1,y1, x2,y2);
    fixneg(x1);
    fixneg(y1);
    fixneg(x2);
    fixneg(y2);
    if(x1<0|| y1 < 0) {
      x1=x2;
      y1=y2;
      if(x1<0|| y1 < 0) {
        return false;
      }
      p[i]=x1;
      q[i]=y1;
      a+=y1;
      b+=x1;
      return solve(i+1, a,b);
    }
    swap(x1, x2);
    swap(y1, y2);
    if(x1<0|| y1 < 0 ) {
      x1=x2;
      y1=y2;
      if(x1<0|| y1 < 0) {
        return false;
      }
      p[i]=x1;
      q[i]=y1;
      a+=y1;
      b+=x1;
      return solve(i+1, a,b);
    }
    p[i]=x1; q[i]=y1;
    if(solve(i+1,a+y1,b+x1))
      return true;
    swap(x1, x2);
    swap(y1, y2);
    p[i]=x1; q[i]=y1;
    return solve(i+1,a+y1,b+x1);
}


int main() {
  scanf("%d", &n);
  for(i=1;i<=n;i++) {
    scanf("%lf", &BB[i]);
  }
  for(i=1;i<=n;i++) {
    scanf("%lf", &AA[i]);
    AA[i]+=BB[i];
  }
  bool ans = solve(1, 0,0);
  while(!ans);
  for(i=1;i<n;i++)printf("%.8lf ", p[i]);printf("%.8lf\n", p[i]);
  for(i=1;i<n;i++)printf("%.8lf ", q[i]);printf("%.8lf\n", q[i]);
  return 0;
}
