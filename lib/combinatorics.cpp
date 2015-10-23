#include <stdio.h>
// global_div is assumed to be the divisor for all mod
#define global_div 1000000007
#define maxn 1000

typedef long long int LD;

struct Reverse {
  virtual LD reverse(LD) = 0;
};

#define MO global_div

// a*b % div
inline int mul_mod(int a,int b){
  int ret;
  __asm__ __volatile__ ("\tmull %%ebx\n\tdivl %%ecx\n"
                        :"=d"(ret):"a"(a),"b"(b),"c"(MO));
  return ret;
}
// performace: r1 > r2 with -O2 (1.7s vs 3s)
// r1 < r2 without -O2 (6.5s vs 4s)
//
struct Reverse1 : public Reverse {
  static const int div = 1000000007;
  // a^n % div
  // for some reason pow() outperformed pow2 and pow3 with -O2.
  // pow, pow2, pow3 = 1.72s, 3.64s, 3.34s
  // while without -O2, pow3 > pow2 > pow
  // pow, pow2, pow3 = 6.55s, 5.48s, 4.16s
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

  // a^n % div
  LD pow2(LD a,LD n) {
    LD ans = 1, now = a;
    while(n) {
      if(n&1) {
        ans = mul_mod(ans, now);
      }
      now =mul_mod(now, now);
      n>>=1;
    }
    return ans;
  }

  // a^n % div
  LD pow3(LD a,LD n) {
    LD ans = 1, now = a;
    while(n) {
      if(n&1) {
        __asm__ __volatile__ ("\tmull %%ebx\n\tdivl %%ecx\n"
                        :"=d"(ans):"a"(ans),"b"(now),"c"(MO));
      }
      __asm__ __volatile__ ("\tmull %%ebx\n\tdivl %%ecx\n"
                            :"=d"(now):"a"(now),"b"(now),"c"(MO));
      n>>=1;
    }
    return ans;
  }

  // reverse(a) * a  == 1 (mod div)
  LD reverse(LD a) {
    return pow(a, div - 2);
  }
} r1;

struct Reverse2 : public Reverse {
  static const long long int div = 1000000007;
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


// O(1) for C(n,a) after O(n) preprocessing
struct Cn {
  static const long long int div = 1000000007;
  // p[i]= i!
  LD p[maxn];
  // revp[i] * p[i] == 1 mod(div)
  LD revp[maxn];
  LD ans [maxn];
  int n;
  void init(int nn, Reverse* r) {
    n = nn;
    int i;
    p[0] = revp[0] = 1;
    for(i=1;i<=n;i++) {
      p[i] = (p[i-1] * i) % div;
      revp[i] = r->reverse(p[i]);
    }

    for(i=0;i<=n;i++) {
      ans[i]= CC(i);
    }
  }
  LD CC(int a) {
    LD ans = p[n];
    ans *= revp[a];
    ans %= div;
    ans *= revp[n-a];
    ans %= div;
    return ans;
  }
  // pick i out of j
  LD Cij(int i, int j) {
    if(i>j)
      return 0;
    LD ans = p[j];
    ans *= revp[i];
    ans %= div;
    ans *= revp[j-i];
    ans %= div;
    return ans;
  }
  LD C(int a) {
    return ans[a];
  }
} cn;

// O(1) for C(a,b) for a<=b<=n after O(n^2) preprocessing
struct Cij_n {
  static const long long int div = 1000000007;
  int n;
  LD p[maxn][maxn];
  void init(int nn) {
    n = nn;
    int i,j;
    p[0][0]=1;
    for(j=1;j<=n;j++) p[0][j]=0;

    for(i=1;i<=n;i++) {
      p[i][0] = 1;
      for(j=1;j<=i;j++) {
        p[i][j] = p[i-1][j-1] + p[i-1][j];
        if(p[i][j] >= div)
          p[i][j] -= div;
      }
      for(;j<=n;j++) {
        p[i][j] = 0;
      }
    }
  }
  // C(a, b)
  LD C(int a, int b) {
    return p[a][b];
  }
} cijn;

void test_r1() {
  int i;
  LD  ans = 0;
  for(i=1;i<=10000000;i++) {
    ans += r1.reverse(i);
  }
  printf("%lld\n", ans);
}

void test_r2() {
  int i;
  LD  ans = 0;
  for(i=1;i<=10000000;i++) {
    ans += r2.reverse(i);
  }
  printf("%lld\n", ans);
}


int main() {
  int n, i,j;
//  test_r1();
//  test_r2();

  scanf("%d", &n);
  cijn.init(n);
  cn.init(n, &r1);

  for(i=0;i<=n;i++) {
    for(j=0;j<=n;j++) {
      if(cn.Cij(j, i) != cijn.C(i, j)) {
        printf("%d %d %lld %lld\n", i, j, cn.Cij(j,i), cijn.C(i,j));
      }
    }
  }
  for(i=0;i<=n;i++) {
    printf("%lld ", cn.C(i));
  }
  return 0;
}
