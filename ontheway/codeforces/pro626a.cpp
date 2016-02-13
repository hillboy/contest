#include<stdio.h>
#include<string.h>

int n;

char s[10000];

int i,j;

int main() {
  scanf("%d %s", &n, s);
  int ans = 0;
  for(i=0;s[i];i++) {
    int a=0,b=0;
    for(j=i;s[j];j++){
      if(s[j]=='U') a++;
      if(s[j]=='D') a--;
      if(s[j]=='L') b++;
      if(s[j]=='R') b--;
      if(a==0&&b==0) {
        ans++;
      }
    }
  }
  printf("%d\n", ans);

  return 0;
}
