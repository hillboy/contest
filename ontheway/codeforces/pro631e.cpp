#include<stdio.h>
#include<algorithm>
#include<map>
using namespace std;
#define maxn 200100

typedef long long int LD;

int p[maxn];

LD sum[maxn], ans;

int que[maxn];

map<int, int> q;

int i,j,n,m;

bool greater_delta(int i, int j, int r) {
  // (sum[r] - sum[j]) / (r-j) >  (sum[j] - sum[i]) / (j-i)
  return (sum[r]-sum[j]) * (j-i) > (sum[j]-sum[i]) * (r-j);
}

inline void prepare() {

  que[1]=1;que[2]=2;

  m=2;

  for(i=3;i<=n;i++) {
    while(m>1) {
      if(!greater_delta(que[m-1], que[m],i)) {
        m--;
      } else
        break;
    }
    m++;
    que[m]=i;
  }
}

void inline make() {
  for(i=1;i<=n;i++)
    q[p[i]]=0;
  map<int, int>::reverse_iterator ii;
  for(ii=q.rbegin();ii!=q.rend();ii++) {
    while(m>1) {
      if( (sum[que[m]] - sum[que[m-1]]) >= (LD) (ii->first) * (que[m] - que[m-1])) {
        m--;
      } else
        break;
    }
    ii->second=que[m];
  }
}

int main() {
  scanf("%d", &n);
  for(i=1;i<=n;i++) {
    scanf("%d", &p[i]);
    sum[i]=sum[i-1]+p[i];
    ans+=(long long int)(i)*p[i];
  }
  prepare();
  make();
  LD now, nowans=0;
  for(i=1;i<=n;i++) {
    if(q[p[i]] >= i) {
      j=q[p[i]];
      now=p[i];
      now*=(j-i);
      now-= (sum[j] - sum[i]);
      if(now>nowans) {
        nowans=now;
      }
    }
  }
  for(i=n;i;i--)
    sum[i]=sum[i-1];
  prepare();
  make();
  for(i=1;i<=n;i++) {
    if(q[p[i]] < i) {
      j=q[p[i]];
      now = p[i];
      now*=(j-i);
      now-= (sum[j] - sum[i]);
      if(now>nowans) {
        nowans=now;
      }
    }
  }
  printf("%lld\n", ans + nowans);
  return 0;
}
