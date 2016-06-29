#include<stdio.h>

#include<string.h>
#include<algorithm>
#include<map>
#include<set>
#include<vector>
using namespace std;

#define maxn 100100

#define forlr(x,l,r) for(x=l;x<(int)r;++x)
#define for1(x,y) forlr(x,0,y)
#define forn(x) for1(x,n)

int edges[maxn][2];

int colored[maxn];

vector<int> e[maxn];

int i,j,n,m;

void dfs(int a, int c) {
  if(colored[a])
    return;
  colored[a]=c;
  int i;
  for1(i, e[a].size()) {
    dfs(e[a][i],3-c);
  }
}

int main() {
  scanf("%d %d", &n, &m);
  int a,b;
  for1(i,m) {
    scanf("%d %d", &a, &b);
    a--;b--;
    edges[i][0]=a;edges[i][1]=b;
    e[a].push_back(b);
    e[b].push_back(a);
  }
  for1(i,n) {
    if(!colored[i]) {
      dfs(i,1);
    }
  }
  for1(i,m) {
    if(colored[edges[i][0]] == colored[edges[i][1]]) {
      printf("-1\n");
      return 0;
    }
  }
  j=0;
  for1(i,n) {
    if(colored[i]==1)
      j++;
  }
  printf("%d\n", j);
  for1(i,n) {
    if(colored[i]==1)
      printf("%d ", i+1);
  }
  printf("\n");
  j=0;
  for1(i,n) {
    if(colored[i]==2)
      j++;
  }
  printf("%d\n", j);
  for1(i,n) {
    if(colored[i]==2)
      printf("%d ", i+1);
  }
  printf("\n");
  return 0;
}
