#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include <map>
#include <string>
#include <math.h>
#include <string>
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

vector<string> p[11];

int i,j,n,m;

char sep;

char buffer[100];

vector<string> ans;

int ptr[11];

int main() {
  scanf("%d", &n);
  int start = 100, end = 0, total;
  forcnt(n) {
    scanf("%s%n", buffer,&j);
    p[j-1].push_back(buffer);
    if(j<start) start = j;
    if(j>end) end = j;
  }
  start --; end --;
  total = start + end;
  scanf(" %c", &sep);
  for1tr(i, 10) {
    sort(p[i].begin(), p[i].end());
  }
  for1tr(i, 10) {
    while(ptr[i] < sz(p[i])) {
      string& a = p[i][ptr[i]];
      ptr[i]++;
      string& b = p[total-i][ptr[total-i]];
      ptr[total-i]++;
      if(a+sep>b+sep)
        ans.push_back(b+sep+a);
      else
        ans.push_back(a+sep+b);
    }
  }
  sort(ans.begin(), ans.end());
  for(auto& i : ans) {
    printf("%s\n", i.c_str());
  }
  return 0;
}
