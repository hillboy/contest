#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
#define maxn 153
typedef long long int LD;

#define maxint 1000000000LL

LD p[maxn][maxn];

LD sum[maxn];

bool checked[maxn][maxn];

bool cando[maxn][maxn];

LD s[maxn], q[maxn];

int i,j,n,m, A, B;

void make(int b, int c) {
//  printf("%d %d\n", b,c);
  if(checked[b][c])
    return;
  checked[b][c]=1;
  if(b==n) {
    if(c<=s[b]) {
      p[b][c]=-maxint;
      cando[b][c]=1;
    } else {
      cando[b][c]=0;
    }
    return;
  }
  if(sum[b]<c)
    return;
  // eat
  int i;
  for(i=0;i<=sum[1];i++) {
    make(b+1, i);
  }

  LD j=maxint;
  bool ok=false;
  for(i=0;i<=sum[b]-c;i++) {
    if(cando[b+1][i])
      ok=true;
  }

  for(i=sum[b]-c+1;i<=sum[b];i++) {
    if(cando[b+1][i]) {
      if(p[b+1][i] < j)
        j=p[b+1][i];
    }
  }
  

  if(ok)
    if(!cando[b][c]) {
      cando[b][c]=1;
      p[b][c]=-j - q[b];
    }

  // not eat
  for(i=0;i<=sum[1];i++) {
    if(cando[b+1][i] && i >=c) {
      j=p[b+1][i]+1-q[b];
      if(j<=0)
        j=1;
      if(!cando[b][c]) {
        cando[b][c]=1;
        p[b][c]=j;
      } else {
        if(p[b][c] > j) {
          p[b][c]=j;
        }
      }
    }
  }
}

int main() {
  scanf("%d %d %d", &n, &A, &B);
  int a,b;
  for(i=1;i<=n;i++) {
    scanf("%d %d", &a, &b);
    q[i]=a;
    s[i]=b;
  }
  for(i=n;i;i--) {
    sum[i]=sum[i+1]+s[i];
  }
  memset(p, 0, sizeof(p));
  for(i=sum[1];i>=0;i--) {
    make(1, i);
    if(cando[1][i] && p[1][i] <= A-B) {
      printf("%d %d\n", i, (int)(sum[1]-i));
      break;
    }
  }
  return 0;
}
