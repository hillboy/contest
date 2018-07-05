#include <iostream>
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

int i,j,n,m,k;

#define maxn 1000000

vector<pair<int, int> > p;

bool checked[maxn];

int num[maxn];

int main() {
  scanf("%d", &n);
  for0r (i, n) {
    scanf("%d", &j);
    p.push_back(make_pair(j, i));
  }
  sort(p.begin(), p.end());
  int k = 0;
  for0r(i, n) if (!checked[i]) {
    k++;
    m=0;
    j = i;
    while(1) {
      checked[j] = 1;
      m++;
      j = p[j].second;
      if (checked[j])
        break;
    }
    num[i] = m;
  }
  printf("%d\n", k);
  for0r(i, n) if (num[i]) {
    printf("%d", num[i]);
    j=i;
    while(1) {
      printf(" %d", j+1);
      m++;
      j = p[j].second;
      if (j==i)
        break;
    }
    printf("\n");
  }
  return 0;
}
