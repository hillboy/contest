#include<stdio.h>
#include<algorithm>
#include<math.h>
#define maxn 100010
using namespace std;
#define pi acos(-1)

int i,j,n,m;

struct point {
  double x,y;
  void input() {
    scanf("%lf %lf", &x, &y);
  }
} P, p[maxn];;

inline double sqr(double a) {
  return a*a;
}

double dis(point& a, point& b) {
  return sqrt(sqr(a.x-b.x) + sqr(a.y-b.y));
}

double dis2(point& a, point& b, point& c) {
  double temp = (c.x-b.x)*(b.y-a.y) - (b.x-a.x)*(c.y-b.y);
  temp = abs(temp);
  temp /= dis(b,c);
  return temp;
}
double dis3(double x, double y, double x1, double y1, double x2, double y2, point a,point b, point c) {
  double cross = (x2 - x1) * (x - x1) + (y2 - y1) * (y - y1);
  if (cross <= 0) return sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));

  double d2 = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
  if (cross >= d2) return sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
  return dis2(a,b,c);

  double r = cross / d2;
  double px = x1 + (x2 - x1) * r;
  double py = y1 + (y2 - y1) * r;
  return sqrt((x - px) * (x - px) + (py - y1) * (py - y1));
}

int main() {
  scanf("%d", &n);
  P.input();
  double mindis = -1, maxdis=-1, temp;
  for(i=0;i<n;i++) {
    p[i].input();
    temp = dis(P, p[i]);
    if(mindis<0 || temp < mindis) {
      mindis = temp;
    }
    if(maxdis<0 || temp > maxdis) {
      maxdis = temp;
    }
  }
  p[n]=p[0];
  for(i=1;i<=n;i++) {
    temp = dis3(P.x, P.y, p[i].x, p[i].y, p[i-1].x, p[i-1].y, P, p[i], p[i-1]);
    if(mindis<0 || temp < mindis) {
      mindis = temp;
    }
    if(maxdis<0 || temp > maxdis) {
      maxdis = temp;
    }
  }

  printf("%.10lf\n", (sqr(maxdis) - sqr(mindis)) * pi);



  return 0;
}
