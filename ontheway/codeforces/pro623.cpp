#include<stdio.h>
#define maxn 511

bool g[maxn][maxn];

int ans[maxn];

int i,j,n,m;

bool make(int a, int now) {
  if(ans[a]) {
    if(ans[a]==now)
      return true;
    return false;
  }
  ans[a]=now;
  int i;
  if(now==2) {
    for(i=1;i<=n;i++) {
      if(i!=a && !g[a][i]) {
        return false;
      }
    }
    return true;
  }
  for(i=1;i<=n;i++) {
    if(i!=a && !g[a][i]) {
      if(!make(i,4-now)) {
        return false;
      }
    }
  }
  return true;
}

int main() {
  scanf("%d %d", &n, &m);
  int a,b;
  for(i=1;i<=m;i++) {
    scanf("%d %d", &a, &b);
    g[a][b]=g[b][a]=1;
  }
  for(i=1;i<=n;i++)
    for(j=1;j<=n;j++) if(i!=j)
      if(!g[i][j] && ans[i]==0) {
        if(!make(i, 1)) {
          printf("No\n");
          return 0;
        }
      }
  for(i=1;i<=n;i++) {
    for(j=1;j<=n;j++) {
      if(ans[i] == 1 && ans [j] == 3) {
        if(g[i][j]) {
          printf("No\n");
          return 0;
        }
      }
    }
  }
  printf("Yes\n");
  for(i=1;i<=n;i++) {
    if(ans[i]) {
      printf("%c", ans[i]-1 + 'a');
    } else {
      printf("b");
    }
  }
  printf("\n");
  return 0;
}
