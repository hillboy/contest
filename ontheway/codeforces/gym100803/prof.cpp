#include<stdio.h>
#include<algorithm>
#include<string.h>
using namespace std;
#define maxn 511

int p[maxn][maxn];

int i,j,n,m;

int fa[maxn],sum[maxn];

int findfa(int a) {
  if(fa[a]==a)
    return a;
  return fa[a]=findfa(fa[a]);
}

bool merge(int a, int b) {
  a=findfa(a);b=findfa(b);
  if(a==b)
    return false;
  if(sum[a]>sum[b])
    swap(a,b);
  sum[b]+=sum[a];
  fa[a]=b;
  return true;
}


struct edge {
  int a,b,c;
  bool chosen,ban;
  void output() {
    printf(" (%d %d) %d %d %d\n", a,b,c,chosen,ban);
  }
} q[50010];

bool cmp(const edge& a, const edge& b) {
  return a.c<b.c;
}

int mst1() {
  int i;
  for(i=1;i<=n;i++) {
    fa[i]=i;
    sum[i]=1;
  }
  int b=0;
  for(i=1;i<=m;i++) {
    if(merge(q[i].a, q[i].b)) {
      q[i].chosen=1;
      b+=q[i].c;
    }
  }
  return b;
}


int mst2() {
  int i;
  for(i=1;i<=n;i++) {
    fa[i]=i;
    sum[i]=1;
  }
  int a=0,b=0;
  for(i=1;i<=m;i++) {
    if(!q[i].ban) 
      if(merge(q[i].a, q[i].b)) {
        a++;
        b+=q[i].c;
      }
  }
  if(a==n-1)
    return b;
  return -1;
}

void make() {
  int i, temp, opt;
  int a=0,b=0;
  opt=mst1();
  for(i=1;i<=m;i++) {
    if(q[i].chosen) {
      q[i].ban = true;
      temp=mst2();
      if(temp<0 || temp != opt) {
        a++;
        b+=q[i].c;
      }
      q[i].ban = false;
    }
  }
  printf("%d %d\n", a,b);
}


int main() {
  scanf("%d %d", &n, &m);
  int a,b,c;
  for(i=1;i<=m;i++) {
    scanf("%d %d %d", &a, &b, &c);
    q[i].a=a;q[i].b=b;q[i].c=c;
  }
  sort(&q[1], &q[1+m], cmp);
  make();
  return  0;
}
