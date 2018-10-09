#include<stdio.h>
#include<algorithm>

using namespace std;

#define maxn 100010

int i,j,n,m, L;

long long int S;

int fa[maxn], last[maxn], ind[maxn], e[maxn], t, high[maxn];

long long int w[maxn];

void adde(int a, int b) {
  fa[b]=a;
  t++;
  last[t]=ind[a];
  e[t]=b;
  ind[a]=t;
}

long long int stS[maxn];

int dp(int a, int st) {
  int i, k = -1, ans = 0;
  stS[st] = stS[st-1] + w[a];

  for(i=ind[a];i;i=last[i]) {
    ans+= dp(e[i], st+1);
    if( k < 0 || high[e[i]] < k) {
      k = high[e[i]];
    }
  }
  if(k<0 || k > st) {
    j = std::lower_bound(stS, &stS[st+1], stS[st] -S)-stS;
    if(st-j>L) {
      j=st-L;
    }
    k=j+1;
    ans++;
  }
  high[a]=k;
  return ans;
}



int main() {
  scanf("%d %d %lld", &n, &L, &S);

  for(i=1;i<=n;i++) {
    scanf("%lld", &w[i]);
    if(w[i] > S) S=-1;
  }
  if(S<0) {
    printf("-1\n");
    return 0;
  }
  for(i=2;i<=n;i++) {
    scanf("%d", &j);
    adde(j, i);
  }
  printf("%d\n", dp(1, 1));
  return 0;
}
