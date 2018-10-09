#include<stdio.h>

int i,j,n,m;

void make(int n, int base) {
  if(n==3) {
    printf("%d %d %d", base, base, base*3);
    return;
  }
  if(n==1) {
    printf("%d", base);
    return;
  }
  int i;
  for(i=1;i<=n/2 + n%2; i++) {
    printf("%d ", base);
  }
  make(n/2, base*2);
}

int main() {
  scanf("%d", &n);
  make(n, 1);
  return 0;
}
