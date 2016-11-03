#include<stdio.h>
#include<algorithm>
#include<unordered_map>
using namespace std;

#define div 1000000000
typedef long long int LD;

#define maxn 10000003

int noprime[maxn];
int q[maxn], t;

int F[maxn];

int sumFmF[maxn];

// Linear prime number sieves
void prepare() {
  int i, j;
  for(i=2;i<maxn;i++) {
    if(!noprime[i]) {
      q[++t]=i;
      noprime[i]=i;
    }
    for(j=1;j<=t;j++) {
      if(double(q[j])*i + 1e-9< maxn) {
        noprime[q[j]*i] = q[j];
      } else {
        break;
      }
      if(i%q[j]==0)
        break;
    }
  }
  F[1]=1;
  for(i=2;i<maxn;i++) {
    if(noprime[i]==i) {
      F[i]=-1;
    } else {
      j=i;
      while(j%noprime[i]==0)
        j/=noprime[i];
      if(i/j>noprime[i]) {
        F[i]=0;
      } else {
        F[i]=-F[j];
      }
    }
  }
}

struct Reverse2 {
  // ax + by = gcd(a,b)
  long long int extend_gcd(long long int a, long long int b,
                           long long int &x, long long int &y) {
    long long int ans,t;
    if(b==0){x=1;y=0;return a;}
    ans=extend_gcd(b,a%b,x,y);t=x;x=y;y=t-(a/b)*y;
    return ans;
  }

  // reverse(a) * a  == 1 (mod div)
  long long int reverse(LD a) {
    static long long int x,y,ans;
    ans=extend_gcd(a, div, x, y);
    if(x<0)
      return (x%div+div);
    return x;
  }
} r2;

LD pow(LD a,LD n) {
  LD ans = 1, now = a;
  while(n) {
    if(n&1) {
      ans *= now; ans %= div;
    }
    now *= now;
    now%=div;
    n>>=1;
  }
  return ans;
}

LD mul(LD& a, LD b) {
  a*=b;
  a%=div;
  return a;
}

// 1+a+a^2+...+a^n
LD sum_pow(LD a, LD n) {
  n++;
  LD ans = 0, now = 1, nownow = 1;
  while(n) {
    if(nownow==1)
      nownow=a;
    else {
      mul(nownow, nownow);
    }
    if(n&1) {
      mul(ans, nownow);
      ans+=now;
      if(now>=div)
        now-=div;
    }
    now = now + now*nownow;
    now%=div;
    n/=2;
  }

  return ans;
}


LD D1(LD now) {
  LD a = 2,b;
  LD ans = 1;
  while(a*a<=now) {
    b=1;
    while(now%a==0) {
      b*=a;
      now/=a;
    }
    if(b>1) {
      b*=a;
      b-=1;
      b%=div;
      mul(ans, b);
      mul(ans,r2.reverse(a-1));
    }
    a++;
  }
  if(now>1) {
    mul(ans, now+1);
  }
  return ans;
}

LD D2(LD now) {
  LD a = 2;
  LD ans = 1;
  int k = 0;
  while(a*a<=now) {
    k=0;
    while(now%a==0) {
      now/=a;
      k++;
    }
    if(k) {
      mul(ans, sum_pow(a, k));
    }
    a++;
  }
  if(now>1) {
    mul(ans, now+1);
  }
  return ans;
}

int C1(int n) {
  int i,j;
  LD ans = 0;
  LD d,dd;
  for(i=1;i<=n;i++) {
    for(j=1;j<=n;j++) {
      d=(LD)i*j;
      dd=d;
      while(dd) {
        if(d%dd==0) {
          ans+=dd%div;
          if(ans>=div)
            ans-=div;
        }
        dd--;
      }
    }
  }
  return ans;
}

int C2(int n) {
  int i,j;
  LD ans = 0;
  for(i=1;i<=n;i++) {
    for(j=1;j<=n;j++) {
      ans+=D2(i*j);
      if(ans>=div)
        ans-=div;
    }
  }
  return ans;
}

int gcd(int a, int b) {
  if(a>b)
    return gcd(b,a);
  if(a==0)
    return b;
  return gcd(b%a, a);
}

int C3(int n) {
  int i,j,r;
  LD ans = 0;
  for(i=1;i<=n;i++) {
    for(j=1;j<=n/i;j++) {
      for(r=1;r<=n;r++) {
        if(gcd(j,r)==1) {
          ans+= (LD)(n)/r * r * i;
          if(ans>=div)
            ans-=div;
        }
      }
    }
  }
  return ans;
}

void fix(LD& a) {
  a%=div;
  if(a<0)
    a+=div;
}

int C4(int n) {
  int e,u,k;
  LD ans = 0, now;
  for(e=1;e<=n;e++) {
    for(u=1;u<=n/e;u++) if(F[u]) {
      now = F[u]*u;
      mul(now, e);
      mul(now, n/(e*u));
      for(k=1;k<=n/u;k++) {
        ans+=now*k%div*(n/k/u)%div;
        fix(ans);
      }
    }
  }
  return ans;
}

