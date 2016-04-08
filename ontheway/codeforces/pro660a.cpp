#include<stdio.h>

int n,a,b;

int p[10000];

int gcd(int a,int b) {
  if (a>b) return gcd(b,a);
  if(a==0)return b;
  return gcd(b%a, a);
}

int main() {
  scanf("%d", &n);
  int m = 0;
  for(int i=1;i<=n;i++) {
    scanf("%d", &p[i]);
    if(i>1 && gcd(p[i-1], p[i]) > 1)
      m++;
  }
  printf("%d\n", m);
  for(int i=1;i<=n;i++) {
    if (i>1&&gcd(p[i-1],p[i]) > 1) {
      printf("1 ");
    }
    printf("%d ", p[i]);
  }
  printf("\n");
  return 0;
}
