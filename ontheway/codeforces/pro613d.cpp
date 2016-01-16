#include<stdio.h>
#include<algorithm>
using namespace std;
#define maxn 101000

int i,j,n,m;

struct Tree {
  int ind[maxn];
  int e[maxn*2], lasti[maxn*2], t;
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
        rmq[i][j] = min(rmq[i][j-1], rmq[i+gap][j-1]);
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
  test1();
  return 0;
}
