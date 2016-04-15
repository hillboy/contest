#include<stdio.h>
#include<algorithm>
#include<map>
using namespace std;

int i,j,n,m;

char s[100000];


char ss[10000], sss[10000];

int nowwords;
string words[100100];

int ans[10010];

struct treenode {
  char a;
  map<char, int> c;
  bool end;
  int endword;
  int fa;
  int edge;
} p[1100000];
int t;

bool add(int a, int now) {
  if(! (ss[now])) {
    return true;
  }
  if (p[a].c.count(ss[now]) == 0) {
    t++;
    p[a].c[ss[now]] = t;
    p[t].a=ss[now];
    p[t].fa=a;
  }
  int tmp;
  if(p[a].c.count(ss[now])) {
    tmp = p[a].c[ss[now]];
    if(add(tmp, now+1)) {
      p[tmp].end = true;
      p[tmp].endword=nowwords;
    }
  }
  return false;
}

int que[1000100], qt;

void bfs() {
  que[1]=1;
  qt=1;
  i=1;
  map<char, int> ::iterator ii;
  while(i<=qt) {
    ii=p[que[i]].c.begin();
    while(ii!=p[que[i]].c.end()) {
      qt++;
      que[qt]=ii->second;
      ++ii;
    }
    i++;
  }
}

void buildedge() {
  int fa, faedge;
  for(int ii = 2;ii<=qt;ii++) {
    i=que[ii];
    fa=p[i].fa;
    if(fa==1) {
      p[i].edge = 1;
      continue;
    }
    faedge = p[fa].edge;
    while(faedge != 1 && p[faedge].c.count(p[i].a) ==0) {
      faedge = p[faedge].edge;
    }
    if (p[faedge].c.count(p[i].a)) {
      p[i].edge = p[faedge].c[p[i].a];
    } else {
      p[i].edge = 1;
    }
  }
}

void make() {
  int ii,k;
  i=1;
  for(ii=0;s[ii];ii++) {
    while(i!=1 && p[i].c.count(s[ii]) ==0) {
      i=p[i].edge;
    }
    if(p[i].c.count(s[ii])) {
      i=p[i].c[s[ii]];
      j=i;
      while (j!=1) {
        if(p[j].end) {
          k=ii-words[p[j].endword].size();
          if(k<0 || ans[k]) {
            ans[ii]=p[j].endword;
            break;
          }
        }
        j=p[j].edge;
      }
    } else {
      // should never happen
    }
  }
}

void output(int a) {
  int i = ans[a];
  if(a < (int)words[i].size() ) {
    printf("%s ", words[i].c_str());
    return;
  }
  output(a-words[i].size());
  printf("%s ", words[i].c_str());
}

int main() {
  scanf("%d", &n);
  scanf("%s", s);
  scanf("%d", &m);
  t=1;
  for(i=1;i<=m;i++) {
    scanf(" %s", sss);
    nowwords=i;
    words[i]=sss;
    for(j=0;sss[j];j++) {
      ss[j]=sss[words[i].size() - j-1];
    }
    ss[j]=0;
    for(j=0;ss[j];j++) {
      if(ss[j]>='A' && ss[j] <= 'Z')
        ss[j] += 'a'-'A';
    }
    add(1, 0);
  }
  p[1].edge = 1;
  bfs();
  buildedge();
  make();
  output(n-1);
  return 0;
}
