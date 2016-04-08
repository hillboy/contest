#include<stdio.h>
int i,j,n,m,ans,ansi;

int p[310000];

int main() {
  scanf("%d %d", &n, &m);
  for(i=1;i<=n;i++) {
    scanf("%d", &p[i]);
  }
  j=1;
  int c=0;
  for(i=1;i<=n;i++) {
    while(j<=n) {
      if(p[j]==0 && c>=m)
        break;
      if(p[j]==0)
        c++;
      j++;
    }
    if(j-i>ans)
      ans=j-i,ansi=i;
    if(p[i]==0)
      c--;
  }
  printf("%d\n", ans);
  for(i=ansi;i<ansi+ans;i++)
    p[i]=1;
  for(i=1;i<=n;i++)
    printf("%d ", p[i]);
  printf("\n");
  return 0;
}
