#include<stdio.h>

int gcd(int a,int b) {
  if(a>b)
    return gcd(b,a);
  if(a==0)
    return b;
  return gcd(b%a, a);
}

int main() {
  int a,b,c;
  scanf("%d %d %d", &a, &b, &c);
  int i;
  for(i=0;i<=10000;i++) {
    if(a*i <= c && (c-a*i) % b ==0) {
      printf("Yes\n");
      return 0;
    }
  }
  printf("No\n");
  return 0;
}
