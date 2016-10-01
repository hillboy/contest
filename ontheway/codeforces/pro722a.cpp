#include<stdio.h>

char s[100];

char ss[100];

int ii,i,j,n,m;

int main() {
  scanf("%d", &n);
  scanf("  %s", s);
  if(s[3] > '5')
    s[3] = '0';
  int now;
  if(n==12) {
    ii=0;
    j=100;
    
    for(i=1;i<=12;i++) {
      now = 0;
      sprintf(ss, "%02d", i);
      if(s[0]!=ss[0])
        now++;
      if(s[1]!=ss[1])
        now++;
      if(now<j){
        j=now;
        ii=i;
      }
    }
    sprintf(ss, "%02d", ii);
    s[0]=ss[0];
    s[1]=ss[1];
  } else {
    ii=0;
    j=100;
    
    for(i=0;i<=23;i++) {
      now = 0;
      sprintf(ss, "%02d", i);
      if(s[0]!=ss[0])
        now++;
      if(s[1]!=ss[1])
        now++;
      if(now<j){
        j=now;
        ii=i;
      }
    }
    sprintf(ss, "%02d", ii);
    s[0]=ss[0];
    s[1]=ss[1];
  }
  printf("%s\n", s);

  return 0;
}
