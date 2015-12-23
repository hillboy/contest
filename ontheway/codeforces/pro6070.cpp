#include<stdio.h>
#include<algorithm>

#define maxn 101000
using namespace std;

pair<int, int> p[maxn];

int q[maxn];

int i,j,n,m, ans;

int main() {
  scanf("%d", &n);
  int a, b;
  for(i=0;i<n;i++) {
    scanf("%d %d", &a, &b);
    p[i]=make_pair(a,b);
  }
  sort(p, p+n);

  ans = -1;

  for(i=0;i<n;i++) {
    j=lower_bound(p, p+n, make_pair(p[i].first-p[i].second, 0)) - p;
    if(j==0) {
      q[i] = i;
    } else {
      q[i]=(i-j) + q[j-1];
    }
    if(ans < 0 || q[i] + (n-i-1) < ans) {
      ans = q[i] + (n-i-1);
    }
  }
  printf("%d\n", ans);

  return 0;
}
