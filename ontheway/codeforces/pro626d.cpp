#include<stdio.h>
#include<algorithm>
#define maxn 5111

int p[maxn];

int delta[maxn],num[maxn];

int i,j,r,n,m;

void make() {
  double a=0,b=0,c=0,total=0;
  for(r=1;r<maxn;r++) if(num[r]) {
    a=0;
    j=1;
    b=0;
    for(i=r-1;i;i--) {
      while(i+j<r) {
        b+=num[j];
        j++;
      }
      a+=b*num[i];
    }
    c+=a*num[r];
  }
  for(i=1;i<maxn;i++)
    total+=num[i];
  total=total*total*total;
  printf("%.10lf\n", c/total);
}


int main() {
  scanf("%d", &n);
  for(i=1;i<=n;i++) {
    scanf("%d", &p[i]);
  }
  std::sort(&p[1], &p[1+n]);
  for(i=1;i<=n;i++) {
    for(j=i+1;j<=n;j++) {
      num[p[j]-p[i]]++;
    }
  }
  make();
  return 0;
}
