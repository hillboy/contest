#include<stdio.h>
#include<math.h>
#include<algorithm>

using namespace std;
#define pi (acos(-1))

#define maxn 300100
#define maxm (maxn*32)

struct point {
  double lcos, lsin;
  double ang;
  void update() {
    double tempcos = lcos*cos(ang) - lsin*sin(ang);
    double tempsin = lsin*cos(ang) + lcos*sin(ang);
    lcos = tempcos;
    lsin = tempsin;
    ang=0;
  }
  void updatelen(double l) {
    double ll = sqrt(lcos*lcos+lsin*lsin);
    lcos += lcos/ll * l;
    lsin += lsin/ll * l;
  }
};

point tree[maxm];


void init(int a, int l, int r, int pos) {
  auto& n = tree[a];
  if(l==r) {
    n.lcos = 1;
    n.lsin = 0;
    return;
  }
  int mid = (l+r)/2;
  if(pos <= mid ) {
    init(a*2, l, mid, pos);
  } else {
    init(a*2+1, mid+1, r, pos);
  }
  n.lcos = tree[a*2].lcos + tree[a*2+1].lcos;
  n.lsin = tree[a*2].lsin + tree[a*2+1].lsin;
}

void update(int a) {
  auto& n = tree[a];
  if(a*2<maxm)
    tree[a*2].ang += n.ang;
  if(a*2+1<maxm)
    tree[a*2+1].ang += n.ang;
  n.update();
}

void update2(int a, int l, int r, int left, int right, double ang) {
  auto& n = tree[a];
  if(l==left && r == right) {
    n.ang += ang;
    update(a);
    return;
  }
  update(a);
  int mid = (l+r)/2;
  if(left <=mid) {
    update2(a*2, l, mid, left, min(right, mid), ang);
  }
  if(right>mid) {
    update2(a*2+1, mid+1, r, max(left, mid+1), right, ang);
  }
  update(a*2);
  update(a*2+1);
  n.lcos = tree[a*2].lcos + tree[a*2+1].lcos;
  n.lsin = tree[a*2].lsin + tree[a*2+1].lsin;
}

void update1(int a, int l, int r, int pos, double sz) {
  auto& n = tree[a];
  if(l==r) {
    n.update();
    n.updatelen(sz);
    return;
  }
  if(n.ang > 0) {
    update(a);
  }
  int mid = (l+r)/2;
  if(pos <= mid ) {
    update1(a*2, l, mid, pos, sz);
  } else {
    update1(a*2+1, mid+1, r, pos, sz);
  }
  update(a*2);
  update(a*2+1);
  n.lcos = tree[a*2].lcos + tree[a*2+1].lcos;
  n.lsin = tree[a*2].lsin + tree[a*2+1].lsin;
}


int i,j,n,m;

int main() {
  scanf("%d %d", &n, &m);
  for(i=1;i<=n;i++) {
    init(1, 1, n, i);
  }
  int a,b,c;
  while(m--) {
    scanf("%d", &a);
    if(a==1) {
      scanf("%d %d", &b, &c);
      update1(1, 1, n, b, c);
    } else {
      scanf("%d %d", &b, &c);
      update2(1, 1, n, b, n, 2*pi - c*pi/180);
    }
    update(1);
    printf("%.10lf %.10lf\n", tree[1].lcos, tree[1].lsin);
  }
  return 0;
}
