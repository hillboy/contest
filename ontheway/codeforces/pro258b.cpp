#include<stdio.h>
#define div 1000000007

typedef long long int LD;

int lucky(int a){
  return (a==4||a==7);
}

LD pow(LD a,LD n){
  LD mul=a,ans=1;
  while(n){
    if(n&1){
      ans*=mul;
      ans%=div;
    }
    mul*=mul;
    mul%=div;
    n/=2;
  }
  return ans;
}

LD C(int a,int b){

  int i;
  LD ans=1;
  for(i=a-b+1;i<=a;i++)
    ans*=i;

  for(i=1;i<=b;i++)
    ans/=i;


  return ans%div;
}

LD make(LD a,int left){
  if(left<0)
    return 0;
  if(a==0){
    if(left==0)
      return 1;
    return 0;
  }
  LD now=1,n=0;
  int i;
  while(now<=a){
    now*=10;
    n++;
  }
  now/=10;
  n--;
  LD ans=0;
  for(i=0;i<a/now;i++){
    if(lucky(i)){
      if(left>0){
        ans+=pow(2,left-1)*pow(8,n-left+1)%div*C(n,left-1)%div;
      }
    }
    else{
      ans+=pow(2,left)*pow(8,n-left)%div*C(n,left)%div;
    }
    if(ans>=div)
      ans-=div;
  }
  if(lucky(i))
    left--;
  if(left<0||n<left)
    return ans;
  ans+=make(a%now,left);
  return ans%div;
}

LD pa(LD n,int a){
  int i;
  LD ans=1;
  for(i=0;i<a;i++){
    ans=ans*(n-i)%div;
  }
  return ans;
}

int i,j,r,n,m;

LD p[20],q[20][20][7];

LD findit(int a,int b,int c){
  if(c==0){
    return 1;
  }
  if(b<0)
    return 0;

  int i;
  LD ans=0;
  for(i=0;i<=c;i++){
    if(i*b>a)
      break;
    ans+=findit(a-i*b,b-1,c-i)*C(c,i)%div*pa(p[b],i)%div;

    if(ans>=div)
      ans-=div;
  }
  return ans;
}

int main(){
  scanf("%d",&n);

  LD ans=0,now;
  for(i=0;i<11;i++){
    now=make(n,i);
    if(i==0)
      now--;
    else{
      ans+=findit(i-1,i-1,6)*now%div;
      if(ans>=div)
        ans-=div;
    }
    p[i]=now;

  }

  printf("%d\n",(int)ans);
  return 0;
}
