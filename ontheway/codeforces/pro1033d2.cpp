#include<stdio.h>
#include<algorithm>
#include<cmath>
#include<map>
using namespace std;
typedef long long int LD;

#define DIV 998244353

LD mysqrt3(LD n) {
  LD l=1, r=sqrt(n) + 100, mid, now;
  double tmp;
  while(l<=r) {
    mid=(l+r)/2;
    tmp = mid ;
    tmp*=tmp*tmp;
    if(tmp -100 > n) {
      r = mid-1;
      continue;
    }

    now = mid*mid*mid;

    if(now == n) {
      return mid;
    }
    if (now < n) {
      l=mid+1;
    } else {
      r=mid-1;
    }
  }
  if(l*l*l==n) return l;
  if(r*r*r==n) return r;
  return 0;
}

LD mysqrt(LD n) {
  LD l=1, r=sqrt(n) + 100, mid, now;
  double tmp;
  while(l<=r) {
    mid=(l+r)/2;
    tmp = mid ;
    tmp*=tmp;
    if(tmp -100 > n) {
      r = mid-1;
      continue;
    }
    now = mid * mid;
    if(now == n) {
      return mid;
    }
    if (now < n) {
      l=mid+1;
    } else {
      r=mid-1;
    }
  }
  if(l*l==n) return l;
  if(r*r==n) return r;
  return 0;
}
#define maxn 1000

LD p[maxn];
bool killed[maxn];

map<LD, int> q;

int i,j,n,m;

LD gcd(LD a, LD b) {
  if(a==0)
    return b;
  if(a>b)
    return gcd(b,a);
  return gcd(b%a, a);
}


int main() {
  scanf("%d", &n);
  LD t1, t2;
  for(i=1;i<=n;i++) {
    scanf("%lld", &p[i]);
    t1 = mysqrt(p[i]);
    if(t1) {
      t2=mysqrt(t1);
      if(t2) t1=t2;
    } else {
      t1 = mysqrt3(p[i]);
    }
    if(t1) {
      killed[i]=true;
      if(q.find(t1) == q.end()) {
        q[t1] = 0;
      }
      while(p[i] % t1 ==0) {
        p[i]/=t1;
        q[t1]++;
      }
    }
  }
  for(i=1;i<=n;i++) if(p[i]>1){
    for(j=i+1;j<=n;j++) if(p[j]>1) {
      LD g = gcd(p[i], p[j]);
      if(g>1 && (g<p[i] || g<p[j])) {
        if(q.find(g) == q.end())
          q[g] = 0;
      }
    }
  }

  for(auto& g : q) {
    for(i=1;i<=n;i++) {
      while(p[i] % g.first == 0) {
        killed[i]=1;
        p[i] /= g.first;
        g.second ++;
      }
    }
  }


  LD ans = 1;
  for(i=1;i<=n;i++) if (p[i]>1){
    int c = 1;
    for(j=i+1;j<=n;j++) if(p[j] == p[i]) {
      c++;
      p[j]=1;
    }
    ans*=c+1;
    ans%=DIV;
    if(!killed[i]) {
      ans*=c+1;
      ans%=DIV;
    }
  }
  for(const auto& g : q) {
    ans *= g.second+1;
    ans%=DIV;
  }
  printf("%d\n", (int) ans);


  return 0;
}
