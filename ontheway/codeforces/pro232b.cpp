#include<iostream>

#include<string.h>
using namespace std;


typedef long long int LD;
#define maxn 2100001
#define div 1000000007
#define mod 1000000007

LD n,m,k,tn,tn1,mn;


LD extend_gcd(LD a,LD b,LD &x,LD &y)
{
        LD ans,t;
        if(b==0){x=1;y=0;return a;}
        ans=extend_gcd(b,a%b,x,y);t=x;x=y;y=t-(a/b)*y;
        return ans;
}

LD reverse[maxn];


int i,j;

LD p[maxn];

LD c1[maxn],c2[maxn],c[maxn];


inline void prepareCC(LD cc[maxn],LD n){
        int i;
        cc[0]=1;
        for(i=1;i<=n;i++){
          cc[i]=cc[i-1]*(n-i+1)%mod;
          cc[i]*=reverse[i];
          cc[i]%=mod;
        }
}

inline void prepare(){
  LD x,y,ans;

  for(i=1;i<=n*n;i++){
                ans=extend_gcd(i,mod,x,y);
                if(x<0)
                        x=(x%mod+mod);
                reverse[i]=x;
  }
}

LD pow(LD a,LD n){
  LD ans=1,x=a;
  while(n){
    if(n&1){
      ans*=x;
      ans%=div;
    }
    n/=2;
    x*=x;
    x%=div;
  }
  return ans;
}



LD f(LD i){
  if(i<=mn)
    return tn1;
  else return tn;
}


LD ans[maxn];

LD cr1[maxn],cr[maxn];


int main(){
  cin>>n>>m>>k;
  tn=m/n;
  mn=m%n;
  tn1=tn+1;
  prepare();

  prepareCC(c1,n*mn);
  prepareCC(c2,n*(n-mn));
  prepareCC(c,n);

  ans[0]=1;
  for(i=0;i<=n;i++){
    cr[i]=pow(c[i],tn);
    cr1[i]=pow(c[i],tn1);
  }
  int up=0,r;
  for(i=1;i<=n;i++){
    for(j=up;j>=0;j--){
      for(r=1;r<=n;r++){
        if(r+j>k)
          break;

        if(i<=mn)
          ans[r+j]+=cr1[r]*ans[j];
        else
          ans[r+j]+=cr[r]*ans[j];
        ans[r+j]%=div;
        // cout<<i<<" "<<j<<" "<<r<<" "<<ans[r+j]<<endl;
      }
    }
    up+=n;
    if(up>k)
      up=k;
  }
  cout<<ans[k];
  return 0;
  if(mn==0){
    cout<<pow(c2[k],tn);
    return 0;
  }

  for(i=0;i<=k;i++){
    if(i<=(n*mn)&&(k-i)<=n*(n-mn)){
      // ans+=pow(c1[i],tn1)*pow(c2[k-i],tn);
      // ans%=div;
    }
  }
  cout<<ans;
  return 0;
}
