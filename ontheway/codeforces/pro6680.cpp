#include<stdio.h>

#define maxn 111

int p[maxn][maxn];

int i,j,n,m,q;

int ans[maxn*maxn];

int main() {
  scanf("%d %d %d", &n, &m, &q);
  int t=0;
  for(i=0;i<n;i++)
    for(j=0;j<m;j++) {
      p[i][j]=t++;
    }
  int a,b,c,d;
  while(q--) {
    scanf("%d", &a);
    if(a==1) {
      scanf("%d", &b);
      b--;
      c=p[b][0];
      for(i=0;i<m-1;i++)
        p[b][i]=p[b][i+1];
      p[b][i]=c;
    } else if(a==2) {
      scanf("%d", &b);
      b--;
      c=p[0][b];
      for(i=0;i<n-1;i++)
        p[i][b]=p[i+1][b];
      p[i][b]=c;
    } else {
      scanf("%d %d %d", &b, &c, &d);
      b--;c--;
      ans[p[b][c]]=d;
    }
  }
  t=0;
  for(i=0;i<n;i++) {
    for(j=0;j<m-1;j++) {
      printf("%d ",ans[t++]);
    }
    printf("%d\n", ans[t++]);
  }

  return 0;
}

