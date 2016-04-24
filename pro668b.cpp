#include<stdio.h>

#include<string.h>

int i,j,n,m;

#define maxn 1001000

int total;


int p[maxn];

bool q[maxn];

int t;


void fix(int& a) {
  a = ((a%n)+n)%n;
}

int main() {
  scanf("%d %d", &n, &m);
  bool even1 = true;
  int a,b;
  while(m--) {
    scanf("%d", &a);
    if(a==1) {
      scanf("%d", &b);
      fix(b);
      total += b;
      fix(total);
      if(b&1) {
        even1 = !even1;
      }
    } else {
      if(t && q[t-1]==even1) {
        t--;
      } else {
        q[t]=even1;
        t++;
      }
    }
  }
  int di = 1;
  if(t && q[0]) {
    di=1;
  } else {
    di=-1;
  }
  for(i=0;i<n;i++) {
    if(i&1) {
      j=i;
      j-=t*(di);
      fix(j);
      j+=total;
      fix(j);
      p[j]=i;
    } else {
      j=i;
      j+=t*(di);
      fix(j);
      j+=total;
      fix(j);
      p[j]=i;
    }
  }
  for(i=0;i<n-1;i++) {
    printf("%d ", p[i]+1);
  }
  printf("%d\n", p[i]+1);
  return 0;
}
