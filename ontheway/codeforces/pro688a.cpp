#include<iostream>
#include<string.h>
#include<algorithm>
#include<map>
#include<set>
#include<vector>
#include<map>
#include<string>
using namespace std;

#define forlr(x,l,r) for(x=l;x<(int)r;++x)
#define for1(x,y) forlr(x,0,y)
#define forn(x) for1(x,n)

int i,j,n,m;

string all1;

int main() {
  ios_base::sync_with_stdio(false);
  all1="";
  cin >> n >> m;
  for1(i,n) {
    all1+='1';
  }
  int ans = 0, now = 0;
  string temp;
  while(m--) {
    cin >> temp;
    if(temp==all1) {
      if(now>ans)
        ans=now;
      now=0;
    } else {
      now++;
    }
  }
  if(now>ans)ans=now;
  cout << ans << endl;
  return 0;
}
