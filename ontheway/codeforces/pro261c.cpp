#include<iostream>
#include<string.h>
using namespace std;

typedef long long int LD;

LD n,m,ans;

LD p[100];

int i,j,t;

void make(LD m,LD now,bool half){
  // cout<<m<<" "<<now<<" "<<half<<" "<<ans<<endl;
  if(now<0||m>n)
    return;

  LD p[100],k;
  int i;
  memset(p,0,sizeof(p));
  if (half){
    p[0]=1;
    k=1;
    while(1){
      ans+=p[now];
      for(i=now-1;i>=0;i--){
        p[i+1]+=p[i];
      }
      m+=k;
      // cout<<"K="<<k<<" ans="<<ans<<" m="<<m<<endl;
      k*=2;
      if(k+m>n+1){
        make(m,now,0);
        return;
      }
    }
  }else{
    if(now==0)
        ans++;
    m++;
    make(m,now-1,1);
  }
}

int main(){
  cin>>n>>m;
  LD now;
  int i=0;
  while(m%2==0){
    m/=2;
    i++;
  }
  if(m!=1){
    cout<<"0\n";
    return 0;
  }
  make(0,i,1);
  if(i==0)
    ans--;
  cout<<ans;
  return 0;
}
