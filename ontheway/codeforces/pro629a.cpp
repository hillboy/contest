#include<stdio.h>

int p[111],q[111];

int ans;

int main() {
  int n,i,j;
  char c;
  scanf("%d", &n);
  for(i=1;i<=n;i++) {
    for(j=1;j<=n;j++) {
      scanf(" %c", &c);
      if(c=='C') {
        ans+=p[i]++;
        ans+=q[j]++;
      }
    }
  }
  printf("%d\n", ans);
  return 0;
}
