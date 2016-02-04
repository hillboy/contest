#include<stdio.h>
#include<algorithm>
using namespace std;
#define maxn 11000001 

typedef long long int LD;
int L, n, m, i, j;

LD D;

LD p[maxn];

int qt;

pair<long long int, int> q[maxn];

bool cmp(pair<LD, int> a, pair<LD, int> b) {
  return a.first > b.first;
}

LD que[maxn];
LD que2[maxn];

int main() {
  int ii,nn;
  scanf("%d", &nn);
  int a;
  for(ii=1;ii<=nn;ii++) {
    printf("Case #%d: ", ii);
    scanf("%d %d %d %lld", &L, &n, &m, &D); 
    if(m>L)
      m=L;
    for(i=0;i<n;i++) {
      scanf("%d", &a);
      q[i].first=a;
      q[i].second=a;
      push_heap(q, q+i+1, std::greater<pair<long long int, int>>());
    }
    qt=0;
    while(L--) {
      que[qt++]=q[0].first;
      pop_heap(q, q+n, std::greater<pair<long long int, int>>());
      q[n-1].first += q[n-1].second;
      push_heap(q, q+n, std::greater<pair<long long int, int>>());
    }
    for(i=0;i<m;i++) {
      que2[i]=0;
    }
    LD ans = 0, now;
    for(i=0;i<qt;i++) {
      now=max(que2[0], que[i]) + D;
      if(now>ans)
        ans=now;
      pop_heap(que2, que2+m, std::greater<LD>());
      que2[m-1]=now;
      push_heap(que2, que2+m, std::greater<LD>());
    }
    printf("%lld\n", ans);
  }
  return 0;
}
