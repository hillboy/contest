#include<stdio.h>
#include<assert.h>
#include<vector>
using namespace std;

typedef long long int LD;
#define maxn 10000000
#define recursive_bound 16

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
  // a^n % div
  // for some reason pow() outperformed pow2 and pow3 with -O2.
  // pow, pow2, pow3 = 1.72s, 3.64s, 3.34s
  // while without -O2, pow3 > pow2 > pow
  // pow, pow2, pow3 = 6.55s, 5.48s, 4.16s
  // reverse(a) * a  == 1 (mod div)
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

void case1() {
  poly a;
  a.a.push_back(1);
  a.a.push_back(1);
  a.a.push_back(1);
  auto p = a.eval(1<<19, 2, 7340033);
  printf("%lu\n", p.size());
  for(unsigned long i = 0; i< p.size();i ++) {
    printf("%d ", p[i]);
  }
  printf("\n");
}

void case2() {
  poly a,b;
  for(int i = 0; i< 3;i++) {
    a.a.push_back(1);
    b.a.push_back(1);
  }
  int DIV = 7340033;
  int m = 1<<10;
  int w = (int) pow(2, (1<<9) * 7 , DIV);
  // int DIV = 17;
  // int m = 1<<3;
  // int w = 1<<1;
  auto pa = a.eval(m, w, DIV);
  auto pb = b.eval(m, w, DIV);
  poly c;
  c.a.resize(m);
  assert((int)pa.size() == m);
  assert((int)pb.size() == m);
  for(int i=0;i<m;i++) {
    c.a[i] = (long long int)pa[i] *  pb[i] % DIV;
  }
  Reverse1 r(DIV);
  int w1=r.reverse(w);
  long long int m2 = r.reverse(m);
  auto pc = c.eval(m, w1, DIV);
  for(int i=0;i<(int)pc.size();i++) {
    printf("%lld ", (pc[i] * m2 % DIV + DIV )%DIV);
  }
  printf("\n");
}


long long int extend_gcd(long long int a, long long int b,
                         long long int &x, long long int &y) {
  long long int ans,t;
  if(b==0){x=1;y=0;return a;}
  ans=extend_gcd(b,a%b,x,y);t=x;x=y;y=t-(a/b)*y;
  return ans;
}

void case3() {
  long long int x, y;
  auto a = extend_gcd(7340033, 13631489, x, y);
  // 2271917 * 7340033 +  -1223340 * 13631489 = 1
  printf("%lld %lld %lld\n", a, x, y);
}


int main() {
  case3();
  return 0;
}
