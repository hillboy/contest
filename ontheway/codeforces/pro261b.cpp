#include<stdio.h>
#include<string.h>

#define maxn 60

double p[maxn][maxn][maxn];
int i,j,n,m,r,k;

int q[maxn];
double mul[maxn];

int main(){
  scanf("%d",&n);
  mul[0]=1;
  int sum=0;
  for(i=1;i<=n;i++){
    scanf("%d",&q[i]);
    sum+=q[i];
    mul[i]=mul[i-1]*i;
  }
  scanf("%d",&m);
  if(sum<=m){
    printf("%d\n",n);
    return 0;
  }
  double ans=0;
  for(i=1;i<=n;i++){
    memset(p,0,sizeof(p));
    p[0][0][0]=1;
    for(j=1;j<=n;j++) {
    for(k=0;k<n;k++){
        for(r=0;r<=m;r++){
          p[k][j][r]=p[k][j-1][r];
          if(r>=q[j]&&i!=j&&k>0){
            p[k][j][r]+=p[k-1][j-1][r-q[j]];
          }
        }
    }
    // for(k=1;k<n;k++){
    //   for(r=0;r<=m;r++)
    //     printf("%lf\t",p[k][j][r]);
    // }
    // printf("........\n");
    }
    for(r=0;r<=m;r++){
      if(r+q[i]>m){
        for(k=1;k<n;k++){
          // printf("%d %d %d %lf\n",i,r,k,p[k][n][r]);
          ans+=mul[k]*mul[n-k-1]*k*p[k][n][r];
        }
      }
    }
  }
  printf("%.10lf\n",ans/mul[n]);
  return 0;
}
