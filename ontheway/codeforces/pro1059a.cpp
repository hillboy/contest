#include<stdio.h>

int main() {
  int n,l, a, i, ans = 0;
  scanf("%d %d %d", &n, &l, &a);
  int last= 0, x,y;
  for(i=1;i<=n;i++) {
    scanf("%d %d", &x, &y);
    if(x-last >=a) {
      ans+= (x-last)/a;
    }
    last = x+y;
  }
  if(l-last >=a)
    ans+= (l-last)/a;
  printf("%d\n", ans);
  return 0;
}
