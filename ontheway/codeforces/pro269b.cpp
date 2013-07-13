#include<stdio.h>
#include<string.h>
#define maxn 5011

int p[maxn],q[2][maxn];

int f[maxn],small[maxn];

bool nothas[maxn];

int i,j,n,m;

int main(){
  double a;
  scanf("%d %d",&n,&m);
  for(i=1;i<=n;i++){
    scanf("%d %lf",&p[i],&a);
    nothas[i]=1;
  }

  nothas[p[n]]=0;

  for(i=n-1;i;i--){
    j=p[i]-1;
    while(nothas[j])j--;
    small[i]=j;
    nothas[p[i]]=0;
  }

  int know,now=0;
  for(i=n-1;i;i--){
    know=now;
    now=1-now;
    for(j=m;j>=1;j--){
      q[now][j]=q[know][j];
      if(p[i+1]<j)
        q[now][j]++;
      if (small[i]>=j)
        q[now][j]++;
      if(j<m&&q[now][j+1]<q[now][j])
        q[now][j]=q[now][j+1];
    }
    f[i]=f[i+1]+1;
    if(q[now][p[i]]<f[i])
      f[i]=q[now][p[i]];
  }
  printf("%d\n",f[1]);
  return 0;
}
