#include<stdio.h>

int i,j,n,m,now;

int p[1000][4];


int main() {
  scanf("%d %d", &n, &m);
  for(i=1;i<=n;i++) {
    p[i][0]=++now;
    p[i][3]=++now;
  }
  for(i=1;i<=n;i++) {
    p[i][1]=++now;
    p[i][2]=++now;
  }
  for(i=1;i<=n;i++) {
    if(p[i][1]<=m)
      printf("%d ", p[i][1]);
    if(p[i][0]<=m)
      printf("%d ", p[i][0]);
    if(p[i][2]<=m)
      printf("%d ", p[i][2]);
    if(p[i][3]<=m)
      printf("%d ", p[i][3]);
  }
  printf("\n");
  return 0;
}
