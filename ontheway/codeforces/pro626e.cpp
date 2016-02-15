#include<stdio.h>
#include<algorithm>
using namespace std;
#define maxn 200100

int p[maxn];

long long int sum[maxn];

int i,j,n,m;

int ansi,ansk;
double ans,nowsum,lastsum;

inline void make() {
  long long int total1, total2;
  for(i=2;i<n;i++) {

    int l = 1, r = i-1, mid;
    if (n-i < r) r = n-i;
    while ( l <= r) {
      mid = (l+r) /2;
      if (mid == 0)
      break;
      total1 = sum[n] - sum[n-mid] + sum[i] - sum[i-mid-1];
      total2 = p[n-mid] + p[i-mid-1];
      if (i-mid-1 > 0 && n-mid > i && total1 * 2 < total2 * (mid+mid+1)) {
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    r=l;
    if (r>0) {
      if ((sum[n] - sum[n-r] + sum[i] - sum[i-r-1])*1.0/(r+r+1) - p[i]>ans) {
        ans = (sum[n] - sum[n-r] + sum[i] - sum[i-r-1])*1.0/(r+r+1) - p[i];
        ansi = i;
        ansk= r;
      }
    }
  }

}

void output() {
  if(ans>1e-9) {
    printf("%d\n", ansk*2+1);
    for(j=1;j<=ansk;j++)
    printf("%d %d ", p[ansi-j], p[n-j+1]);
    printf("%d\n", p[ansi]);
  } else {
    printf("1\n");
    printf("%d\n", p[1]);
  }
}

int main() {
  scanf("%d", &n);
  for(i=1;i<=n;i++) {
    scanf("%d", &p[i]);
  }
  sort(&p[1], &p[1+n]);
  for(i=1;i<=n;i++) {
    sum[i]=sum[i-1] + p[i];
  }
  make();
  output();
  return 0;
}
