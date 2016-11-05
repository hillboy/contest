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

#define maxn 5100

int p[maxn];

vector<pair<int, int> > e[maxn];

int ee[maxn][3];

int i,j,n,m;

LD di[maxn];

int num[maxn];

bool cl[maxn];

bool nowcl;

LD dis[maxn], total_dis[maxn];

void dfs1(int a, int fa) {
  num[a] = 1;
  for(auto& i : e[a]) {
    if (i.first !=fa) {
      dfs1(i.first, a);
      dis[a] += dis[i.first];
      dis[a] += (LD) (i.second) * num[i.first];
      num[a] += num[i.first];
    }
  }
}

void dfs2(int a, int fa, LD up) {
  total_dis[a] = dis[a] + up;
  for(auto& i : e[a]) {
    if (i.first !=fa) {
      dfs2(i.first, a, up + dis[a] - dis[i.first] + (LD)(n-num[i.first]*2) * i.second);
    }
  }
}

LD dfs(int a, int fa, LD dis) {
  cl[a] = nowcl;
  di[a] = dis;
  LD sum = 0;
  num[a]=1;
  for(auto& i : e[a]) {
    if(i.first != fa) {
      sum += dfs(i.first, a, dis + i.second);
      sum += (LD) (i.second) * num[i.first];
      num[a] += num[i.first];
    }
  }
  return sum;
}

void make() {
  dfs1(1, 0);
  dfs2(1, 0, 0);
  LD sum1, sum2, num1, num2, total=0, now, nowmin=0, min1, min2, temp;
  int ii;
  for (ii = 0; ii < n-1;ii++) {
    nowcl = false;
    sum1 = dfs(ee[ii][0], ee[ii][1], 0);
    num1 = num[ee[ii][0]];
    nowcl = true;
    sum2 = dfs(ee[ii][1], ee[ii][0], 0);
    num2 = num[ee[ii][1]];
    total += (LD) (ee[ii][2]) * num1 * num2;

    min1 = sum1;
    min2 = sum2;
    for1tr(i, n) {
      if(cl[i]) {
        temp = total_dis[i] - sum1 - (ee[ii][2] + di[i]) * num1;
        if(temp<min2)
          min2= temp;
      } else {
        temp = total_dis[i] - sum2 - (ee[ii][2] + di[i]) * num2;
        if(temp<min1)
          min1= temp;
      }
    }
    now = (min1-sum1) * num2 + (min2 - sum2) * num1;
//    printf("%d %lld\n", ii, now);
//    printf("(%lld %lld) (%lld %lld)\n", min1, sum1, min2, sum2);
    if(now<nowmin)
      nowmin = now;
  }
//  printf("%lld %lld\n", total , nowmin);
  printf("%lld\n", total + nowmin);
}

int main() {
  scanf("%d", &n);
  int a,b,c;
  forcnt(n-1) {
    scanf("%d %d %d", &a,&b,&c);
    e[a].push_back(make_pair(b,c));
    e[b].push_back(make_pair(a,c));
    ee[i][0] = a;
    ee[i][1] = b;
    ee[i][2] = c;
    i++;
  }
  make();
  return 0;
}
