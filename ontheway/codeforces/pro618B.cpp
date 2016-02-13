#include<stdio.h>
#include<algorithm>

using namespace std;

#define maxn 100

int i,j,n,m;

int p[maxn][maxn];

int ans[maxn];

bool checked[maxn];

int main() {
  scanf("%d", &n);
  for(i=1;i<=n;i++) {
    for(j=1;j<=n;j++) {
      scanf("%d", &p[i][j]);
    }
  }
  int ii;
  for(ii=1;ii<n;ii++) {
    for(i=1;i<=n;i++) {
      if(!checked[i]) {
        int now = -1;
        for(j=1;j<=n;j++) {
          if(!checked[j] && i!=j) {
            if(now<0) {
              now = p[i][j];
            } else {
              if(p[i][j] != now) {
                now = -1;
                break;
              }
            }
          }
        }
        if(now>0) {
          checked[i]=1;
          ans[i]=now;
          break;
        }
      }
    }
  }
  for(i=1;i<=n;i++) if(!checked[i])
    ans[i]=n;
  for(i=1;i<n;i++) printf("%d ", ans[i]);
  printf("%d\n", ans[i]);
  return 0;
}
