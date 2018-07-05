#include<stdio.h>
#include<string.h>
#include<set>
#include<vector>
#include<algorithm>
using namespace std;
#define maxn 200010

int p[maxn*20];

std::set<int> q[62];

int i,j,n,m;

char s[maxn];

int charint(char a) {
  if (a>='a' && a<='z')
    return a-'a';
  if (a>='A' && a<='Z')
    return a-'A' + 26;
  return a-'0' + 52;
}
char intchar(int a) {
  if(a<26)
    return a+'a';
  if(a<52)
    return a-26+'A';
  return a-52+'0';
}

void init(int a,int l, int r) {
  if(l==r) {
    p[a]=1;
    return;
  }
  p[a]=r-l+1;
  int mid=(l+r)/2;
  init(a*2, l, mid);
  init(a*2+1, mid+1, r);
}

void change(int a, int l, int r, int now) {
  p[a]--;
  if (l==r)
    return;
  int mid=(l+r)/2;
  if(now<=mid)
    change(a*2, l, mid, now);
  else
    change(a*2+1, mid+1, r,now);
}

int lookup(int a, int l, int r, int now) {
  if(l==r)
    return l;
  int mid = (l+r)/2;
  if(p[a*2]>=now)
    return lookup(a*2, l, mid, now);
  else
    return lookup(a*2+1, mid+1, r, now-p[a*2]);
}

int main() {
  scanf("%d %d", &n, &m);
  scanf("%s", &s[1]);
  for(i=1;i<=n;i++) {
    s[i] = charint(s[i]);
    q[int(s[i])].insert(i);
  }
  init(1, 1, n);

  int l,r,now;
  char a;

  while(m--) {
    scanf("%d %d %c", &l, &r, &a);
    now=charint(a);
    l=lookup(1, 1,n, l);
    r=lookup(1, 1,n,r);
    while(true) {
      auto ii=q[now].lower_bound(l);
      if (ii==q[now].end())
        break;
      if( (*ii) <=r) {
        change(1, 1, n, *ii);
        q[now].erase(ii);
      } else {
        break;
      }
    }
  }
  vector<pair<int, char>> ans;
  for(i=0;i<62;i++) {
    for (auto ii = q[i].begin(); ii!=q[i].end();ii++) {
      ans.push_back(make_pair(*ii, intchar(i)));
    }
  }
  sort(ans.begin(), ans.end());
  for(const auto& ii : ans) {
    printf("%c", ii.second);
  }
  printf("\n");
  return 0;
}
