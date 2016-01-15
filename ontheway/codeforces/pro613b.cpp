#include<stdio.h>
#include<algorithm>
using namespace std;
#define maxn 100100
typedef long long int LD;

int p[maxn];

pair<int,int>q[maxn];

LD sum[maxn];

int ansArr[maxn];

int i,j,n,A, c1, c2;

LD m;

LD ans = -1;

void make() {
  LD u1;
  int ansi;
  for(i=n-1;i>=0;i--) {
    sum[i]=sum[i+1]+p[i];
  }

  LD nowmin=0,k=0, temp;
  LD lastu=0,income=0, ansk, ansnowmin;
  j=0;

  for(i=0;i<=n;i++) {
    u1 = A;
    u1*=(n-i);
    u1-=sum[i];
    if(u1>m)
      continue;
    u1=m-u1;
    income+=u1-lastu;
    lastu=u1;

    while(j<i) {
      if(income >= k*(p[j]-nowmin)) {
        income-=k*(p[j]-nowmin);
        nowmin=p[j];
        k++;
      } else {
        break;
      }
      j++;
    }
    LD delta = 0;
    if(k) {
      delta = income/k;
      if(delta>A-nowmin) {
        delta = A-nowmin;
      }
    }

    if(i==0) {
      delta=A;
    }

    temp = (n-i);
    temp *= c1;
    temp += (nowmin+delta) * c2;
    if(temp > ans) {
      ansi=i;
      ans=temp;
      ansk=k;
      ansnowmin=nowmin+delta;
    }
  }
  printf("%lld\n", ans);
  for(i=0;i<ansk;i++) {
    ansArr[q[i].second] = ansnowmin;
  }
  while(i<ansi) {
    ansArr[q[i].second]=q[i].first;
    i++;
  }
  while(i<n) {
    ansArr[q[i].second]=A;
    i++;
  }
  for(i=0;i<n;i++) {
    printf("%d ", ansArr[i]);
  }
  printf("\n");
}

int main() {
  scanf("%d %d %d %d %lld", &n, &A, &c1, &c2, &m);
  for(i=0;i<n;i++) {
    scanf("%d", &p[i]);
    q[i].first = p[i];
    q[i].second = i;
  }
  sort(p, p+n);
  sort(q,q+n);
  make();
  return 0;
}

