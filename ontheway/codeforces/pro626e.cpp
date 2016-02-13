#include<stdio.h>
#include<algorithm>
using namespace std;
#define maxn 200100

int p[maxn];

int i,j,n,m;

int ansi,ansk;
double ans,nowsum,lastsum;

inline void make() {
  for(i=2;i<n;i++) {
    if((p[i-1]+p[n]-2*p[i])/3.0 > ans) {
      ans=p[i-1]+p[n]-2*p[i];
      ansi=i;
      j=1;
      lastsum=p[i];
      nowsum=p[i];
      while(i-j && n-j+1>i) {
        nowsum+=p[i-j]+p[n-j+1];
        if(nowsum/(j*2+1) < lastsum/((j-1)*2+1)) {
          break;
        }
        j++;
      }
      j--;
      ans=(nowsum/(j*2+1));
      ansk=j;
    }
  }
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
  make();
  return 0;
}
