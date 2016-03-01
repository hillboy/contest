#include<stdio.h>
#include<algorithm>

#include<map>

using namespace std;
#define maxn 1011

int p[maxn];

int i,j,r,n,m;

int num0;

int ans;

int q[maxn];

map<int, int>qq;

inline void make() {
  int now;
  map<int,int> ::iterator ii;
  for(i=1;i<=n;i++)
    for(j=1;j<=n;j++) if(j!=i && ((p[i]!=0) || (p[j]!=0))) {
      q[1]=p[i];
      q[2]=p[j];
      qq[p[i]]--;
      qq[p[j]]--;
      r=2;
      while(1) {
        now=q[r]+q[r-1];
        ii=qq.find(now);
        if(ii!=qq.end() && ii->second > 0) {
          r++;
          q[r]=now;
          qq[now]--;
        } else {
          break;
        }
      }
      if(r>ans)
        ans=r;
      while(r) {
        qq[q[r]]++;
        r--;
      }
    }
}

int main() {
  scanf("%d", &n);
  int a;
  for(i=1;i<=n;i++) {
    scanf("%d", &a);
    if(a==0) {
      num0++;
    }
    p[i]=a;
    if(qq.count(a)) {
      qq[a]+=1;
    } else {
      qq[a]=1;
    }
  }
  ans=num0;
  make();
  printf("%d\n", ans);
  return 0;
}
