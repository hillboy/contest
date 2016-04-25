#include<stdio.h>
#include<complex>
#include<math.h>
#include<vector>
using namespace std;
#define maxn 20

typedef double T;
typedef complex<T> Pt;
typedef const Pt &PT;
const T EPS=1e-10, INF=1e100, PAI=acos(-1.0);
#define X real()
#define Y imag()
T crossp(PT a,PT b) { return a.X*b.Y-a.Y*b.X; }
T crossp(PT o, PT a, PT b) { return crossp(a-o, b-o); }
T innerp(PT a,PT b) { return a.X*b.X+a.Y*b.Y; }
inline int sign(T a) { return a<-EPS? -1: a>EPS? 1: 0; }
void scan(Pt &p) {
	double x,y; scanf("%lf %lf",&x,&y); p=Pt(x,y);
}
bool pt_less(PT a,PT b) {
	int sx=sign(a.X-b.X);
	if(sx) return sx<0; else return sign(a.Y-b.Y)<0;
}
bool pt_equal(PT a,PT b) {
	return sign(a.X-b.X)==0 && sign(a.Y-b.Y)==0;
}
struct PtLess {
	bool operator()(PT a,PT b) const {
		int sx=sign(a.X-b.X);
		if(sx) return sx<0; else return sign(a.Y-b.Y)<0;
	}
};
bool Inter_Circ(Pt oa,T a, Pt ob,T b, Pt &s1,Pt &s2) {
	Pt v=ob-oa, h=v*Pt(0,1);
	T c=sqrt(norm(v));
	if(sign(c-abs(a-b))<0 || sign(c-a-b)>0) return 0;
	T q=acos((a*a+c*c-b*b)/(2*a*c));
	h=a*sin(q)*h/sqrt(norm(h));
	s1=oa+v*(a*cos(q)/c)+h, s2=s1-h*2.;
	return 1;
}
bool Outter_Circle_Tangent(Pt o1, T r1, Pt o2, T r2,
		Pt &u1, Pt &u2, Pt &d1, Pt &d2) {

	T d=norm(o2-o1), dr=abs(r2-r1);
	if(sign(d-dr*dr)<=0) return false;
	d=sqrt(d);

	int chg=0;
	if(sign(r1-r2)>0) swap(r1,r2), swap(o1,o2), chg=1;
	T c=-dr/d, s=sqrt(1-c*c);
	Pt v=o2-o1, ru=Pt(c,s), rd=Pt(c,-s);
	u1=o1+v*ru/d*r1;
	u2=o2+v*ru/d*r2;
	d1=o1+v*rd/d*r1;
	d2=o2+v*rd/d*r2;
	if(chg) swap(u1,u2), swap(d1,d2);
	return true;
}


int i,j,n,m;

T r = 100;

Pt p[30], O, des;

Pt input() {
  T a,b;
  scanf("%lf %lf", &a, &b);
  return Pt(a,b);
}

vector<Pt> all;

int color[1000];

double q[1000][1000]; 

inline bool prepare() {
  for(i=1;i<=n;i++) {
    if(norm(p[i] - O) < r*r) {
      return false;
    }
    if(norm(p[i] - des) < r*r) {
      return false;
    }
    // Outter_Circle_Tangent
    
    Pt u1, u2, d1, d2;
    Outter_Circle_Tangent(O, 0, p[i], r, u1, u2, d1, d2);
  }
  for(i=1;i<=n;i++) {
    for(j=i+1;j<=n;j++) {

    }
  }
}

int main() {
  scanf("%d", &n);
  O=Pt(0,0);
  des = input();
  for(i=1;i<=n;i++) {
    p[i]=input();
  }
  prepare();
  return 0;
}
