#include<stdio.h>
#include<string.h>

#define maxn 201000

char s1[maxn],s2[maxn];

int sum[maxn];

int i,j,n,m;


int main() {
  scanf("%s%n ",&s1[1], &n);
  scanf("%s%n",&s2[1], &m);
  for(i=1;s2[i];i++) {
    sum[i]=sum[i-1];
    if(s2[i] =='1') {
      sum[i]++;
    }
  }
  long long int ans=0,tmp;
  for(i=1;i<=n;i++) {
    if(s1[i]=='0') {
      tmp=sum[m-n+i] - sum[i-1];
    } else {
      tmp=(m-n+1) - sum[m-n+i] + sum[i-1];
    }
    ans+=tmp;
  }
  printf("%lld\n", ans);
  return 0;
}
