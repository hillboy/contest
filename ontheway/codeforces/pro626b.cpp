#include<stdio.h>
#define maxn 203

int i,j,n,m;

bool checked[maxn][maxn][maxn];

int p[3];

bool ans[3];

void make() {

  if(checked[p[0]][p[1]][p[2]]) 
    return;
  checked[p[0]][p[1]][p[2]] = 1;

  int i,sum=0,ansi;
  for(i=0;i<3;i++) {
    if(p[i]) {
      sum+=p[i];
      ansi=i;
    }
    if(p[i]>=2) {
      p[i]--;
      make();
      p[i]++;
    }
    if(p[(i+1)%3] && p[(i+2)%3]) {
      p[(i+1)%3]--;
      p[(i+2)%3]--;
      p[i]++;
      make();
      p[(i+1)%3]++;
      p[(i+2)%3]++;
      p[i]--;
    }
  }
  if(sum==1) {
    ans[ansi]=1;
  }
}

int main() {
  scanf("%d", &n);
  char a;
  for(i=1;i<=n;i++) {
    scanf(" %c", &a);
    if(a=='R')p[0]++;
    if(a=='G')p[1]++;
    if(a=='B')p[2]++;
  }
  make();
  if(ans[2])printf("B");
  if(ans[1])printf("G");
  if(ans[0])printf("R");
  return 0;
}
