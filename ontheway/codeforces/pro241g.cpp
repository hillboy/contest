#include<stdio.h>

int i,j,n,m;

int main(){
  printf("%d\n",310);
  printf("%d %d\n",600000,0);
  int len=100000,delta=5000;
  for(i=2;i<310;i++){
    len+=delta;
    printf("%d %d\n",delta,len);
    delta-=10;
  }
  printf("%d %d\n",1000000,1000000);
  return 0;
}
