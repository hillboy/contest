#include<stdio.h>

int i,j,n,m;

int main() {
  scanf("%d", &n);
  while(n) {
    i=1;j=1;
    while(i<=n) {
      i*=2;
      j++;
    }
    j--;
    i/=2;
    n-=i;
    printf("%d ", j);
  }
  return 0;
}
