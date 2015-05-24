// merge sort tree
#include<stdio.h>
#include<algorithm>
using namespace std;
#define maxn 201000

int i,j,n,m;

int pp[maxn];

struct point {
  static int p[maxn*30],t,m;

  int l,r;
  point *ln, *rn;

  void prepare(int l, int r);
  int count(int num);
}nodes[maxn*6];

int count(point& a, int l, int r, int left, int right, int num) {
  if(l==left && r==right) {
    return a.count(num);
  }
  int mid = (l+r)/2, ans = 0;
  if(left<=mid) {
    ans = count(*a.ln, l, mid, left, right<mid?right:mid, num);
  }
  if(right>mid) {
    ans += count(*a.rn, mid+1, r, left > mid ? left : mid+1, right, num);
  }
  return ans;
}


int main() {
  scanf("%d",&n);
  for(i=0;i<n;i++) {
    scanf("%d", &pp[i]);
  }
  // must start from nodes[0]
  nodes[0].prepare(0,n-1);
  int ans;
  for(i=1;i<n;i++){
    ans = 0;
    for(j=0;j*i+1<n;j++) {
      ans+=count(nodes[0], 0, n-1, i*j+1, i*j+i <n ? i*j+i:n-1, pp[j]);
    }
    printf("%d ", ans);
  }
  return 0;
}

void point::prepare(int l, int r) {
  if (l>r)
    return;
  if(l == r) {
    t++;
    // change this pp pp[] if read from another array.
    p[t]=pp[l];
    this->l=this->r=t;
    return;
  }
  int mid = (l+r)/2, il, ir;
  ln = &nodes[++m];
  ln->prepare(l, mid);
  rn = &nodes[++m];
  rn ->prepare(mid+1, r);
  il = ln->l;
  ir = rn->l;
  this->l=t+1;
  while(il<=ln->r || ir <= rn->r) {
    t++;
    if(il>ln->r) {
      p[t]=p[ir++];
    } else if (ir > rn->r){
      p[t]=p[il++];
    } else if (p[il] < p[ir]) {
      p[t]=p[il++];
    } else {
      p[t]=p[ir++];
    }
  }
  this->r=t;
}

int point::count(int num) {
  return 
    std::lower_bound(&p[l], &p[r+1], num) - &p[l];
}
int point::p[maxn*30],point::t=0,point::m=0;
