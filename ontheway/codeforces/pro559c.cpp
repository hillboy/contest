#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;
#define div 1000000007
#define maxn 2011
#define maxm 200010

vector<pair<int, int> >p;

long long int pow(int a,int n) {
  long long int ans = 1, now = a;
  while(n) {
    if(n&1) {
      ans*=now;ans%=div;
    }
    now*=now;
    now%=div;
    n/=2;
  }
  return ans;
}

long long int reverse(int a) {
  return pow(a, div - 2);
}


long long int fac[maxm], rfac[maxm];

void prepare() {
  fac[0]=1;
  rfac[0]=1;
  for(int i=1;i<maxm;i++) {
    fac[i]=fac[i-1]*i;
    fac[i] %= div;
    rfac[i] = reverse(fac[i]);
  }
}


int h,w,n, i,j;

long long int q[maxn];

template <class T>
T sub(T a, T b) {
  T c;
  c.first = a.first - b.first;
  c.second = a.second - b.second;
  return c;
}


long long int C(int n, int a) {
  long long int ans = fac[n];
  ans *= rfac[a];
  ans %= div;
  ans *= rfac[n-a];
  ans %= div;
  return ans;
}

template <class T>
long long int dis(T a, T b) {
  T c = sub(a,b);
  if(c.first < 0 || c.second < 0) {
    return 0;
  }
  return  C(c.first + c.second, c.first);
}


int main() {
  prepare();
  scanf("%d %d %d", &h, &w, &n);
  int a,b;
  for(i=0;i<n;i++) {
    scanf("%d %d",&a, &b);
    p.push_back(make_pair(a,b));
  }
  sort(p.begin(), p.end());
  p.push_back(make_pair(h, w));
  pair<int, int> one = make_pair(1, 1);
  for(i=0;i<=n;i++) {
    q[i] = dis(p[i], one);
    for(j=0;j<i;j++) {
      q[i] -= (q[j] * dis(p[i], p[j])) % div;
      if (q[i] < 0)
        q[i] += div;
    }
  }
  printf("%d\n", (int) q[n]);
  return 0;
}
