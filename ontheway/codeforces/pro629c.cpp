#include<stdio.h>
#include<algorithm>
using namespace std;
#define maxn 2009
#define div 1000000007
typedef long long int LD;
int i,j,n,m;


int p[maxn][maxn];

inline void add(int& a, int b) {
  a+=b;
  if(a>=div)
    a-=div;
}

void prepare() {
  p[0][0]=1;
  for(i=1;i<maxn;i++) {
    for(j=0;j<=i;j++) {
      add(p[i][j], p[i-1][j+1]);
      if(j>0)
        add(p[i][j], p[i-1][j-1]);
    }
  }
}

int total, maxright;

void make() {
  long long int ans = 0, now=0;
  int otheri, otherj;
  for(i=maxright;i<=n-m;i++) {
    for(j=maxright;j<=i;j++) {
      now=p[i][j];
      otheri=n-m-i;
      otherj=total+j;
      if(otheri<maxn && otherj < maxn) {
        now*=p[otheri][otherj];
      } else {
        now*=0;
      }
      now%= div;
      ans+=now;
      if(ans>=div)
        ans-=div;
    }
  }
  printf("%d\n", (int)ans);
}

int main() {
  prepare();
  scanf("%d %d", &n, &m);
  char a;
  j=0;
  for(i=1;i<=m;i++) {
    scanf(" %c", &a);
    if(a=='(') {
      j++;
    } else {
      j--;
    }
    if(j<0) {
      if((-j) > maxright) {
        maxright = (-j);
      }
    }
  }
  total = j;
  make();
  return 0;
}
