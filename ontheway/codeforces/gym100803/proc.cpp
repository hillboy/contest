#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<vector>
using namespace std;

int i,j,n,m;

vector<pair<int, int> > p;

int main() {
  int a,b;
  scanf("%d %d", &n, &m);
  for(i=1;i<=m;i++) {
    scanf("%d %d", &a, &b);
    p.push_back(make_pair(a,b));
  }
  sort(p.begin(), p.end());
  int ans=0;
  a=0;
  b=0;
  for(i=0;i<(int)p.size();i++) {
    if(p[i].first>b) {
      ans+=b-a;
      a=p[i].first;
      b=p[i].second;
    } else {
      if(p[i].second > b)
        b=p[i].second;
    }
  }
  ans+=b-a;
  ans*=2;
  ans+=n+1;
  printf("%d\n", ans);
  return 0;
}
