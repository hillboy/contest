#include<stdio.h>
#include<string.h>
#define maxn 1101

int p[maxn];

int d[maxn];

int s[maxn];

int i,j,n,m;

int main(){
  scanf("%d %d",&n,&m);
  for(i=1;i<=n;i++){
    scanf("%d",&d[i]);
  }
  for(i=1;i<=n;i++){
    scanf("%d",&s[i]);
  }
  int now=0,ans=0;
  for(i=1;i<=n;){
    // printf("%d %d %d\n",i,now,ans);

    for(j=i;j<=n;j++){
      // printf("     %d %d %d\n",j,now,ans);
      now+=s[j];
      if(now<d[j]){
        int a=(d[j]-now)/s[i];
        if((d[j]-now)%s[i])
          a++;
        now+=a*s[i];
        ans+=a*m;
        ans+=d[j];
        now-=d[j];
      }else{
        ans+=d[j];
        now-=d[j];
      }

      if(s[j+1]>s[i]){
        break;
      }
    }
    i=j+1;
  }
  printf("%d\n",ans);
  return 0;
}
