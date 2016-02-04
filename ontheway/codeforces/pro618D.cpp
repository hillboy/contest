#include<stdio.h>
#include<algorithm>
using namespace std;

#define maxn 210000

typedef long long int LD;


int di[maxn];
int ind[maxn];

int last[maxn*2], e[maxn*2];

int i,j,n,m,x,y,t;

void adde(int a, int b) {
  di[a]++;
  t++;
  last[t]=ind[a];
  e[t]=b;
  ind[a]=t;
}

LD p[maxn][2];

void dfs(int a,int fa) {
  int i;
  LD sum1=0, tmp, max1=0,max2=0;
  for(i=ind[a];i;i=last[i]) {
    if(e[i]!=fa) {
      dfs(e[i], a);
      sum1+=p[e[i]][1];
      tmp = p[e[i]][0] + 1 - p[e[i]][1];
      if(tmp > max1) {
        max2=max1;
        max1=tmp;
      } else if (tmp > max2) {
        max2=tmp;
      }
    }
  }
  p[a][0]=sum1 + max1;
  p[a][1]=sum1;
  if(sum1+max1+max2 > sum1) {
    p[a][1]=sum1+max1+max2;
  }

  if(p[a][0] > p[a][1]) {
    p[a][1]=p[a][0];
  }
}

void make1() {
  LD ans = y;
  for(i=1;i<=n;i++) {
    if(di[i]==n-1) {
      ans*=(n-2);
      ans+=x;
      break;
    }
  }
  if(i>n) {
    ans*=(n-1);
  }
  printf("%lld\n", ans);
}

int main() {
  scanf("%d %d %d", &n, &x, &y);
  int a,b;
  for(i=1;i<n;i++) {
    scanf("%d %d", &a, &b);
    adde(a,b);
    adde(b,a);
  }
  if(x>=y) {
    make1();
    return 0;
  }
  dfs(1,0);
  LD ans1 = x, ans2 = y;
  ans1*=p[1][1];
  ans2*=n-p[1][1]-1;
  printf("%lld\n", ans1+ans2);
  return 0;
}
