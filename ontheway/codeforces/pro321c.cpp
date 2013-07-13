#include<stdio.h>
#include<string.h>
#define maxn 201000

int ind[maxn],last[maxn],e[maxn];
int ans[maxn];
int i,j,n,m,t;

void adde(int a,int b){
  t++;
  e[t]=b;
  last[t]=ind[a];
  ind[a]=t;
}

bool checked[maxn];

int que[maxn],tt,de[maxn],fa[maxn];

void bfs(int a){
  tt=1;
  que[1]=a;
  checked[a]=1;
  int i,j;
  de[a]=1;
  fa[a]=0;
  while(i<=tt){
    for (j=ind[que[i]];j;j=last[j]){
      if (!checked[e[j]]){
        checked[e[j]]=1;
        que[++tt]=e[j];
        fa[e[j]]=que[i];
        de[e[j]]=de[que[i]]+1;
      }
    }
    i++;
  }
}


void clearQue(){
  int i;
  for(i=1;i<=tt;i++){
    checked[que[i]]=0;
  }
}

void make(int a,int now){
  bfs(a);
  int b,c,i,j;
  b=que[tt];
  clearQue();
  bfs(b);
  c = que[tt];
  clearQue();
  i=(de[c]+1)/2;
  for(j=1;j<i;j++){
    c=fa[c];
  }
  checked[c]=1;
  ans[c]=now;
  for(i=ind[c];i;i=last[i]){
    if (!checked[e[i]]){
      make(e[i],now+1);
    }
  }
}

int main(){
  scanf("%d",&n);
  int a,b;
  for(i=1;i<n;i++){
    scanf("%d %d",&a,&b);
    adde(a,b);
    adde(b,a);
  }
  make(1,1);
  for(i=1;i<=n;i++){
    printf("%c ",char(ans[i]+'A'-1));
  }
  return 0;
}
