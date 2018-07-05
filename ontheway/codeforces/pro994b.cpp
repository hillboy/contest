#include<stdio.h>
#include<algorithm>
using namespace std;

#define maxn 101000

int i,j,n,m;

int p[maxn][2];

pair<int, int> q[maxn];

long long int qq[maxn][12];

int main() {
  scanf("%d %d",&n, &m);
  int a, b;
  for(i=0;i<n;i++) {
    scanf("%d", &a);
    p[i][0]=a;
    q[i].first = a;
  }
  for(i=0;i<n;i++) {
    scanf("%d", &b);
    p[i][1]=b;
    q[i].second = b;
  }
  sort(q, q+n);

  for(i=0;i<n;i++) {
    for(j=1;j<=m;j++) {
      if(i>0) {
        qq[i][j] = qq[i-1][j];
        if (qq[i-1][j-1] + q[i].second > qq[i][j]) {
          qq[i][j] = qq[i-1][j-1] + q[i].second;
        }
      } else {
        qq[i][j] = q[i].second;
      }
      if (qq[i][j-1]>qq[i][j])
        qq[i][j] = qq[i][j-1];
    }
  }
  pair<int, int> ii;
  long long int ans;
  for(i=0;i<n;i++) {
    ii.first = p[i][0];
    ii.second = p[i][1];
    j = std::lower_bound(q,q+n, ii)-q;
    ans = p[i][1];
    if (j>0) {
      ans+= qq[j-1][m];
    }
    printf("%lld ",ans);
  }
  return 0;
}
