#include<iostream>
using namespace std;
typedef long long int LD;

LD a,b,ans,A,now,C;

int i,j,n,m;

int main() {
  cin>>a>>b;
  ans=1;
  now=1;

  LD aa = a;
  if(a<b) {
    cout << 0 << endl;
    return 0;
  }
  while(aa) {
    if(b&1) {
      n++;
      ans*=2;
      A+=now;
    } else {
      m++;
      C+=now;
    }
    b/=2;
    now*=2;
    aa/=2;
  }

  if( (a<A)) {
    cout << 0 <<endl;
    return 0;
  }

  LD tmp = a-A;
  C = (C<<1);
  if ( (tmp | C) != C) {
    cout << 0 <<endl;
    return 0;
  }


  if(tmp==0) {
    ans-=2;
    if(ans<0)
      ans=0;
  }

  cout << ans << endl;
  return 0;
}
