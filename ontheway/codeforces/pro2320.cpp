#include<stdio.h>
#include<string.h>
#define maxn 100

int c3(int n){
  int ans=n*(n-1)*(n-2);
  ans/=6;
  return ans;
}

int c2(int n){
  return n*(n-1)/2;
}

int i,j,n,m;

int p[maxn*2];

bool ans[maxn+1][maxn+1];

int main(){
  scanf("%d",&n);
  int nn;
  // for(nn=3;nn<=100000;nn++){

  memset(ans,0,sizeof(ans));
  memset(p,0,sizeof(p));

  for(i=3;i<=n;i++){
    if(c3(i+1)>n){
      break;
    }
    p[i]=-1;
  }
  n-=c3(i);
  m=i;
  while(n>0){
    m++;
    for(j=2;j<i;j++){
      if(c2(j+1)>n){
        break;
      }
    }
    n-=c2(j);
    p[m]=j;
  }

  int a,b;
  for(a=1;a<=i;a++)
    for(b=1;b<=i;b++)
      ans[a][b]=1;
  for(a=i+1;a<=m;a++){
    for(b=1;b<=p[a];b++){
      ans[a][b]=ans[b][a]=1;
    }
  }
  // printf("%d %d\n",nn,m);
  printf("%d\n",m);
  for(a=1;a<=m;a++){
    for(b=1;b<=m;b++){
      if(a==b||!ans[a][b])printf("0");
      else
        printf("1");
    }
    printf("\n");
  }
  // }
  return 0;
}
