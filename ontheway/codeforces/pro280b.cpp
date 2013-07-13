#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
#define maxn 101000
int l[maxn],r[maxn],fa[maxn];
int p[maxn],n,m,i,j;
int main(){
  scanf("%d",&n);
  for(i=1;i<=n;i++){
    scanf("%d",&p[i]);
    if(m==0){
      m=i;
    }else{
      j=i-1;
      int last=0;
      while(j!=0&&p[j]<p[i]){
        last=j;
        j=fa[j];
      }
      if(j==0){
        l[i]=m;
        fa[m]=i;
        m=i;
      }else {
        l[i]=last;
        fa[last]=i;
        fa[i]=j;
        r[j]=i;
      }
    }
  }
  int ans=0;
  for(i=1;i<=n;i++){
    j=l[i];
    while(j){
      if((p[i]^p[j])>ans)
        ans=(p[i]^p[j]);
      j=r[j];
    }
    j=r[i];
    while(j){
      if((p[i]^p[j])>ans)
        ans=(p[i]^p[j]);
      j=l[j];
    }
  }
  printf("%d\n",ans);
//  printf("%d %d\n",ans, m);
//  for (i=1;i<=n;i++){
//    printf("%d %d\n",l[i],r[i]);
//  }
  return 0;
}
