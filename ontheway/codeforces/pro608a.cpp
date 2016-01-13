#include<stdio.h>

int n, ans, a,b;

int main() {
  scanf("%d %d", &n, &ans);
  while(n--) {
    scanf("%d %d", &a,&b);
    if(a+b > ans)
      ans=a+b;
  }
  printf("%d\n",ans);
  return 0;
}
