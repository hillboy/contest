#include<stdio.h>

#include<string.h>
#include<algorithm>
#include<map>
#include<set>
#include<vector>
using namespace std;

#define maxn 510

#define forlr(x,l,r) for(x=l;x<(int)r;++x)
#define for1(x,y) forlr(x,0,y)
#define forn(x) for1(x,n)

bool p[maxn][maxn];

int q[maxn*maxn][2],t;
int updates[maxn*maxn][2], tt;

int i,j,n,m;

bool ans[maxn];

int main() {
  scanf("%d %d", &n, &m);
  t=1;
  q[0][0]=0;
  q[0][0]=0;
  p[0][0]=1;
  int now,ta;
  for1(i,n) {
    scanf("%d", &now);
    tt=0;
    for1(j,t) {
      if(now+q[j][0]+q[j][1]<=m) {
        if (!p[ta=(now+q[j][0])][q[j][1]]) {
          p[ta][q[j][1]] = 1;
          updates[tt][0]=ta;
          updates[tt][1]=q[j][1];
          tt++;
        }
        if (!p[q[j][0]][ta=(now+q[j][1])]) {
          p[q[j][0]][ta] = 1;
          updates[tt][0]=q[j][0];
          updates[tt][1]=ta;
          tt++;
        }
      }
    }
    while(tt--) {
      q[t][0]=updates[tt][0];
      q[t][1]=updates[tt][1];
      t++;
    }
  }
  for1(i,m) {
    if(p[i][m-i] || p[m-i][i]) {
      ans[i]=1;
      ans[m-i]=1;
    }
  }
  j=0;
  for1(i,m+1) {
    if(ans[i])
      j++;
  }
  printf("%d\n", j);
  for1(i, m+1) {
    if(ans[i]) {
      printf("%d ", i);
    }
  }
  return 0;
}
