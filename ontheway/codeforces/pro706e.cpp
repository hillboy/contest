#include<stdio.h>
#include<algorithm>
using namespace std;

#define forlr(i,l,r) for(i=l;i<r;i++)
#define forrl(i,r,l) for(i=r-1;i>=l;i--)
#define for0r(i,r) forlr(i,0,r)

#define forltr(i,l,r) for(i=l;i<=r;i++)
#define for1tr(i,r) forltr(i,1,r)
#define forrtl(i,r,l) for(i=r;i>=l;i--)

#define forcnt(n) for(int cnt=n; cnt; cnt--)

#define maxn 1002
int i,j,n,m,q,num_q;

struct point {
  point *r, *d;
  int num;
} p[maxn][maxn];

void init() {
  forltr(i,0,n) {
    forltr(j,0,m) {
      p[i][j].r = &p[i][j+1];
      p[i][j].d = &p[i+1][j];
    }
  }
}

void make() {
  int ai,aj,bi,bj,w,h;
  point *a,*b, *ta, *tb;
  while(num_q--) {
    scanf("%d %d %d %d %d %d", &ai, &aj, &bi, &bj, &h, &w);
    a=&p[ai-1][0];
    forcnt(aj-1) {
      a=a->r;
    }
    b=&p[bi-1][0];
    forcnt(bj-1) {
      b=b->r;
    }
    ta=a;tb=b;
    forcnt(h) {
      ta=ta->d;
      tb=tb->d;
      swap(ta->r, tb->r);
    }
    forcnt(w) {
      ta=ta->r;tb=tb->r;
      swap(ta->d, tb->d);
    }
    ta=a;tb=b;
    forcnt(w) {
      ta=ta->r;tb=tb->r;
      swap(ta->d, tb->d);
    }
    forcnt(h) {
      ta=ta->d;
      tb=tb->d;
      swap(ta->r, tb->r);
    }
  }
  forltr(i,1,n) {
    a=&p[i][0];
    forcnt(m) {
      a=a->r;
      printf("%d ", a->num);
    }
    printf("\n");
  }
}

int main() {
  scanf("%d %d %d", &n, &m, &num_q);
  forltr(i,1,n) {
    forltr(j,1,m) {
      scanf("%d", &p[i][j].num);
    }
  }
  init();
  make();
  return 0;
}
