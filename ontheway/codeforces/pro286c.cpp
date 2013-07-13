#include<stdio.h>
#define maxn 1001000
int p[maxn];
int s[maxn];
int myabs(int a){
  return a<0?-a:a;
}
int i,j,n,m;
int main(){
  scanf("%d",&n);
  for(i=1;i<=n;i++){
    scanf("%d",&p[i]);
  }
  scanf("%d",&m);
  for(i=1;i<=m;i++){
    scanf("%d",&j);
    p[j]=-p[j];
  }
  int t=0;
  for(i=n;i;i--){
    if(p[i]<0){
      s[t++]=-p[i];
    } else {
      if (t>0&&s[t-1]==p[i]){
        t--;
      }else {
        s[t++]=p[i];
        p[i]=-p[i];
      }
    }
  }
  if (t>0){
    printf("NO\n");
  } else {
    printf("YES\n");
    for(i=1;i<=n;i++){
      printf("%d ",p[i]);
    }
  }
  return 0;
}
