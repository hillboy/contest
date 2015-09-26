#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;

#define maxn 100010

int i,j,n,m;

struct cmp {
  int* min_;
  cmp(int* m) {
    min_ = m;
  }
  bool operator() (int i, int j) {
    return min_[i] < min_[j];
  }
};

struct Tree {
  int fa[maxn][20];
  int last[maxn], e[maxn],ind[maxn];
  int min_[maxn], rank[maxn];
  int buffer[maxn];
  int root;
  void adde(int a, int b) {
    static int t = 0;
    fa[b][0]=a;
    t++;
    last[t]=ind[a];
    ind[a]=t;
    e[t]=b;
  }
  void get_min(int a) {
    int i;
    min_[a] = a;
    for(i=ind[a]; i; i=last[i]) {
      get_min(e[i]);
      if(min_[e[i]] < min_[a]) {
        min_[a] = min_[e[i]];
      }
    }
  }
  void sort_node(int a) {
    static int t = 0, k = 0;
    static cmp cmper = cmp(&min_[0]);
    int i;
    int buffer_start = t+1, buffer_end;
    for(i=ind[a];i;i=last[i]) {
      t++;
      buffer[t]=e[i];
    }
    buffer_end = t;
    if(buffer_start <= buffer_end) {
      sort(&buffer[buffer_start], &buffer[buffer_end + 1], cmper);
    }
    for(i=buffer_start;i<=buffer_end;i++) {
      sort_node(buffer[i]);
    }
    k--;
    rank[a] = k;
  }
  void makefa() {
    int i, j;
    for(j=1;j<20;j++) {
      for(i=1;i<=n;i++) {
        fa[i][j] = fa[fa[i][j-1]][j-1];
      }
    }
  }

}T;

struct Machine {
  Tree& tree;
  pair<int, int> p[maxn];
  int t;
  bool checked[maxn];
  Machine(Tree& T) : tree (T){
    int i,a;
    scanf("%d %d", &n, &m);
    for(i=1;i<=n;i++) {
      scanf("%d", &a);
      if(a==0)
        tree.root = i;
      else
        tree.adde(a, i);
    }
    tree.get_min(tree.root);
    tree.sort_node(tree.root);
    tree.makefa();
    for(i=1;i<=n;i++) {
      p[t] = make_pair(tree.rank[i], i);
      t++;
      push_heap(p, p + t);
    }
  }
  int add_ball() {
    int ans = p[0].second;
    checked[p[0].second] = 1;
    pop_heap(p, p+t);
    t--;
    return ans;
  }
  int remove(int a) {
    int i, ans = 0;
    while(checked[tree.fa[a][0]]) {
      i=0;
      while(checked[tree.fa[a][i]])
        i++;
      i--;
      ans += (1<<i);
      a=tree.fa[a][i];
    }
    p[t] = make_pair(tree.rank[a], a);
    t++;
    push_heap(p, p+t);
    checked[a]=false;
    return ans;
  }
  void make() {
    int a,b;
    while(m--) {
      scanf("%d %d", &a, &b);
      if (a==1) {
        while(b--) {
          a=add_ball();
        }
        printf("%d\n", a);
      } else {
        printf("%d\n", remove(b));
      }
    }
  }
};


int main() {
//  freopen("a.txt", "r", stdin);
  Machine* M = new Machine(T);
  M->make();
  return 0;
}
