#include<stdio.h>

int n,m,P;

int i,j;

int main() {
  int ii,nn;
  bool output;
  scanf("%d", &nn);
  for(ii=1;ii<=nn;ii++) {
    output=false;
    if(ii==22)
      output = true;
    scanf("%d %d %d", &n, &m, &P);
    if (output) {
      printf("%d %d %d\n", n, m, P);
    }
    for(i=1;i<=n;i++) {
      for(j=1;j<=m;j++) {
        int a;
        scanf("%d", &a);
        if(output)
        printf("%d ", a);
      }
      if(output) 
        printf("\n");
    }
    for(i=1;i<n;i++) {
      int a,b;
      scanf("%d %d", &a, &b);
      if(output) {
        printf("%d %d\n", a, b);
      }
    }
  }
  return 0;
}
