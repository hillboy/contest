#include<stdio.h>
#define maxn 501000

int i,j,n,m,d;

bool p[maxn];

int main() {
  scanf("%d %d",&n, &d);
  p[0]=1;
  while(n--){
    scanf("%d", &m);
    for(i=maxn-m-1;i>=0;i--)
      if(p[i])
        p[i+m] = 1;
  }
  i=0;
  int ans = 0;
  while(1){
    j=i+d;
    if(j>=maxn)
      j=maxn-1;
    while(j>i&&!p[j])
      j--;
    if(j==i)
      break;
    ans++;
    i=j;
  }
  printf("%d %d\n", i, ans);
  return 0;
}
