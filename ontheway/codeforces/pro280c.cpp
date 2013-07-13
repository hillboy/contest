#include<stdio.h>
#include<string.h>
#define maxn 201000
int fa[maxn];
int ind[maxn],last[maxn],e[maxn],d[maxn],que[maxn];

int i,j,n,m,t;

int main(){
  scanf("%d",&n);
  int a,b;
  for(i=1;i<n;i++){
    scanf("%d %d",&a,&b);
    fa[b]=a;
    t++;
    last[t]=ind[a];
    ind[a]=t;
    e[t]=b;
  }
  d[1]=1;
  t=1;
  que[1]=1;
  int ii=1;
  while(ii<=t){
    i=que[ii];
    for(j=ind[i];j;j=last[j]){
      d[e[j]]=d[i]+1;
      que[++t]=e[j];
    }
    ii++;
  }
  double ans=0;
  for(i=1;i<=n;i++){
    ans+=1.0/d[i];
  }
  printf("%.9lf\n",ans);
  return 0;
}
