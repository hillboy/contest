#include<stdio.h>

int a,b,n,i,j;

char s[1000000];

int main(){
  scanf("%d %d %d",&a,&b,&n);
  sprintf(s,"%d",a);
  j=0;
  while(s[j])
    j++;
  while(n--){
    for(i=0;i<10;i++){
      if((a*10+i)%b==0){
        s[j++]=(i+'0');
        break;
      }

    }
    if(i==10){
        printf("-1\n");
        return 0;
    }
    a=(a*10+i)%b;
  }
  printf("%s\n",s);
  return 0;
}
