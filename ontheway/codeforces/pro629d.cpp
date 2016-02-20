#include<stdio.h>
#include<math.h>
#include<map>
#include<algorithm>
#define pi (acos(-1))
using namespace std;
typedef long long int LD;

map<LD, double> p;

int i,j,n,m;

int main() {
  scanf("%d", &n);
  p[0]=0;
  LD v;
  int h,r;
  map<LD, double> ::iterator ii,jj;
  while(n--) {
    scanf("%d %d", &r, &h);
    v=r;
    v*=r;
    v*=h;
    ii=p.lower_bound(v);
    if(ii==p.begin()) {
      continue;
    }
    jj=ii;
    jj--;
    double temp=(jj->second) + v;
    if(ii==p.end()) {
      p[v]=temp;
      continue;
    }
    if(p.find(v) != p.end()) {
      if(p[v] >= temp) {
        continue;
      }
    }
    p[v]=temp;
    while(1) {
      ii=p.find(v);
      ii++;
      if(ii!=p.end()) {
        if((ii->second) <= temp) {
          p.erase(ii);
          continue;
        }
      }
      break;
    }
  }
  ii=p.end();
  ii--;
  printf("%.10lf\n", (ii->second)*pi);
  return 0;
}
