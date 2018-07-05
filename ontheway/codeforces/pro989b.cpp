#include<stdio.h>

int i,j,n,m;

char s[20000];

int main() {
  scanf("%d %d", &n, &m);
  scanf(" %s", s);
  int last = -1;
  for(i=0;i<n;i++) {
    if (s[i]=='.') {
      if (i-m>=0 || i + m < n) {
        last = i;
      }
      s[i] = '0';
    }
  }
  bool k = true;
  for (i=m;i<n;i++) {
    if (s[i]!=s[i-m]) {
      k = false;
    }
  }
  if (k && last<0) {
    printf("No\n");
    return 0;
  }
  if(k) {
    s[last] = '1';
  }
  printf("%s", s);
  return 0;
}
