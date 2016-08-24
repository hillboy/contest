#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include <map>
#include <string>
#include <math.h>
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

#define maxn 1000000

char s[maxn];

int main() {
  scanf("%s", s);
  int i = 0, j;
  char last=0;
  if (s[0]!='a') {
    while(s[i] && s[i]!='a') {
      last = s[i]-1;
      printf("%c", last);
      i++;
    }
    if(s[i])
      printf("%s\n", &s[i]);
  } else {
    while(s[i] && s[i]=='a') {
      i++;
    }
    if(s[i]) {
      j=0;
      while(j<i) {
        printf("%c", 'a');
        j++;
      }
      while(s[i] && s[i]!='a') {
        last = s[i]-1;
        printf("%c", last);
        i++;
      }
      if(s[i])
        printf("%s", &s[i]);
    } else {
      j=0;
      while(j<i-1) {
        printf("%c", 'a');
        j++;
      }
      printf("%c", 'z');
    }
  }
  return 0;
}
