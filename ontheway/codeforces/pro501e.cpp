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
#define maxn 100010

int i,j,n,m,left, right;;

int p[maxn];

int sum[maxn], odd;

int nowsum[maxn];

void make() {
  LD ans = left;
  ans *= n-right+1;
  i=left;
  int mid = n/2 + n%2;
  while(i<right-1) {
    if(i<=n/2) {
      nowsum[p[i]]++;
      if(nowsum[p[i]]>sum[p[i]]/2) {
        break;
      }
    } else {
      if(p[i]==p[1+n - i]) {
        if(i==mid && n%2==1 && p[i] !=odd) {
          break;
        }
      } else {
        break;
      }
    }
    ans+=n-right+1;
    i++;
  }
  j=right;
  mymemset(nowsum, 0);
  while(j>left+1) {
    if(j>mid) {
      nowsum[p[j]]++;
      if(nowsum[p[j]] > sum[p[j]]/2) {
        break;
      }
    } else {
      if(p[j]!=p[1+n-j])
        break;
      else {
        if(j==mid && n%2==1 && p[j] !=odd) {
          break;
        }
      }
    }
    j--;
    ans+=left;
  }
  printf("%lld\n", ans);
}

int main() {
  scanf("%d", &n);
  for1tr(i,n) {
    scanf("%d", &p[i]);
    sum[p[i]]++;
  }
  i=1;j=n;
  while(i<j) {
    if (p[i]==p[j]) {
      sum[p[i]]-=2;
      i++,j--;
    }
    else
      break;
  }
  if(i>=j) {
    LD ans = n+1;
    ans*=n;
    ans/=2;
    printf("%lld\n", ans);
    return 0;
  }
  left = i;
  right = j;
  j=0;
  for1tr(i,n) {
    if(sum[i] & 1) {
      odd = i;
      j++;
    }
  }
  if(j>1 || (j==1 && n%2==0)) {
    printf("0\n");
    return 0;
  }
  make();
  return 0;
}
