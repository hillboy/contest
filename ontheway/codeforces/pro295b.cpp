#include<stdio.h>
#include<string.h>
#define maxn 510

int p[maxn][maxn],q[maxn][maxn];
int que[maxn],x[maxn],t;
long long int y[maxn];
int i,j,n,m;

int dis[maxn];
bool checked[maxn];

inline void make1(){
  memset(checked,0,sizeof(checked));
  memset(dis,0,sizeof(dis));
  int now=que[t],last,nowdis,i,ii;
  dis[now]=0;
  while(1){
    checked[now]=1;
    last=now;
    now=-1;
    nowdis=0;
    for(ii=1;ii<t;ii++){
      i=que[ii];
      if(!checked[i]){
        if(dis[i]==0||dis[i]>dis[last]+p[last][i])
          dis[i]=dis[last]+p[last][i];
        if(dis[i]<nowdis||nowdis==0){
          now=i;
          nowdis=dis[i];
        }
      }
    }
    if(nowdis==0)
      break;
  }
  for(i=1;i<t;i++)
    q[que[t]][que[i]]=dis[que[i]];
}
inline void make2(){
  memset(checked,0,sizeof(checked));
  memset(dis,0,sizeof(dis));
  int now=que[t],last,nowdis,i,ii;
  dis[now]=0;
  while(1){
    checked[now]=1;
    last=now;
    now=-1;
    nowdis=0;
    for(ii=1;ii<t;ii++){
      i=que[ii];
      if(!checked[i]){
        if(dis[i]==0||dis[i]>dis[last]+p[i][last])
          dis[i]=dis[last]+p[i][last];
        if(dis[i]<nowdis||nowdis==0){
          now=i;
          nowdis=dis[i];
        }
      }
    }
    if(nowdis==0)
      break;
  }
  for(i=1;i<t;i++)
    q[que[i]][que[t]]=dis[que[i]];
}

void outputq(){
  for(i=1;i<=n;i++){
    for(j=1;j<=n;j++)
      printf("%d ",q[i][j]);
    printf("\n");
  }
}

int main(){
  scanf("%d",&n);
  for(i=1;i<=n;i++){
    for(j=1;j<=n;j++)
      scanf("%d",&p[i][j]);
  }
  for(i=1;i<=n;i++)
    scanf("%d",&x[i]);
  long long int ans=0;
  int a,b,aa,bb;
  for(i=n;i;i--){
    que[++t]=x[i];
    make1();
    make2();
    ans=0;
    for(aa=1;aa<=t;aa++) 
      for(bb=1;bb<=t;bb++){
        a=que[aa];
        b=que[bb];
        if(q[a][b]>q[a][x[i]]+q[x[i]][b])
          q[a][b]=q[a][x[i]]+q[x[i]][b];
        ans += q[a][b];
      }
    y[i]=ans;
  }
  for(i=1;i<=n;i++){
    printf("%I64d ",y[i]);
  }
  return 0;
}
