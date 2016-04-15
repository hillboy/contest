#include<stdio.h>
#include<algorithm>
#include<map>
using namespace std;
typedef long long int LD;
#define maxn 200010

typedef pair<LD, LD> point;

int i,j,n,m;

LD p[maxn],q[maxn],sp[maxn],sq[maxn];

map<LD, LD> pp;


point del(point a,point b) {
  point ans = make_pair(b.first - a.first, b.second - a.second);
  return ans;
}

double cross(point a,point b) {
  return 1.0*a.first*b.second - 1.0*a.second*b.first;
}

// c on the right of a->b
bool right(point a,point b,point c) {
  return cross(del(a,b), del(a,c)) < 1e-9;
}

void test1() {
  point a = {0,0};
  point b = {0,2};
  point c = {-1,-1};
  printf("%d\n", right(a,b,c));
}

int main() {
  scanf("%d", &n);
  for(i=1;i<=n;i++) {
    scanf("%d", &j);
    p[i]=j;
    q[i]=i*p[i];
    sp[i]=sp[i-1]+p[i];
    sq[i]=sq[i-1]+q[i];
  }
  LD ans = p[n], temp;
  pp[sp[n]]=sq[n];
  for(i=n-1;i;i--) {

    if(pp.find(sp[i]) != pp.end()) {
      if(pp[sp[i]] < sq[i])
        pp[sp[i]]=sq[i];
    } else {
      pp[sp[i]]=sq[i];
    }

    auto ii  = pp.find(sp[i]);
    auto before = ii;
    auto after = ii;
    if (ii!=pp.begin()) {
      before--;
    }
    after++;
    bool cool = true;
    if(after != pp.end() && ii!=pp.begin()) {
      if (right(*before, *after, *ii)) {
        pp.erase(ii);
        cool = false;
      }
    }
    if(cool) {
      while(1) {
        ii=pp.find(sp[i]);
        if(ii==pp.begin())
          break;
        ii--;
        if(ii==pp.begin())
          break;
        ii--;

        auto jj=ii;
        jj++;
        if(jj==pp.end())
          break;
        auto kk = jj;
        kk++;
        if(kk==pp.end())
          break;

        if (right(*ii, *kk, *jj)) {
          pp.erase(jj);
        } else {
          break;
        }
      }

      while(1) {
        ii=pp.find(sp[i]);

        auto jj=ii;
        jj++;
        if(jj==pp.end())
          break;
        auto kk = jj;
        kk++;
        if(kk==pp.end())
          break;

        if (right(*ii, *kk, *jj)) {
          pp.erase(jj);
        } else {
          break;
        }
      }
    }

    auto start = pp.begin();
    while(start != pp.end()) {
      start = pp.begin();
      auto next = start;
      next ++;
      if(next == pp.end())
        break;
      if ((next->second - start->second) >= (i-1) *  (next->first - start->first)) {
        pp.erase(start);
      }
      else
        break;
    }

    start = pp.begin();
    temp = (start->second - sq[i-1]) - (i-1) * (start->first - sp[i-1]);
    if(temp>ans)
      ans=temp;
  }
  if(ans<0)
     ans=0;
  printf("%lld\n", ans);
  return 0;
}
