#include<stdio.h>

int i,j,n,m;

int p[1000],q[1000];

int ans;

int main() {
  int a,b;
  char c;
  scanf("%d", &n);
  for(i=1;i<=n;i++) {
    scanf(" %c %d %d", &c, &a, &b);
    if(c=='M') {
      p[a]++;
      p[b+1]--;
    } else {
      q[a]++;
      q[b+1]--;
    }
  }
  int nowa=0,nowb=0;
  for(i=0;i<1000;i++) {
    nowa+=p[i];
    nowb+=q[i];
    if(nowa>nowb) {
      if (nowb>ans)ans=nowb;
    } else {
      if(nowa>ans)ans=nowa;
    }
  }
  printf("%d\n", ans*2);
  return 0;
}
