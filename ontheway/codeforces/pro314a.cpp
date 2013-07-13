#include<stdio.h>
#include<string.h>
typedef long long int LD;

#define maxn 201000

LD p[maxn];

int i,j,n,m;

int  main(){
  LD now,nowsum=0;
  int tempnow;
  scanf("%d %d",&n,&m);
  j=0;
  for(i=1;i<=n;i++){
    scanf("%d",&tempnow);
    now=tempnow;
    if(nowsum-(n-i)*now*(j)<m){
      printf("%d\n",i);
    }else {
      j++;
      nowsum+=now*j-now;
    }
  }
  return 0;
}
