#include<stdio.h>
#include<algorithm>
using namespace std;
#define maxn 110000

int p[maxn],q[maxn];

int i,j,n,m,t;
int main(){
  scanf("%d",&m);
  for(i=0;i<m;i++)
    scanf("%d",&p[i]);
  scanf("%d",&n);
  for(i=0;i<n;i++)
    scanf("%d",&q[i]);
  sort(p,p+m);
  sort(q,q+n);
  i=n-1;
  j=0;
  t=p[0];
  int ans=0;
  while(i>=0){
    if(j<m&&p[j]-1<=i){
      while(p[j]--){
        ans+=q[i];
        i--;
      }
      if(i>=0)
        i--;
      if(i>=0)
        i--;
      p[0]=t;
      // j++;
    }else{
      ans+=q[i];
      i--;
    }
  }
  printf("%d\n",ans);
  return 0;
}
