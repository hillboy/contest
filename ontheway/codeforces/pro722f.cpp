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
#define maxn 1001000

int i,j,n,m;

int  len[maxn];

vector<int> p[maxn];

vector<int> q[maxn];
vector<int> qq[maxn];

LD gcd(LD a, LD b) {
  if(a>b)
    return gcd(b,a);
  if(a==0)
    return b;
  return gcd(b%a, a);
}

LD lcm(LD a, LD b) {
  return a*b/gcd(a,b);
}

int pp[45];

int num[45];


int main() {
  scanf("%d %d", &n, &m);
  int now;
  for1tr(i,n) {
    scanf("%d", &len[i]);
    for0r(j, len[i]) {
      scanf("%d", &now);
      p[i].push_back(now);
      q[now].push_back(i);
      qq[now].push_back(j);
    }
  }
  int ii;
  int last = -1;

  int b;
  int ans;
  int start;

  int k;
  for1tr(ii,m) {
    last = -2;
    now=0;
    ans=0;
    start = -1;
    mymemset(num, 0);
    for0r(i, sz(q[ii])) {
      if(q[ii][i]!=last+1) {
        start = i;
        mymemset(num, 0);
      } else {
        b=qq[ii][i];
        while(1) {
          for(k=1;k<=40;k++) {
            if(num[k]) {
              if( (pp[k] - b) % gcd(len[q[ii][i]], k)) {
                break;
              }
            }
          }
          if(k>40)
            break;
          num[len[q[ii][start]]] --;
          start ++;
        }
      }
      last = q[ii][i];
      pp[len[q[ii][i]]] = qq[ii][i];
      num[len[q[ii][i]]]++;

      if(i-start+1>ans) {
        ans=i-start+1;
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}
