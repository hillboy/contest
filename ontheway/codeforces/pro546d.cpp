#include<stdio.h>
#define maxn 5001000

int noprime[maxn];
int q[maxn], t;

void prepare() {
  int i, j;
  for(i=2;i<maxn;i++) {
    if(!noprime[i]) {
      q[++t]=i;
      noprime[i]=i;
    }
    for(j=1;j<=t;j++) {
      if(double(q[j])*i + 1e-9< maxn) {
        noprime[q[j]*i] = q[j];
      } else {
        break;
      }
      if(i%q[j]==0)
        break;
    }
  }
}

int ans[maxn];

void make() {
  int i, j, r;
  for(i=2;i<maxn;i++) {
    j=i;
    r=0;
    while(j>1) {
      r++;
      j/=noprime[j];
    }
    ans[i]=r + ans[i-1];
  }
}

int main() {
  prepare();
  make();
  int nn, a,b;
  scanf("%d", &nn);
  while(nn--) {
    scanf("%d %d", &a, &b);
    printf("%d\n", ans[a]-ans[b]);
  }
  return 0;
}
