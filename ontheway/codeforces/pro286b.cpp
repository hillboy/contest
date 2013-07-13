#include<stdio.h>
#define maxn 1001000
int p[maxn*2];
int i,j,n,m;
int main(){
  scanf("%d",&n);
  for(i=1;i<=n;i++){
    p[i]=i;
  }
  for(i=2;i<=n;i++){
    int last=0,temp;
    for (j=i-1;j<n+i-1;j+=i){
      temp=p[j];
      p[j]=last;
      last=temp;
    }
    p[n+i-1]=last;
  }
  for(i=0;i<n;i++){
    printf("%d ",p[i+n]);
  }
  return 0;
}
