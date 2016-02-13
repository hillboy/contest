#include<stdio.h>

#define maxans 12100000
int i,j,n,m;

inline void make() {
  int a,b,c;
  int nn,mm;
  for(i=1;i<=maxans;i++) {
    a=i/2;
    b=i/3;
    c=i/6;
    a-=c;
    b-=c;
    nn=n-a;
    mm=m-b;
    if(nn<0)nn=0;
    if(mm<0)mm=0;
    if(nn+mm<=c) {
      printf("%d\n", i);
      return;
    }
  }
}

int main() {
  scanf("%d %d", &n, &m);
  make();
  return 0;
}
