#include<stdio.h>
#include<string.h>
#define maxn 401000

int last[maxn],e[maxn],num[maxn],c[maxn];

int ind[maxn],t;

int edge[maxn/2][2];

int di[maxn];

void adde(int a,int b,int cc,int n){
  t++;
  last[t]=ind[a];
  ind[a]=t;
  e[t]=b;
  num[t]=n;
  c[t]=cc;
}

int i,j,n,m;

int input[maxn],que[maxn],pque[maxn];

bool checked[maxn],finished[maxn];

int sume(int now){
  int i,j,ans=0;
  for(i=ind[now];i;i=last[i]){
    j=e[i];
    if(!finished[j]){
      ans+=c[i];
      // printf("e %d %d c%d\n",now,j,ans);
    }
  }
  return ans;
}

int main(){
  scanf("%d %d",&n,&m);
  int a,b,cc,i,j;
  for(i=1;i<=m;i++){
    scanf("%d %d %d",&a,&b,&cc);
    adde(a,b,cc,i);
    adde(b,a,cc,i);
    edge[i][0]=a;
    edge[i][1]=b;
  }
  t=0;
  checked[1]=finished[1]=1;
  for(i=ind[1];i;i=last[i]){
    j=e[i];
    input[j]+=c[i];
    di[num[i]]=1;
    if(!checked[j]){
      checked[j]=1;
      t++;
      que[t]=j;
    }
  }
  int pt=0,now;

  for(now=1;now<=t;now++){
    if (que[now]!=n)
    if(sume(que[now])==input[que[now]]){
      pt++;
      pque[pt]=que[now];
      finished[que[now]]=1;
    }
  }
  int ii=1;

  while(ii<=pt){
    now=pque[ii];
    // printf("now: %d\n",now);
    for(i=ind[now];i;i=last[i]){
      j=e[i];
      if(!finished[j]){
        di[num[i]]=now;
        input[j]+=c[i];
        if(j!=n)
        if(sume(j)==input[j]){
          pt++;
          pque[pt]=j;
          finished[j]=1;
        }
      }
    }
    ii++;
  }
  for(i=1;i<=m;i++){
    if(di[i]==edge[i][0])
      printf("0\n");
    else
      printf("1\n");
  }
  return 0;
}
