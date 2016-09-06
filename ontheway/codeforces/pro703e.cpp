#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>
using namespace std;

#define forlr(i,l,r) for(i=l;i<r;i++)
#define forrl(i,r,l) for(i=r-1;i>=l;i--)
#define for0r(i,r) forlr(i,0,r)

#define forltr(i,l,r) for(i=l;i<=r;i++)
#define for1tr(i,r) forltr(i,1,r)
#define forrtl(i,r,l) for(i=r;i>=l;i--)

#define forcnt(n) for(int cnt=n; cnt; cnt--)

#define X(x) (x).first
#define Y(x) (x).second

#define mymemset(x, val) memset(x, val, sizeof(x))
#define sz(x) ((int)x.size())

typedef long long int LD;

#define maxn 20

LD dividers[maxn];

int mods[maxn],t;

int nowa[maxn], nowb[maxn];

int i,j,n, mm;

LD m;

void decode(int n, int *p) {
  int i;
  for0r(i, t) {
    p[i] = n%mods[i];
    n/=mods[i];
  }
}

int encode(int *p) {
  int i;
  int ans = 0;
  for(i=t-1;i>=0;i--) {
    ans *= mods[i];
    ans+=p[i];
  }
  return ans;
}

pair<int, LD> p[1<<maxn];

int found[1<<maxn], last[1<<maxn];

int que[1<<maxn], qt;

vector<int> ans[1<<maxn];

int main() {
  scanf("%d %lld", &n, &m);
  LD now, nownow;
  if (m==1) {
    LD ans = -1;
    for1tr(i, n) {
      scanf("%lld", &now);
      if(ans<0||now<ans)
        ans = now, nownow = i;
    }
    printf("1\n%lld\n", nownow);
    return 0;
  }
  forltr(i, 2, 1000000) {
    if (m % i ==0) {
      dividers[t] = i;
      mods[t]=1;
      while(m%i==0) {
        mods[t]++;
        m/=i;
      }
      t++;
    }
  }
  if (m>1) {
    dividers[t] = m;
    mods[t]=2;
    t++;
  }
  mm = 1;
  for0r(i, t) {
    mm *= mods[i];
  }
  qt = 1;
  
  found[0]= 0;

  forcnt(n) {
    scanf("%lld", &now);
    mymemset(nowb, 0);
    nownow = now;
    bool has = false;
    for0r(i, t) {
      if (nownow % dividers[i] == 0) {
        has = true;
        while(nownow % dividers[i] ==0) {
          nownow /= dividers[i];
          nowb[i] ++;
        }
      }
    }
    if (!has)
      continue;

    sort(que, que+qt);

    for (j=qt-1;j>=0;j--) {
      decode(que[j], nowa);
      bool unchanged = true;
      for0r(i, t) {
        if(nowb[i] && nowa[i] < mods[i] -1) {
          unchanged = false;
          nowa[i]+=nowb[i];
          if(nowa[i] >= mods[i])
            nowa[i] = mods[i]-1;
        }
      }
      if (unchanged) {
        continue;
      }
      /*
      for0r(i, t) {
        printf("%d ", nowa[i]);
      }
      printf("<---- nowa\n");
      for0r(i, t) {
        printf("%d ", nowb[i]);
      }
      printf("<---- nowb\n");
      */
      int k = encode(nowa);
      auto temp = make_pair(p[que[j]].first + 1, p[que[j]].second + now);
      if(found[k]) {
        if (temp < p[k]) {
          p[k] = temp;
          found[k] = n-cnt+1;
          last[k] = que[j];
          ans[k] = ans[que[j]];
          ans[k].push_back(n-cnt+1);
        }
      } else {
        found[k] = n-cnt+1;
        p[k] = temp;
        que[qt++] = k;
        last[k] = que[j];
        ans[k] = ans[que[j]];
        ans[k].push_back(n-cnt+1);
      }
    }
  }

  if (found[mm-1]) {
    printf("%d\n", p[mm-1].first);
    i = mm-1;
    for0r(j, sz(ans[i])) {
      printf("%d ", ans[i][j]);
    }
  } else {
    printf("-1\n");
  }
  return 0;
}
