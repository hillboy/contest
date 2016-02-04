#include<stdio.h>
#include<algorithm>
#include<map>
#include<set>
using namespace std;
#define maxn 201000

int i,j,n,m;


struct Tree {
  int ind[maxn];
  int e[maxn*2], lasti[maxn*2], t;
  int di[maxn];
  int que1[maxn*2], qt1;


  int que2[maxn*2], qt2;
  int num2[maxn], pos2[maxn], nt2, num2_to_a[maxn];

  void addE(int a,int b) {
    t++;
    e[t]=b;
    lasti[t]=ind[a];
    ind[a]=t;
  }

  void dfs1(int a, int last) {
    int i;
    bool leaf = true;
    qt1++;
    que1[qt1]=a;
    di[a]=di[last]+1;
    for(i=ind[a]; i; i=lasti[i]) {
      if(e[i] != last) {
        leaf = false;
        dfs1(e[i], a);
      }
    }
    if(!leaf) {
      que1[qt1]=a;
    }
  }

  void dfs2(int a, int last) {
    int i;
    num2[a] = nt2;
    num2_to_a[nt2]=a;
    nt2++;
    qt2++;
    que2[qt2]=num2[a];
    pos2[a]=qt2;
    for(i=ind[a]; i; i =lasti[i]) {
      if(e[i] != last) {
        dfs2(e[i], a);
        qt2++;
        que2[qt2]=num2[a];
      }
    }
  }

  int rmq[maxn][32];

  // 1 to qt2
  void rmq_init() {
    int i,j=1,gap=1;
    for(i=1;i<=qt2;i++) {
      rmq[i][0]=que2[i];
    }
    while(gap<qt2) {
      for(i=1;i<=qt2;i++) {
        if(i+gap<=qt2)
          rmq[i][j] = min(rmq[i][j-1], rmq[i+gap][j-1]);
        else 
          rmq[i][j]=rmq[i][j-1];
      }
      j++;
      gap+=gap;
    }
  }

  int rmq_query(int a,int b) {
    if(a>b) {
      swap(a,b);
    }
    int i = 1, j = 0;
    while(i<=b-a+1) {
      i+=i;
      j++;
    }
    j--;
    i/=2;
    return min(rmq[a][j], rmq[b-i+1][j]);
  }

  int lca(int a, int b) {
    if(a==b)
      return a;
    int ans = rmq_query(pos2[a], pos2[b]);
    return num2_to_a[ans];
  }
} tree;

void test1() {
  for(i=0;i<=tree.qt2;i++) {
    printf("%d\n", tree.que2[i]);
  }
  for(i=1;i<=4;i++) {
    for(j=1;j<=4;j++) {
      printf("(%d %d): %d\n", i, j , tree.lca(i,j));
    }
  }
}

int query[maxn], k;

map<int, int> q;

struct HP {
  int lca;
  int pos1, pos2;
} hp[maxn*2];

bool cmp(HP& a, HP& b) {
  return tree.di[a.lca] < tree.di[b.lca];
}

int hpt;

set<int> removed;

void rm(int pos) {
  map<int,int>::iterator ii,left,right;
  ii=q.find(pos);
  if(ii==q.begin()) {
    q.erase(ii);
    return;
  }
  left=ii;
  left--;
  right = ii;
  right ++;
  if(right==q.end()) {
    q.erase(ii);
    return;
  }
  hp[hpt].pos1 = left->first;
  hp[hpt].pos2=right->first;
  hp[hpt].lca = tree.lca(left->second, right->second);
  hpt++;
  push_heap(hp, hp+hpt, cmp);
  q.erase(ii);
}

void make() {
  removed.clear();
  hpt=0;
  map<int,int>::iterator ii,jj;
  jj=ii=q.begin();
  ii++;
  while(ii!=q.end()) {
    hp[hpt].pos1 = ii->first;
    hp[hpt].pos2=jj->first;
    hp[hpt].lca = tree.lca(ii->second, jj->second);
    hpt++;
    push_heap(hp, hp+hpt, cmp);
    jj=ii;
    ii++;
  }
  int ans = 0;
  int pos1, pos2;
  map<int,int>::iterator i1, i2;
  while(q.size() > 1) {
    i1=q.find(hp[0].pos1);
    i2=q.find(hp[0].pos2);
    if( i1== q.end() && i2 == q.end() ) {
      pop_heap(hp, hp+hpt,cmp);
      hpt--;

      continue;
    }
    if(i1== q.end()) {
      int lca = hp[0].lca;
      pop_heap(hp, hp+hpt,cmp);
      hpt--;
      if(removed.find(lca) != removed.end()) {
        rm(i2->first);
      }
      continue;
    }
    if(i2== q.end()) {
      int lca = hp[0].lca;
      pop_heap(hp, hp+hpt,cmp);
      hpt--;
      if(removed.find(lca) != removed.end()) {
        rm(i1->first);
      }
      continue;
    }
    int lca = hp[0].lca;
    pos1=hp[0].pos1;
    pos2=hp[0].pos2;
    pop_heap(hp, hp+hpt, cmp);
    hpt--;
    if(q.find(tree.pos2[lca]) != q.end()) {
      if(tree.di[i1->second] - tree.di[lca] ==1 ||
          tree.di[i2->second] - tree.di[lca] ==1) {
        printf("-1\n");
        return;
      }
      if(i1->second != lca && i2->second !=lca) {
        rm(pos1);
        rm(pos2);
        ans+=2;
      } else {
        if(i1->second == lca) {
          rm(pos2);
        } else {
          rm(pos1);
        }
        ans++;
      }
    } else {
      if(removed.find(lca) == removed.end()) {
        ans++;
        removed.insert(lca);
      }
      rm(pos1);
      rm(pos2);
    }
  }
  printf("%d\n", ans);
}

int main() {
  scanf("%d", &n);
  int a,b;
  for(i=1;i<n;i++) {
    scanf("%d %d", &a, &b);
    tree.addE(a,b);
    tree.addE(b,a);
  }
  tree.dfs1(1,0);
  tree.dfs2(1,0);
  tree.rmq_init();

  scanf("%d", &a);
  while(a--) {
    scanf("%d", &b);
    q.clear();
    for(i=0;i<b;i++) {
      scanf("%d", &j);
      q[tree.pos2[j]]=j;
    }
    if(q.size() == 1) {
      printf("0\n");
      continue;
    }
    make();
  }
  return 0;
}
