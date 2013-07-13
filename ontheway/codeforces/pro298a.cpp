#include<stdio.h>

int i,j,n,m;

int l,L,r,R;

int main() {
  scanf("%d",&n);
  char a;
  for(i=1;i<=n;i++){
    scanf(" %c",&a);
    if(a=='R'){
      R=i;
      if (r==0)
        r=i;
    } else if (a=='L') {
      L=i;
      if(l==0)
        l=i;
    }
  }
  if (R){
    if(l)
      printf("%d %d\n",r,R);
    else
      printf("%d %d\n",r,R+1);
  } else {
    printf("%d %d\n",L,l-1);
  }
  return 0;
}


