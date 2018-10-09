#include<stdio.h>
#include<algorithm>
using namespace std;
#define maxn 1000100

int i,j,n,m;

int p[maxn], q[maxn];

bool ans[maxn];

int main() {
  scanf("%d", &n);
  for(i=1;i<=n;i++) {
    scanf("%d", &p[i]);
    q[p[i]]=i;
  }
  int x,y;
  for(i=n;i;i--) {
    x=q[i];
    for(j=1;(long long int)j*i <=n;j++) {
      y=x+i*j;
      if(y<=n && p[y] > i &&!ans[y]) {
        ans[x] = true;
        break;
      }
      y=x-i*j;
      if(y>0 && p[y] > i &&!ans[y]) {
        ans[x] = true;
        break;
      }
    }
  }
  for(i=1;i<=n;i++) {
    printf("%c", ans[i]?'A':'B');
  }
  printf("\n");
  return 0;
}
