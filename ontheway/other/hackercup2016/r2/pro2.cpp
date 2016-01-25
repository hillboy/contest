#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;


#define maxn 3111

double p[maxn][maxn],P, sum[maxn];
double q[maxn];

int i,j,n,m;

void prepare() {
  memset(p,0,sizeof(p));
  p[0][0]=1;
  for(i=1;i<=n;i++) {
    for(j=0;j<=i;j++) {
      if(j==0) {
        p[i][j]=p[i-1][j]*(1-P);
      } else {
        p[i][j]=p[i-1][j]*(1-P) + (p[i-1][j-1]*P);
      }
    }
  }
  memset(sum,0,sizeof(sum));
  for(i=1;i<=n;i++) {
    for(j=m;j<=i;j++) {
      sum[i]+=p[i][j];
    }
  }
  memset(q,0,sizeof(q));
  for(i=1;i<=n;i++) {
    for(j=1;j<=i;j++) {
      q[i]=max(q[i], q[i-j] + sum[j]);
    }
  }
}

int main() {
  int ii,nn;
  scanf("%d", &nn);
  for(ii=1;ii<=nn;ii++) {
    printf("Case #%d: ", ii);
    scanf("%d %d %lf", &n, &m, &P);
    prepare();
    printf("%.9lf\n", q[n]);
  }
  return 0;
}
