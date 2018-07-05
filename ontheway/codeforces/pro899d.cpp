#include<stdio.h>
#include<algorithm>
#include<string.h>
using namespace std;

long long int i,j,n,m;

long long int k10 (long long int n ) {
  long long int ans = 1;
  while(n-->0) {
    ans*=10;
  }
  return ans;
}

long long int g(long long int n) {
  char s[100];
  long long int l;
  memset(s, 0, sizeof(s));
  l=sprintf(s, "%lld", n);
  if (s[0]<'5')
    return 0;
  long long int ans =0 ;
  ans+= n-k10(l-1)*5 + 1;
  if (s[0]=='9' && n+1 == k10(l))
    ans--;
  return ans;
}

long long int f(long long int n) {
  char s[100];
  long long int l;
  memset(s, 0, sizeof(s));
  l=sprintf(s, "%lld", n);
  long long int ans =0;
  long long int a = s[0]-'0';
  ans += a*a*(k10(l-1)/2);
  ans-=a;
  ans += (n-k10(l-1)*a + 1) * a;
//  if (n+1 == (a+1) * k10(l-1))
//    ans--;
  if (s[1] >'4')
    ans+=g(n%k10(l-1));
  return ans;
}

int main() {
  scanf("%lld", &n);
  if (n<5) {
    printf("%lld\n", n*(n-1)/2);
    return 0;
  }
  m=g(n);
  if (m>0) {
    printf("%lld\n", m);
    return 0;
  }
  m = f(n);
  printf("%lld\n", m);
  return 0;
}
