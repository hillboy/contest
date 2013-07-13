#include<stdio.h>
#define maxn 1001000
int i,j,n,m;

int p[maxn];

int main(){
  scanf("%d",&n);
  j=(1<<26)-1;
  for (i=n;i;i--){
    if(p[i]==0){
      int r= j-i;
      if(r>n||p[r]>0){
        j/=2;
        i++;
        continue;
      }
      p[r]=i;
      p[i]=r;
    }
  }
  long long int ans=0;
  for(i=0;i<=n;i++){
    ans+=p[i]^i;
  }
  printf("%I64d\n",ans);
  for(i=0;i<=n;i++){
    printf("%d ",p[i]);
  }
  return 0;
}
