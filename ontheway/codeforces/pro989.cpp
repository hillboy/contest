#include<stdio.h>

char s[1000];

int i,j,n,m;

int main() {
  scanf(" %s", s);

  for(i=1;s[i];i++) {
    if ((int)(s[i-1]) + s[i] + s[i+1] == 'A' + 'B' + 'C' && s[i] != s[i-1]) {
      printf("Yes\n");
      return 0;
    }
  }
  printf("No\n");
  return 0;
}
