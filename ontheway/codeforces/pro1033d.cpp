#include<stdio.h>
#include<algorithm>
#include<map>
#include<set>
using namespace std;
#define maxn 1259929
#define maxm 2000000000000000000LL
#define maxprime 97177
#define DIV 998244353

int i,j,n,m;

int noprime[maxn];
int q[maxn], t;
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
}

long long int gcd(long long int a, long long int b) {
	if (a==0)
		return b;
  if (a>b)
    return gcd(b,a);
  return gcd(b%a, a);
}

long long int myrandom(){
        long long int a;
        a = rand();
        a *= rand();
        a *= rand();
				if (a<0)
					a=-a;
        return a;
}

// Miller_Rabin
long long int square_multiply(long long int x, long long int c, long long int n){
        long long int z;
        z = 1;
        while(c){
                if(c%2==1)z = (z*x)%n;
                x = (x*x)%n;
                c=(c>>1);
        }
        return z;
}
bool isPrime(long long int n){
        long long int k = 0, i, j, m, a;
        m = n - 1;
        while(m%2==0)m=(m>>1),k++;
        for(i=0;i<1000;i++){
                a = 0;
                while(a==0)a  = myrandom()%n;
                a = square_multiply(a, m, n);
                if(a==1)continue;
                for(j=0;j<k;j++){
                        if(a==n-1)break;
                        a = (a*a)%n;
                }
                if(j<k)continue;
                return false ;
        }
        return true;
}


int ans[maxn];

long long int p[maxn];

map<long long int, int> pp;
set<long long int> subprimes;

int main() {
  prepare();
  scanf("%d", &n);
  for(i=1;i<=n;i++) {
    scanf("%lld", &p[i]);
    for(j=1;j<=maxprime;j++) {
      while(p[i]%q[j]==0) {
        p[i]/=q[j];
        ans[j]++;
      }
      if((long long int)(q[j]) * q[j] >p[i])
        break;
    }
  }

  for(i=1;i<=n;i++) if(p[i]>1) {
    for(j=i+1;j<=n;j++) if(p[j] > 1){
      long long int g = gcd(p[i], p[j]);
      if(g==1)
        continue;
      if(g<p[i] || g<p[j]) {
        if (pp.find(g) == pp.end() ) {
          subprimes.insert(g);
          pp[g]=0;
        }
      }
    }
  }

  for(i=1;i<=n;i++) {
    for(auto ii : subprimes) {
      while(p[i] % ii==0) {
        pp[ii] ++;
        p[i] /= ii;
      }
    }
  }

  long long int total = 1;

  for(i=1;i<=n;i++) if(p[i] > 1){
    bool isp = isPrime(p[i]);
    int c = 1;
    for(j=i+1;j<=n;j++) {
      if(p[j]==p[i]) {
        c++;
        p[j]=1;
      }
    }
    total *= (c+1);
    total %= DIV;

    if(!isp) {
      total *= (c+1);
      total %= DIV;
    }
  }

  for (const auto& ii : pp ) {
    total *= ii.second+1;
    total %=DIV;
  }

  for(i=1;i<=maxprime;i++) {
    if(ans[i]>0) {
      total *= ans[i] + 1;
      total %= DIV;
    }
  }

  printf("%d\n", (int)total);
  return 0;
}
