#include<stdio.h>
#include<algorithm>
using namespace std;
#define maxn 100010

struct point {
  int a,b,num;
  bool ans;
} p[maxn];

bool cmp1(const point& a, const point& b) {
  if(a.a == b.a) {
    return a.b < b.b;
  }
  return a.a<b.a;
}

bool cmp2(const point& a, const point& b) {
  return a.num < b.num;
}

int i,j,n,m;

int main() {
  scanf("%d", &n);
  for(i=0;i<n;i++) {
    scanf("%d %d", &p[i].a, &p[i].b);
    p[i].num = i;
  }
  sort(p, p+n, cmp1);
  p[0].ans = p[1].ans = 1;
  if(p[0].a == p[1].a) {
    i=2;
    while(p[i].a==p[0].a)
      i++;
    p[i].ans=1;
  } else {
    i=2;
    while((long long int)(p[i].b-p[1].b)*(p[1].a - p[0].a) == (long long int)(p[1].b-p[0].b)*(p[i].a - p[1].a)) {
      i++;
    }
    p[i].ans=1;
  }
  sort(p, p+n, cmp2);
  for(i=0;i<n;i++) {
    if(p[i].ans)
      printf("%d ",p[i].num+1);
  }
  return 0;
}
