// Modular multiplicative inverse
#include<iostream>
#include<map>
using namespace std;

#define mod 1000000007
#define maxn 110000
typedef long long int lld;

lld extend_gcd(lld a,lld b,lld &x,lld &y)
{
  lld ans,t;
  if(b==0){x=1;y=0;return a;}
  ans=extend_gcd(b,a%b,x,y);t=x;x=y;y=t-(a/b)*y;
  return ans;
}

lld reverse[maxn];

map<int,int> count;

lld n,m;
int i,j;

int p[maxn],t;

bool lucky(int a){
  while(a){
    if(a%10!=4&&a%10!=7)
      return 0;
    a/=10;
  }
  return 1;
}

lld c1[maxn],c2[2][maxn];

void prepareC1(int n){
  c1[0]=1;
  int i;
  for(i=1;i<=n;i++){
    c1[i]=c1[i-1]*(n-i+1)%mod;
    c1[i]*=reverse[i];
    c1[i]%=mod;
  }
}
int now;
void prepareC2(){
  now=0,i,j;
  c2[now][0]=1;
  for(i=0;i<t;i++){
    now=1-now;
    c2[now][0]=1;
    c2[1-now][i+1]=0;
    for(j=1;j<=i+1;j++){
      c2[now][j]=c2[1-now][j]+c2[1-now][j-1]*p[i]%mod;
      c2[now][j]%=mod;
    }
  }
}


int main()
{
  cin>>n>>m;
  lld x,y,ans;
  lld i;
  for(i=1;i<=n;i++){
    ans=extend_gcd(i,mod,x,y);
    if(x<0)
      x=(x%mod+mod);
    reverse[i]=x;
    cin>>j;
    if(count.find(j)!=count.end()){
      count[j]++;
    }
    else{
      count[j]=1;
    }
  }

  map<int,int>::iterator ii;
  int kk=0;
  for(ii=count.begin();ii!=count.end();ii++){
    if(ii->second>1&&lucky(ii->first)){
      p[t++]=ii->second;
      kk+=p[t-1];
    }
  }
  prepareC1(n-kk);
  prepareC2();
  ans=0;
  lld temp;
  for(kk=0;kk<=m;kk++){
    temp=c1[kk]*c2[now][m-kk]%mod;
    ans+=temp;
    ans%=mod;
  }
  cout<<ans;
  return 0;
}
