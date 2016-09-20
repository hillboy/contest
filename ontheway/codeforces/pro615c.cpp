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

int i,j,n,m;

#define maxn 200010

int start, ed, delta;

struct TrieNode {
  TrieNode* child[26];
  int start, ed;
  static TrieNode* newNode() {
    TrieNode* a = new TrieNode();
    int i;
    for0r(i, 26)
      a->child[i] = nullptr;
    a->start = ::start;
    a->ed = :: ed;
    return a;
  }
  void add(char* s) {
    if (!(*s)) {
      return;
    }
    ::ed += delta;
    int a = (*s) - 'a';
    if(child[a] == nullptr) {
      child[a] = newNode();
    }
    child[a]->add(s+1);
  }
} root;

char s[maxn], ss[maxn], sss[maxn];

int main() {
  scanf("%s %s", s, ss);
  for(i=0;s[i];i++) {
    start = i+1;
    delta = 1;
    ed = start - delta;
    root.add(&s[i]);
  }
  n = i;
  for0r(i, n) {
    sss[i] = s[n-i-1];
  }
  for0r(i, n) {
    start = n-i;
    delta = -1;
    ed = start - delta;
    root.add(&sss[i]);
  }
  int ans = 0;
  i = 0;
  while(ss[i]) {
    j = i;
    TrieNode* now = &root;
    while(now) {
      now = now->child[ss[j]-'a'];
      if(now) {
        j++;
      }
    }
    if(j==i)
      break;
    ans++;
    i=j;
  }
  if(ss[i]) {
    printf("-1\n");
    return 0;
  }

  printf("%d\n", ans);
  i = 0;
  while(ss[i]) {
    j = i;
    TrieNode* now = &root, *pre;
    while(now) {
      pre = now;
      now = now->child[ss[j]-'a'];
      if(now) {
        j++;
      }
    }
    printf("%d %d\n", pre->start, pre->ed);
    i=j;
  }
  return 0;
}
