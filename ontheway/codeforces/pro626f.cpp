#include<stdio.h>
#include<algorithm>
#include<string.h>
using namespace std;
#define div 1000000007

int i,j,r,n,m;

typedef long long int LD;

int p[203][203][1001];

int q[203];


void add(int a,int b,int c, LD delta) {
  if(c>m)
    return;
  if(delta>=div) {
    delta%=div;
  }
  p[a][b][c] += delta;
  if(p[a][b][c]>=div) {
    p[a][b][c]-=div;
  }
}

inline void make() {
  p[0][0][0]=1;
  int delta=0;
  for(i=1;i<=n;i++) {
    if(i>1)
      delta=q[i]-q[i-1];
    else
      delta=0;
    for(j=0;j<=n;j++) {
      for(r=0;r<=m;r++) {
        LD lastnum = p[i-1][j][r];
        if(lastnum) {
          // join
          add(i, j, r+delta*j, lastnum*(j+1)%div);
          // end
          if(j) {
            add(i, j-1, r+delta*j, lastnum*j%div);
          }
          // add
          add(i, j+1, r+delta*j, lastnum);
        }
      }
    }
  }
  int ans=0;
  for(i=0;i<=m;i++) {
    ans+=p[n][0][i];
    if(ans>=div) {
      ans-=div;
    }
  }
  printf("%d\n", ans);
}


int main() {
  memset(p,0,sizeof(p));
  scanf("%d %d", &n, &m);
  for(i=1;i<=n;i++) {
    scanf("%d", &q[i]);
  }
  sort(&q[1], &q[1+n]);
  make();

  return 0;
}
