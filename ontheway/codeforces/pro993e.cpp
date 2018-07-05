#include<stdio.h>
#include<string.h>
#include<vector>
using namespace std;

typedef long long int LD;
#define maxn 10000000

LD pow(LD a,LD n, int div) {
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
struct Reverse1 {
  int div;
  Reverse1(int div) : div(div){}
  LD reverse(LD a) {
    return pow(a, div - 2, div);
  }
};

vector<int> fft_eval(unsigned long n, const vector<int>& a, long long int w, int DIV) {
  unsigned int i, m = a.size();
  vector<int> ans(n);
  
  if (n == 1) {
    if(a.size() > 0)
      ans[0] = a[0];
    else 
      ans[0]=0;
    return ans;
  }

  vector<int> a_odd(m/2), a_even(m-m/2);
  for(i=0;i<m/2;i++){
    a_even[i] = a[i*2];
    a_odd[i] = a[i*2 + 1];
  }
  if (m&1) {
    a_even[m-m/2-1] = a[m-1];
  }


  vector<int> f_even = fft_eval(n/2, a_even, w*w%DIV, DIV);
  vector<int> f_odd = fft_eval(n/2, a_odd, w*w%DIV, DIV);
  long long int now = 1;
  for(i=0;i<n/2;i++) {
    ans[i] = (f_even[i] + now * f_odd[i]) % DIV;
    ans[i+n/2] = (f_even[i] - now * f_odd[i]) % DIV;
    now *= w;
    now %= DIV;
  }
  return ans;
}

struct poly {
  vector<int> a;
  vector<int> eval(int n, int w, int DIV) const {
    return fft_eval(n, a, w, DIV);
  }
};

// size of m
vector<int> solve(const poly& a, const poly& b, int m, int w, int DIV) {
  auto pa = a.eval(m, w, DIV);
  auto pb = b.eval(m, w, DIV);
  poly c;
  c.a.resize(m);
  for(int i=0;i<m;i++) {
    c.a[i] = (long long int)pa[i] *  pb[i] % DIV;
  }
  Reverse1 r(DIV);
  int w1=r.reverse(w);
  long long int m2 = r.reverse(m);
  auto pc = c.eval(m, w1, DIV);
  for(int i=0;i<(int)pc.size();i++) {
    pc[i] = (pc[i] * m2 % DIV + DIV )%DIV;
  }
  return pc;
}

int i,j,n,m;

int p[maxn], t;

poly pa, pb;

struct bignum {
  const int wei = 10;
  int p[100], t;

  bignum(const bignum& a) : t(a.t) {
    memcpy(p, a.p, sizeof(p));
  }

  bignum(long long int now): t(0) {
    while(now) {
      p[t++] = now % wei;
      now/=wei;
    }
    if(t==0) {
      t++;
      p[0]=0;
    }
  }
  void mul(long long int a) {
    long long int now = 0, temp;
    int i;
    for(i=0;i<t;i++) {
      temp = a*p[i] + now;
      p[i] = temp % wei;
      now = temp / wei;
    }
    while(now) {
      p[t++] = now % wei;
      now/=wei;
    }
  }

  long long int mod(long long int a) {
    long long int ans = 0;
    int i;
    for(i=t-1;i>=0;i--) {
      ans=(ans*wei + p[i]) % a;
    }
    return ans;
  }
};

void make() {
  int DIV = 7340033;
  int m = 1<<19;
  int w = (int) pow(2, (1<<0) * 7 , DIV);
  auto res1 = solve(pa, pb, m, w, DIV);

  DIV = 13631489;
  m = 1<<19;
  w = (int) pow(2, (1<<0) * 13 , DIV);
  auto res2 = solve(pa, pb, m, w, DIV);
  // 2271917 * 7340033 +  -1223340 * 13631489

  long long int mn = 7340033LL * 13631489;
  long long int m1n1 = 2271917LL * 7340033 % mn;
  long long int m2n2 = (-1223340LL * 13631489 %mn + mn) %mn ;
  bignum m2n2big(m2n2);
  bignum m1n1big(m1n1);

  long long int ans;
  for(i=1;i<t;i++) {
    bignum b1(m1n1big), b2(m2n2big);
    b1.mul(res2[t-i-1]);
    b2.mul(res1[t-i-1]);
    ans = b1.mod(mn) + b2.mod(mn);
    printf(" %lld", ans % mn);
  }
  while(i<=n) {
    i++;
    printf(" 0");
  }
  printf("\n");
}

int main() {
  scanf("%d %d", &n, &m);
  int now = 0;
  long long int zero = 0;
  for(i=1;i<=n;i++) {
    scanf("%d", &j);
    now++;
    if(j<m) {
      p[++t]=now;
      zero += (long long int) now * (now-1) / 2;
      now=0;
    }
  }
  now++;
  zero += (long long int) now * (now-1) / 2;
  p[++t] = now;

  for(i=1;i<=t;i++) {
    pa.a.push_back(p[i]);
  }
  for(i=t;i;i--) {
    pb.a.push_back(p[i]);
  }
  printf("%lld", zero);
  make();
  return 0;
}
