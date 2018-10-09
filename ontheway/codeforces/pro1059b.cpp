#include<stdio.h>

#define maxn 1011

char s[maxn][maxn];

int i,j,n,m, ii,jj;

bool check(int x, int y) {
  int ii,jj;
  for(ii=-1;ii<=1;ii++) for(jj=-1;jj<=1;jj++) if(ii!=0||jj!=0) {
    if(s[x+ii][y+jj] !='#') {
      return false;
    }
  }
  return true;
}

int main() {
  scanf("%d %d", &n, &m);
  for(i=1;i<=n;i++) {
    scanf("%s", &s[i][1]);
  }
  for(i=1;i<=n;i++) {
    for(j=1;j<=m;j++) {
      if(s[i][j] == '#') {
        bool ok = false;
        for(ii=-1;ii<=1;ii++) for(jj=-1;jj<=1;jj++) if(ii!=0||jj!=0) {
          if(check(i+ii, j+jj)) {
            ok = true;
            break;
          }
        }
        if(!ok) {
          printf("NO\n");
          return 0;
        }
      }
    }
  }
  printf("YES\n");
  return 0;
}
