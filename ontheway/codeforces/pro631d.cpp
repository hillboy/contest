#include<stdio.h>
#include<algorithm>
using namespace std;

typedef long long int LD;

#define maxn 200100

LD ss[maxn],tt[maxn];

int jump[maxn];

int i,j,n,m;

// indexed 1
// KMP kmp
template<typename T>
void build_jump(T s[maxn], int jump[maxn], int n) {
  jump[1]=2;
  int i,j;
  for(i=2;i<=n;i++) {
    j=jump[i-1];
    while(j && s[j+1] !=s[i]) {
      j=jump[j];
    }
    if(s[j+1]==s[i]) {
      jump[i]=j+1;
    } else {
      jump[i]=0;
    }
  }
}

struct st {
  int n;
  LD p[maxn];
  char c[maxn];

  void add(int now, char a) {
    if(n==0 || c[n] != a) {
      n++;
      p[n]=now;
      c[n]=a;
    } else {
      p[n]+=now;
    }
  }
}s, t;

LD ans;

bool ct(int i, int j) {
  return s.c[i] == t.c[j] && s.p[i] >= t.p[j];
}

void case1() {
  int i;
  for(i=1;i<=s.n;i++) {
    if(s.c[i]==t.c[1]) {
      if(s.p[i] >=t.p[1]) {
        ans+=s.p[i]-t.p[1]+1;
      }
    }
  }
}
void case2() {
  for(int i=1;i<s.n;i++) {
    if(ct(i,1) && ct(i+1, 2)) {
        ans++;
    }
  }
}




void case3() {
  int i,j;
  for(i=1;i<=s.n;i++) {
    ss[i]=s.p[i]*30+s.c[i]-'a';
  }
  for(i=2;i<t.n;i++) {
    tt[i-1]=t.p[i]*30+t.c[i]-'a';
  }
  n=s.n;
  m=t.n-2;
  build_jump(tt, jump, m);
  j=0;
  for(i=1;i<=n;i++) {
    while( j && tt[j+1] != ss[i]) {
      j=jump[j];
    }
    if(tt[j+1]==ss[i]) {
      j++;

      if(j==m) {
        if(i-m>0 && i<n) {
          if(ct(i-m,1) && ct(i+1, t.n)) {
            ans++;
          }
        }
        j=jump[j];
      }
    }
  }
}

int main() {
  int n,m;
  scanf("%d %d", &n, &m);
  int a;
  char b;
  while(n--) {
    scanf(" %d-%c", &a, &b);
    s.add(a, b);
  }
  while(m--) {
    scanf(" %d-%c", &a, &b);
    t.add(a,b);
  }
  if(t.n==1) {
    case1();
    goto aaa;
  }
  if(t.n==2) {
    case2();
    goto aaa;
  }
  case3();
aaa:printf("%lld\n", ans);
  return 0;
}
