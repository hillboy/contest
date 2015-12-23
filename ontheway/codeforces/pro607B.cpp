#include<stdio.h>

#define maxn 511

int p[maxn][maxn];

int q[maxn];

int make(int a,int b) {
  if(p[a][b])
    return p[a][b];
  if(a==b) {
    p[a][b] = 1;
    return 1;
  }
  int i,now;
  p[a][b]=make(a,b-1) + 1;
  for(i=a+1;i<=b;i++) {
    if(q[i]==q[b]) {
      now = make(a,i-1) + make(i,b);
      if(now<p[a][b])
        p[a][b] = now;
    }
  }
  if(q[a]==q[b]) {
    if(a+1 == b) {
      now = 1;
    } else {
      now = make(a+1, b-1);
    }
    if(now<p[a][b])
      p[a][b] = now;
  }
  return p[a][b];
}

int main() {
  int i,n;
  scanf("%d", &n);
  for(i=1;i<=n;i++) {
    scanf("%d", &q[i]);
  }
  printf("%d\n", make(1,n));
  return 0;
}
