#include<stdio.h>
#define maxn 110000
int i,j,n,m;

int p[maxn];

int main(){
  scanf("%d %d",&n,&m);
  long long int ans=0,temp;
  for(i=1;i<=n;i++)
    scanf("%d",&p[i]);
  for(i=j=1;i<=n;i++){
    while(j<=n&&p[j]-p[i]<=m)
      j++;
    if(j-i>2){
      temp=j-i-1;
      temp*=temp-1;
      temp/=2;
      ans+=temp;
    }
  }
  printf("%I64d\n",ans);
  return 0;
}
