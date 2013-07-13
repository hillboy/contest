#include<iostream>
#include<string.h>
using namespace std;
#define maxn 400000
#define maxm 16
typedef long long int LD;

int i,j,n,m;

LD A,B;

LD p[maxn],que[maxn],t,p0[maxm][maxn];

LD pp[maxm][maxm];

void oit(LD a[maxm][maxm]){
  int i,j;
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      cout<<a[i][j]<<" ";
    }
    cout<<endl;
  }
}

void checkit(int a,LD b){
  if(a>=m+n)
    return;
  if(p[a]){
    return;
  }
  p[a]=b+1;
  que[++t]=a+A;
}

void BFS(LD a){
  t=1;
  que[1]=a;
  memset(p,0,sizeof(p));
  int i=1,j;
  LD now;
  while(i<=t){
    now=que[i];
    // cout<<now<<" : "<<p[now-A]<<endl;
    for(j=n;j;j--){
      if(now%j==0){
        break;
      }
    }
    if(j>1)
      j--;
    while(j>0){
      checkit(now+j-A,p[now-A]);
      j--;
    }
    i++;
  }
}

void dismul(LD a[maxm][maxm],LD b[maxm][maxm],LD c[maxm][maxm]){
  int i,j,r;
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      c[i][j]=0;
    }
  }
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
        c[i][j]=a[i][0]+b[0][j];
    }
    for(r=0;r<n;r++){
      for(j=0;j<n;j++){
        if(a[i][r]+b[r][j]<c[i][j]){
          c[i][j]=a[i][r]+b[r][j];
        }
      }
    }
  }
}

void dispow(LD a[maxm][maxm],LD ans[maxm][maxm],LD nn){
  int i,j,r;
  LD mul[maxm][maxm],temp[maxm][maxm];
  bool first=1;
  memcpy(mul,a,sizeof(mul));
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      ans[i][j]=0;
    }
  }
  while(nn){
    if(nn%2){
      if(first){
        first=0;
        memcpy(ans,mul,sizeof(mul));
      }else{
        memcpy(temp,ans,sizeof(temp));
        dismul(temp,mul,ans);
      }
    }
    nn/=2;
    memcpy(temp,mul,sizeof(mul));
    dismul(temp,temp,mul);
  }
}

int main(){
  LD i,j;
  cin>>B>>A>>n;
  for(i=1;i<=maxn;i++){
    for(j=2;j<=n;j++){
      if(i%j)
        break;
    }
    if(j>n)
      break;
  }

  m=i;
  for(i=A;i<A+n;i++){
    BFS(i);
    for(j=A;j<A+n;j++){
      pp[i-A][j-A]=p[j+m-A];
    }
    memcpy(p0[i-A],p,sizeof(p));
  }
  LD N=(B-A)/m;
  if(N==0){
    cout<<p0[0][B-A];
    return 0;
  }
  LD ans[maxm][maxm],output=0,temp;
  dispow(pp,ans,N);
  for(i=0;i<n;i++){
    if(i<=(B-A)%m){
      temp=ans[0][i]+p0[i][(B-A)%m];
      if(output==0||temp<output)
        output=temp;
    }
  }
  cout<<output<<endl;
  return 0;
}
