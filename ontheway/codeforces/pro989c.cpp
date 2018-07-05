#include<stdio.h>

#define maxn 50

int i,j,n,m;

int a,b,c,d;

int p[maxn+2][maxn+2];

int last;

void put(int x) {
  p[n][i] = x;
  i++;
  last = x;
}

int main() {
  scanf("%d %d %d %d", &a, &b, &c, &d);
  n=0;
  a--;
  while(b>1 || c > 0 || d > 0 ){
    n++;
    i=1;
    put(1);
    while(i<=maxn) {
      if(b>1 && i<=maxn && last != 2) {
        b--;
        put(2);
        continue;
      }
      if(c>0 && i <= maxn && last != 3) {
        c--;
        put(3);
        continue;
      }
      if(d>0&& i<=maxn && last!= 4) {
        d--;
        put(4);
        continue;
      }
      put(1);
    }
    n++;
    for(i=1;i<=maxn;i++) {
      p[n][i]=1;
    }
  }
  b--;
  n++;
  for(i=1;i<=maxn;i++) {
    p[n][i]=2;
  }
  while(a>0) {
    n++;
    i=1;
    put(2);
    while(i<=maxn) {
      if(a>0 && i<=maxn && last != 1) {
        a--;
        put(1);
        continue;
      }
      put(2);
    }
    n++;
    for(i=1;i<=maxn;i++) {
      p[n][i]=2;
    }
  }
  printf("%d %d\n", n, 50);
  for(i=1;i<=n;i++) {
    for(j=1;j<=maxn;j++) {
      printf("%c", 'A'+p[i][j]-1);
    }
    printf("\n");
  }
  return 0;
}
