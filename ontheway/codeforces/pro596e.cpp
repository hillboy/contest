#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>
using namespace std;

#define forlr(i,l,r) for(i=l;i<r;i++)
#define forrl(i,r,l) for(i=r-1;i>=l;i--)
#define for0r(i,r) forlr(i,0,r)

#define forltr(i,l,r) for(i=l;i<=r;i++)
#define for1tr(i,r) forltr(i,1,r)
#define forrtl(i,r,l) for(i=r;i>=l;i--)

#define forcnt(n) for(int cnt=n; cnt; cnt--)

#define X(x) (x).first
#define Y(x) (x).second

#define mymemset(x, val) memset(x, val, sizeof(x))
#define sz(x) ((int)x.size())

typedef long long int LD;
#define maxn 211

int i,j,n,m,num_q;

int p[maxn][maxn];

int nxt[maxn][maxn][10];

int di[10][2];

int checked[maxn][maxn];

int loop[maxn*maxn], loopnum, loopmask;

int loopa, loopb;

bool tail[maxn][maxn];

void dfs(int a, int b) {
  checked[a][b]=1;
  int i;
  int aa = a + di[p[a][b]][0], bb = b + di[p[a][b]][1];
  if(aa<1||aa>n || bb < 1 || bb >m) {
    loopnum++;
    loop[loopnum] = 1<<p[a][b];
    for0r(i, 10) {
      nxt[a][b][i] = -loopnum;
    }
    checked[a][b] = 2;
    return;
  }
  tail[aa][bb]=true;
  if(!checked[aa][bb]) {
    dfs(aa, bb);
  }
  if (checked[aa][bb]==1) {
    loopa = aa;
    loopb = bb;
    loopnum ++;
    loopmask=0;
  }
  if(loopa) {
    loopmask |= (1<<p[a][b]);
    for0r(i, 10) {
      nxt[a][b][i] = -loopnum;
    }
    if(loopa==a && loopb==b) {
      loopa=loopb=0;
      loop[loopnum] = loopmask;
    }
    checked[a][b] = 2;
    return;
  }
  for0r(i, 10) {
    nxt[a][b][i] = nxt[aa][bb][i];
  }
  nxt[a][b][p[aa][bb]] = (aa << 10) + bb;
  checked[a][b]=2;
  return;
}


int suffix[1000100];
char s[1000100];

int len;

int main() {
  scanf("%d %d %d", &n, &m, &num_q);
  char c;
  for1tr(i,n) {
    for1tr(j,m) {
      scanf(" %c", &c);
      p[i][j]=c-'0';
    }
  }
  for0r(i, 10) {
    scanf("%d %d", &di[i][0], &di[i][1]);
  }

  for1tr(i,n) {
    for1tr(j,m) {
      if(!checked[i][j]) {
        dfs(i,j);
      }
    }
  }
  int a,b,x,y;

  while(num_q--) {
    scanf("%s%n", s, &len);
    len=strlen(s);
    int mask;
    for0r(i, len) {
      s[i]-='0';
    }
    suffix[len]=0;
    for(i=len-1;i>=0;i--) {
      suffix[i] = suffix[i+1] | (1<<s[i]);
    }
    bool ok = false;
    int now;
    for1tr(a, n) {
      if(ok)break;
      for1tr(b,m) {
        if(ok)break;
        if(!tail[a][b]) {
          x=a;y=b;i=0;
          now = 0;
          mask=-1;
          if(p[x][y] !=s[0]) {
            now = nxt[x][y][(int)s[0]];
            if(now>0) {
              x = now >> 10;
              y = now & ((1<<10) - 1);
            } else {
              assert(now<0);
              mask = loop[-now];
            }
          }
          while(i<len) {
            if(mask>=0) {
              if((mask&suffix[i]) == suffix[i]) {
                ok = true;
              }
              break;
            }
            i++;
            if(i<len) {
              now = nxt[x][y][(int)s[i]];
              if(now>0) {
                x = now >> 10;
                y = now & ((1<<10) - 1);
              } else {
                assert(now<0);
                mask = loop[-now];
              }
            }
          }
          if(i==len)
            ok=true;
        }
      }
    }
    for1tr(i, loopnum) {
      if((loop[i] & suffix[0]) == suffix[0]) {
        ok = true;
        break;
      }
    }
    if(ok) {
      printf("YES\n");
    } else {
      printf("NO\n");
    }
  }

  return 0;
}
