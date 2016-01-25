#include<stdio.h>
#include<algorithm>
#include<string.h>
using namespace std;
#define maxn 1000000

int p[maxn];

int left[maxn][2],right[maxn][2];

char s1[maxn],s2[maxn];


int i,j,n,m;


int main() {
  int ii,nn;
  scanf("%d", &nn);
  for(ii=1;ii<=nn;ii++) {
    memset(right, 0, sizeof(right));
    memset(left, 0, sizeof(left));
    printf("Case #%d: ", ii);
    scanf("%d", &n);
    scanf("%s", &s1[1]);
    scanf("%s", &s2[1]);
    for(i=1;i<=n;i++) {
      left[i][0]=n;
      if(s2[i]==s2[i-1]) {
        left[i][1]=left[i-1][1];
      } else {
        left[i][1]=left[i-1][1]+1;
      }
      if(s1[i] == s2[i]) {
        left[i][0] = min(left[i-1][1], left[i-1][0]);
      }
    }
    for(i=n;i;i--) {
      right[i][0]=n;
      if(s2[i]==s2[i+1]) {
        right[i][1]=right[i+1][1];
      } else {
        right[i][1]=right[i+1][1]+1;
      }
      if(s1[i]==s2[i]) {
        right[i][0] = min(right[i+1][1], right[i+1][0]);
      }
    }
    int ans = n+n;
    for(i=0;i<=n;i++) {
      ans=min(ans, max(min(left[i][0], left[i][1]), min(right[i+1][0], right[i+1][1])));
//      printf("%d  %d (%d, %d) (%d, %d)\n", i,ans, left[i][0], left[i][1], right[i+1][0], right[i+1][1]);
    }
    printf("%d\n", ans);
  }
  return 0;
}
