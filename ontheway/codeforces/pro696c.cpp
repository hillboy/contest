#include<iostream>
#include<string.h>
#include<algorithm>
#include<map>
#include<set>
#include<vector>
#include<map>
#include<string>
using namespace std;
#define maxn 20010000
#define div 1000000007

#define forlr(x,l,r) for(x=l;x<(int)r;++x)
#define for1(x,y) forlr(x,0,y)
#define forn(x) for1(x,n)
#define sz(x) (int)x.size()

typedef long long int LD;

int n;

struct matrix {
  LD p[2][2];
} *ans1 , *now1, *resans1, *resnow1, *temp;

void mul_ans1(LD a[2][2], LD b[2][2]) {
  resans1->p[0][0] = (a[0][0] * b[0][0] + a[0][1] * b[1][0]) % div;
  resans1->p[0][1] = (a[0][0] * b[0][1] + a[0][1] * b[1][1]) % div;
  resans1->p[1][0] = (a[1][0] * b[0][0] + a[1][1] * b[1][0]) % div;
  resans1->p[1][1] = (a[1][0] * b[0][1] + a[1][1] * b[1][1]) % div;
  swap(ans1, resans1);
}

void mul_now1(LD a[2][2], LD b[2][2]) {
  resnow1->p[0][0] = (a[0][0] * b[0][0] + a[0][1] * b[1][0]) % div;
  resnow1->p[0][1] = (a[0][0] * b[0][1] + a[0][1] * b[1][1]) % div;
  resnow1->p[1][0] = (a[1][0] * b[0][0] + a[1][1] * b[1][0]) % div;
  resnow1->p[1][1] = (a[1][0] * b[0][1] + a[1][1] * b[1][1]) % div;
  swap(now1, resnow1);
}



matrix* init(long a, long b, long c, long d) {
  matrix *p = new matrix();
  p->p[0][0] = a;
  p->p[0][1] = b;
  p->p[1][0] = c;
  p->p[1][1] = d;
  return p;
}

LD rev = 500000004;

LD ans = 2, now;

void get1(LD p) {
  swap(now1, ans1);
  ans1->p[0][0] = 1;
  ans1->p[0][1] = 0;
  ans1->p[1][0] = 0;
  ans1->p[1][1] = 1;

  now = ans;
  ans = 1;
  while (p > 0) {
    if ((p & 1) > 0) {
      ans *= now;
      ans %= div;
      mul_ans1(ans1->p, now1->p);
    }
    now *= now;
    now %= div;
    mul_now1(now1->p, now1->p);
    p >>= 1;
  }
  /*
     cout << ans1.p[1][0] << "/" << ans << endl;
     return;
     cout << ans << endl;
     cout << ans1.p[0][0] << " " << ans1.p[0][1]  << " "
     << ans1.p[1][0] << " " << ans1.p[1][1] << endl;
     */
}

int main() {
  ios_base::sync_with_stdio(false);
  cin >> n;
  LD m;
  ans1 = init(0, 2, 1, 1);
  resans1 = init(0,0,0,0);
  resnow1 = init(0,0,0,0);
  now1 = init(0,0,0,0);
  int i;
  for1(i,n) {
    cin >> m;
    get1(m);
  }
  LD a = ans1->p[1][1] - ans1->p[1][0];
  if (a < 0) {
    a += div;
  }
  a = a * rev % div;
  cout << (a);
  cout << ("/");
  cout << (ans * rev % div);
  return 0;
}
