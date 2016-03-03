#include<stdio.h>
#include<algorithm>
using namespace std;

int i,j,n,m;


int p[51000], q[51000], pi[51000], qi[51000];


int main() {
  int t, a,b,c,tt=0;
  scanf("%d %d %d", &n, &m, &t);
  while(t--) {
    tt++;
    scanf("%d %d %d", &a, &b, &c);
    if(a==1) {
      p[b]=c;
      pi[b]=tt;
    } else {
      q[b]=c;
      qi[b]=tt;
    }
  }
  for(i=1;i<=n;i++) {
    for(j=1;j<m;j++) {
      if(pi[i] || qi[j]) {
        if(pi[i]>qi[j]) {
          printf("%d ", p[i]);
        } else {
          printf("%d ", q[j]);
        }
      } else {
        printf("0 ");
      }
    }
    if(pi[i] || qi[j]) {
      if(pi[i]>qi[j]) {
        printf("%d\n", p[i]);
      } else {
        printf("%d\n", q[j]);
      }
    } else {
      printf("0\n");
    }
  }
  return 0;
}
