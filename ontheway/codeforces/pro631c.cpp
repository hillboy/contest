#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;
#define maxn 200100

int i,j,n,m;

int p[maxn],start, ed;

vector<int> q[maxn];

int que[maxn][2];

int ans[maxn];


int main() {
  scanf("%d %d", &n, &m);
  for(i=1;i<=n;i++) {
    scanf("%d", &p[i]);
  }
  int a,b;
  for(i=1;i<=m;i++) {
    scanf("%d %d", &a, &b);
    que[i][0]=a;
    que[i][1]=b;
    q[b].push_back(i);
    if(b>ed)
      ed=b;
  }

  start = 1;
  sort(&p[1], &p[ed+1]);

  int nowmax=0;
  for(i=n;i>ed;i--)
    ans[i]=p[i];
  for(i=ed;i;i--) {
    for(j=0;j<(int)q[i].size();j++) {
      if(q[i][j] > nowmax)
        nowmax=q[i][j];
    }
    if(que[nowmax][0]==1) {
      ans[i]=p[ed];
      ed--;
    } else {
      ans[i]=p[start];
      start++;
    }
  }
  for(i=1;i<n;i++)
    printf("%d ", ans[i]);
  printf("%d\n", ans[i]);
  return 0;
}
