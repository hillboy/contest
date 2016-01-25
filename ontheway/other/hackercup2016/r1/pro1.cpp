#include<stdio.h>
#include<algorithm>
using namespace std;
#define maxn 10000000

typedef long long int LD;
int p[maxn];

int q[maxn][10];

int dis(int a, int ai, int b, int bi) {
  int ans = 4-ai+bi-1;
  if(bi>ai && p[b] - p[a] >= bi-ai) {
    if(p[b]-p[a] <= (bi-ai) *10) {
      ans = min(ans, bi-ai-1);
    }
  }
  return ans;
}

int i,j,k,n,m;

int main() {
  int ii,nn;
  scanf("%d", &nn);
  for(ii=1;ii<=nn;ii++) {
    printf("Case #%d: ", ii);
    scanf("%d", &n);
    for(i=1;i<=n;i++) {
      scanf("%d", &p[i]);
    }
    q[0][1]=q[0][2]=q[0][3]=n*4;
    q[0][4]=0;
    for(i=1;i<=n;i++) {
      for(j=1;j<=4;j++)  {
        q[i][j]=n*4;
        for(k=1;k<=4;k++) {
          q[i][j]=min(q[i][j], q[i-1][k] + dis(i-1, k, i, j));
        }
      }
    }
    int ans = n*4;
    for(i=1;i<=4;i++) {
      ans=min(ans, q[n][i]+4-i);
    }
    printf("%d\n", ans);
  }
  return 0;
}
