#include<stdio.h>

#define maxn 100101
typedef long long int LD;

LD p[maxn];

int i,j,n,m;

int dism(int a){
  if(a<=m)
    return m-a;
  else
    return n-(a-m);
}

int  main(){
  scanf("%d %d",&n,&m);
  int min=-1,mi,midis;
  for(i=1;i<=n;i++){
    scanf("%d",&j);
    p[i]=j;
    if(j<min||min<0){
      min=j;
      mi=i;
      midis=dism(i);
    }else if(j==min){
      if(dism(i)<midis){
        mi=i;
        midis=dism(i);
      }
    }
  }
  for(i=1;i<=n;i++){
    if(i!=mi)
      p[i]-=p[mi];
  }
  p[mi]*=n;
  i=mi;
  while(i!=m){
    i++;
    if(i>n)
      i=1;
    p[i]--;
    p[mi]++;
  }
  for(i=1;i<=n;i++){
    printf("%I64d ",p[i]);
  }
  return 0;
}
