#include<stdio.h>

int i,j,n,m;

bool p[20];

int q[20];

int main() {
  scanf("%d %d", &n, &m);
  for(i=1;i<=n;i++) {
    scanf("%d", &q[i]);
  }
  for(i=1;i<=m;i++) {
    scanf("%d", &j);
    p[j]=true;
  }
  for(i=1;i<=n;i++) {
    if(p[q[i]])
      printf("%d ", q[i]);
  }
  printf("\n") ;
  return 0;
}
