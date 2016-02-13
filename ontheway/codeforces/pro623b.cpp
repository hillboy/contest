#include<stdio.h>
#define maxn 1000100

typedef long long int LD;

int p[maxn];
LD q[maxn];
LD maxint;

int i,j,n,m,A,B;

LD ans = -1;

void updateans(LD a) {
  if(ans<0 || a<ans)
    ans=a;
}

void solve1() {
  LD sum = 0, nowmin = 0, sum2=0;
  LD nowans = 0;
  for(i=1;i<=n;i++) {
    sum+=q[i];
    q[i]-=A;
    sum2+=q[i];
    if(sum2<nowmin)
      nowmin=sum2;
    if(sum2 - nowmin > nowans) {
      nowans = sum2-nowmin;
    }
  }
  updateans(sum-nowans);
}

LD solveleft(int k) {
  LD sum = 0, nowmin = 0, sum2=0;
  LD nowans = 0;
  for(i=1;i<=k;i++) {
    sum+=q[i];
    q[i]-=A;
    sum2+=q[i];
    if(sum2<nowmin)
      nowmin=sum2;
  }
  if(sum2 - nowmin > nowans) {
    nowans = sum2-nowmin;
  }
  return sum-nowans;
}

LD solveright(int k) {
  LD sum = 0, nowmin = 0, sum2=0;
  LD nowans = 0;
  for(i=k;i<=n;i++) {
    sum+=q[i];
    q[i]-=A;
    sum2+=q[i];
    if(sum2>nowans)
      nowans = sum2;
  }
  return sum-nowans;
}

void solve(int a) {
  int left = -1, right = -1;
  for(i=1;i<=n;i++) {
    if(p[i]%a==0) {
      q[i]=0;
    } else if ( (p[i] + 1) % a==0) {
      q[i] = B;
    }else if ( (p[i] - 1) % a==0) {
      q[i] = B;
    } else {
      q[i]=maxint;
      if(left < 0 )
        left = i;
      right = i;
    }
  }
  if(left<0) {
    solve1();
    return;
  }

  LD nowans=A;
  nowans*=(right-left+1);
  if(left>1) {
    nowans+=solveleft(left-1);
  }
  if(right<n) {
    nowans += solveright(right+1);
  }
  updateans(nowans);
}

void make1(int a) {
  if(a<=1) {
    return;
  }
  long long int i=2;
  while(i*i<=a) {
    if(a%i==0){
      while(a%i==0) {
        a/=i;
      }
      solve(i);
    }
    i++;
  }
  if(a>1) {
    solve(a);
  }
}

int main() {
  scanf("%d %d %d", &n, &A,&B);
  for(i=1;i<=n;i++) {
    scanf("%d", &p[i]);
    if(m==0 || p[i]< m)
      m=p[i];
  }
  maxint = n;
  maxint*=A;
  make1(p[1]);
  make1(p[1]-1);
  make1(p[1]+1);
  make1(p[n]);
  make1(p[n]-1);
  make1(p[n]+1);
  printf("%lld\n", ans);
  return 0;
}
