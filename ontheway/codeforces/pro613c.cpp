#include<stdio.h>
#define maxn 30

int p[maxn];

int i,j,n,m;

int nowmin=-1;

int ones=0;

int gcd(int a,int b) {
  if(a>b)
    return gcd(b,a);
  if(a==0)
    return b;
  return gcd(b%a, a);
}


void output(char a, int num) {
  while(num--) {
    printf("%c", a);
  }
}


int main() {
  scanf("%d", &n);
  int temp, temp2;
  for(i=1;i<=n;i++) {
    scanf("%d", &p[i]);
    if(p[i]&1) {
      ones++;
    }
    if(nowmin<0) {
      nowmin=p[i];
    } else {
      nowmin=gcd(nowmin, p[i]);
    }
  }
  if(ones>1) {
    printf("0\n");
    for(i=1;i<=n;i++) {
      output('a'+i-1, p[i]);
    }
    return 0;
  }
  if(ones==1) {
    printf("%d\n", nowmin);
    for(j=1;j<=nowmin;j++) {
      for(i=1;i<=n;i++) {
        output('a'+i-1, p[i]/nowmin/2);
      }
      for(i=1;i<=n;i++) {
        output('a'+i-1, p[i]%2);
      }
      for(i=n;i>=1;i--) {
        output('a'+i-1, p[i]/nowmin/2);
      }
    }
    return 0;
  }
  printf("%d\n", nowmin);
  for(j=1;j<=nowmin;j++) {
    if(j&1) {
      for(i=1;i<=n;i++) {
        output('a'+i-1, p[i]/nowmin);
      }
    } else {
      for(i=n;i>=1;i--) {
        output('a'+i-1, p[i]/nowmin);
      }
    }
  }
  return 0;
}
