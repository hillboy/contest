#include<stdio.h>

int i,j,n,m;

void make1() {
  printf("1\n");
  printf("1000 30 1000000\n");
  for(i=1;i<=1000;i++)  {
    for(j=1;j<=30;j++) {
      printf("%d ", i*j+j);
    }
    printf("\n");
  }
  for(i=1;i<1000;i++) {
    printf("%d %d\n", i, i+1);
  }
}

int main() {
  make1();
  return 0;
  printf("1\n");
  printf("1000 30 1000000\n");
  for(i=1;i<=1000;i++)  {
    for(j=1;j<=29;j++) {
      printf("%d ", i*j+j);
    }
    printf("%d ", 1);
    printf("\n");
  }
  for(i=1;i<1000;i++) {
    printf("%d %d\n", 1, i+1);
  }
  return 0;
}
