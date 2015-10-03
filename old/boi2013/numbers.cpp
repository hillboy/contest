#include<stdio.h>
#include<string.h>

bool cmp(int a, int b) {
  if(a<0 || b <0) {
    return false;
  }
  return a==b;
}

struct Point {
  long long int p[30][11][11];
  int q[30];
  int i,j,n,m;
  Point(long long int a) {
    memset(q, -1, sizeof(q));
    n=0;
    while(a > 0) {
      n++;
      q[n] = a%10;
      a/=10;
    }
  }
  long long int get() {
    if(n==0)
      return 1;
    if(n==1)
      return q[1] + 1;
    memset(p, 0, sizeof(p));
    p[n+1][10][10]=1;
    int i, j;
    long long int ans = 0;
    for(i=n;i;i--) {
      make(i);
    }
    for(i=0;i<=10;i++) {
      for(j=0;j<=10;j++) {
        ans+=p[1][i][j];
      }
    }
    return ans;
  }
  void make(int a) {
    p[a][10][10] = p[a+1][10][10];
    int i, j, r;
    if(a == n) {
      for(i=1;i<q[a];i++) {
        p[a][10][i] = p[a+1][10][10];
      }
    } else {
      for(i=1;i<10;i++) {
        p[a][10][i] = p[a+1][10][10];
      }
    }

    for(i=0;i<10;i++) {
      for(j=0;j<10;j++) if(i!=j){
        p[a][i][j] += p[a+1][10][j];
        for(r=0;r<10;r++) if (i!=r && j!=r){
          p[a][i][j] += p[a+1][r][i];
        }
      }
    }
    i=n;
    while(i>a) {
      if(q[i] == q[i+1] || q[i] == q[i+2])
        break;
      i--;
    }
    if (i == a && a < n){
      for(i=0;i<q[a];i++) if (i!=q[a+1] && i != q[a+2]) {
        p[a][q[a+1]][i] ++;
      }

      if (a==1) {
        if(!cmp(q[a], q[a+1]) && !cmp(q[a], q[a+2]) && !cmp(q[a+1], q[a+2])) {
          p[a][q[a+1]][q[a]] ++;
        }
      }
    }

  }
};


int main() {
  long long a, b;
  scanf("%lld %lld", &a, &b);
  Point A(a-1), B(b);
  long long int ans = B.get() - A.get();
  if(a==0)
    ans++;
  printf("%lld\n", ans);
  return 0;
}
