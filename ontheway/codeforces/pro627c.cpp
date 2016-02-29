#include<stdio.h>
#include<algorithm>
using namespace std;

typedef long long int LD;
#define maxn 201000

int d,n,m;

int i,j;

struct point {
  int a,b;
}p[maxn], q[maxn];

int t;

bool cmp1(const point& a, const point& b) {
  return a.a < b.a;
}

bool cmp2(const point& a, const point& b) {
  return a.b > b.b;
}



void make() {
  int now=m, nowstart=0, tank=m;
  LD cost = 0;

  int next = 0;

  for(i=1;i<=n;i++) {
    if(p[i].a<=m) {
      q[t]=p[i];
      t++;
      push_heap(q, q+t, cmp2);
    } else {
      break;
    }
  }
  next=i;

  int dis;

  p[n+1].a=d;
  LD tmp;

  while(now < d) {
    if(t==0) {
      printf("-1\n");
      return;
    }
    if(q[0].a < nowstart) {
      pop_heap(q, q+t, cmp2);
      t--;
      continue;
    }
    int left = q[0].a - nowstart;
    dis = p[next].a - now;
//    printf("%d %d\n", left, dis);
    if (dis >left) {
      tmp = q[0].b;
      tmp *= (left);
      cost += tmp;
      now+=left;
      nowstart = q[0].a;
      pop_heap(q, q+t, cmp2);
      t--;
      continue;
    } else {
      tmp = q[0].b;
      tmp *= (dis);
      cost += tmp;
      now+=dis;
      nowstart += dis;
      q[t]=p[next];
      next++;
      t++;
      push_heap(q, q+t, cmp2);
      continue;
    }
  }
  printf("%lld\n", cost);
}

int main() {
  scanf("%d %d %d", &d, &m, &n);
  for(i=1;i<=n;i++) {
    scanf("%d %d", &p[i].a, &p[i].b);
  }
  sort(&p[1], &p[n+1], cmp1);
  make();
  return 0;
}