int C5(int n) {
  int e,u,k,er;
  LD ans = 0, now,nownow;
  for(e=1,er=1;e<=n;e=er+1) {
    er=(n/(n/e));
    nownow=0;
    for(u=1;u<=n/e;u++) if(F[u]) {
      now = F[u]*u;
      mul(now, n/(e*u));
      for(k=1;k<=n/u;k++) {
        nownow+=now*k%div*(n/k/u)%div;
        fix(nownow);
      }
    }
    mul(nownow, (LD)(e+er)*(er-e+1)/2);
    ans+=nownow;
    fix(ans);
  }
  return ans;
}

LD sum2(LD start, LD end) {
  return (start+end)*(end-start+1)/2%div;
}


int C6(int n) {
  int e,u,k,er,kr;
  LD ans = 0, now,nownow;
  for(e=1,er=1;e<=n;e=er+1) {
    er=(n/(n/e));
    nownow=0;
    for(u=1;u<=n/e;u++) if(F[u]) {
      now = F[u]*u;
      mul(now, n/e/u);
      for(k=1,kr=1;k<=n/u;k=kr+1) {
        kr=(n/u/(n/u/k));
        LD temp = now * (n/k/u) %div;
        mul(temp, sum2(k, kr));
        nownow+=temp;
        fix(nownow);
      }
    }
    mul(nownow, sum2(e, er));
    ans+=nownow;
    fix(ans);
  }
  return ans;
}

// sigma (n/i) * i
unordered_map<int ,int> cache;
int sum_k(int n) {
  auto f = cache.find(n);
  if(f!=cache.end())
    return f->second;
  int k,kr;
  int ans=0;
  for(k=1,kr=1;k<=n;k=kr+1) {
    kr=(n/(n/k));
    LD temp = (n/k);
    mul(temp, sum2(k, kr));
    ans+=temp;
    if(ans>=div)
      ans-=div;
  }
  return cache[n]=ans;
}


int C7(int n) {
  int e,u,er;
  LD ans = 0, now,nownow;
  int xa=0, xb=0;
  for(e=1,er=1;e<=n;e=er+1) {
    er=(n/(n/e));
    nownow=0;
    xa++;
    for(u=1;u<=n/e;u++) if(F[u]) {
      xb++;
      now = F[u]*u;
      mul(now, n/e/u);
      mul(now, sum_k(n/u));
      nownow+=now;
      if(nownow>=div)
        nownow-=div;
    }
    mul(nownow, sum2(e, er));
    ans+=nownow;
    fix(ans);
  }
  printf("%d %d\n", xa, xb);
  return ans;
}

int C8(int n) {
  int e,u,er,ur;
  LD ans = 0, now,nownow;
  int xa=0, xb=0;
  for(int i=1;i<=n;i++) {
    sumFmF[i]=((LD)F[i]*i + sumFmF[i-1])%div;
  }
  for(e=1,er=1;e<=n;e=er+1) {
    er=(n/(n/e));
    nownow=0;
    xa++;
    for(u=1,ur=1;u<=n/e;u=ur+1) {
//      ur=min(n/e/(n/e/u), n/(n/u));
      ur = n/e/(n/e/u);
//      printf("%d %d %d %d\n", u, ur, n/e, n/u);
      xb++;
      now = (sumFmF[ur] - sumFmF[u-1] + div) % div;
      mul(now, n/e/u);
      mul(now, sum_k(n/u));
      nownow+=now;
      if(nownow>=div)
        nownow-=div;
    }
    mul(nownow, sum2(e, er));
    ans+=nownow;
    fix(ans);
  }
  printf("%d %d\n", xa, xb);
  return ans;
}

int C9(int n) {
  LD ans = 0, now,nownow;
  int k,i;
  for(k=1;k<=n;k++) {
    now=(n/k);
    mul(now,k);
    nownow=0;
    for(i=1;i<=k;i++) {
      if(k%i==0) {
        nownow+=F[i]*sum_k(n/i);
        if(nownow<0)
          nownow+=div;
        if(nownow>=div)
          nownow-=div;
      }
    }
    mul(now, nownow);
    ans+=now;
    if(ans>=div)
      ans-=div;
  }
  return ans;
}

void test1000() {
  int n=1000;
  printf("%d\n", C3(n));
  printf("%d\n", C4(n));
  printf("%d\n", C5(n));
  printf("%d\n", C9(n));

}
void test10000() {
  int n = 10000;
  printf("%d\n", C4(n));
  printf("%d\n", C5(n));
  printf("%d\n", C8(n));
}

void test100000() {
  printf("%d\n", C5(100000));
  printf("%d\n", C6(100000));
}

void test1000000() {
  int n=1000000;
  printf("%d\n", C6(n));
  printf("%d\n", C7(n));
  printf("%d\n", C8(n));
}

void test10000000() {
//  printf("%d\n", C6(1000000));
  int n=10000000;
//  printf("%d\n", C7(n));
  printf("%d\n", C8(n));
}

int main() {
//  printf("%d\n", C1(1000));

  prepare();
  test1000();

//  test10000();
//  test10000();
//  test10000000();

  printf("%lu\n", cache.size());
  return 0;
}
