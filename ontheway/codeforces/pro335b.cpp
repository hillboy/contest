#include<stdio.h>
#define maxn 51000
#define maxm 50

int p[maxn][maxm+1];

int ans[maxn][maxm+1];

int last[maxn][30];

int i,j,n,m;

char s[maxn],ss[maxn];

void make() {
  p[0][0]=n+1;
  for(i=1;i<=n;i++) {
    for(j=0;j<=maxm;j++){
      p[i][j]=p[i-1][j];
      ans[i][j]=ans[i-1][j];
      if (j) {
        if(p[i-1][j-1])
        if (p[i][j]<last[p[i-1][j-1]-1][s[i]] && last[p[i-1][j-1]-1][s[i]] > i ) {
          p[i][j] = last[p[i-1][j-1]-1][s[i]];
          ans[i][j]=i;
        }
      }
//      printf("%d ",p[i][j]);
    }
//    printf("\n");
  }
  for (i=maxm;i;i--)
    if (p[n][i]) {
      break;
    }
  if (i == 0 ) {
    printf("%c",s[1]+'a');
    return;
  }
//  printf("%d\n",i);
  int t=0,jj;
  char mid =0;
  if(i<=maxm){
    if (i<maxm) {
      for(j=1;j<=n;j++) {
        if(ans[j][i] == j) {
          jj = j;
          if (p[j][i] > j+1 ) {
            mid = s[j+1]+'a';
            break;
          }
        }
      }
      if (mid==0) {
        j=jj;
      }
    } else
      j=ans[n][i];
    jj=i;
    while(j){
      ss[t++]=s[j]+'a';
      j=ans[j-1][jj-1];
      jj--;
    }
  }
  for(i=t-1;i>=0;i--){
    printf("%c",ss[i]);
  }
  if(mid) {
    printf("%c",mid);
  }
  printf("%s\n",ss);
}

int main() {
  scanf("%s%n",&s[1],&n);
  for(i=1;i<=n+1;i++) {
    s[i]-='a';
    for(j=0;j<26;j++)
      last[i][j]=last[i-1][j];
    if (i<=n)
          last[i][s[i]]=i;
  }
  make();

  return 0;
}
