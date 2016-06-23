#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;

#define maxn 300000

#define forlr(x,l,r) for(x=l;x<(int)r;++x)
#define for1(x,y) forlr(x,0,y)
#define forn(x) for1(x,n)

struct Tree{
  int fa;
  bool heavy;
  int sum, max_son;
  int ans;
  int num;
  vector<int> son;
  void dfs1();
  void dfs2(vector<int>& chain, vector<int>& chaini);
  vector<int> ch;
  vector<int> chi;
} p[maxn+10];

void Tree::dfs1() {
  int i;
  sum=1;
  int heavyi=-1, heavysize=-1;
  forlr(i,0,son.size()) {
    p[son[i]].dfs1();
    sum+=p[son[i]].sum;
    if(p[son[i]].sum>heavysize) {
      heavysize = p[son[i]].sum;
      heavyi = i;
    }
  }
  if(heavyi>=0) {
    max_son = heavyi;
    p[son[heavyi]].heavy = true;
  }
}

void Tree::dfs2(vector<int>& chain, vector<int>& chaini) {
  int i;
  forlr(i, 0, son.size()) {
    if(i!=max_son) {
      p[son[i]].dfs2(p[son[i]].ch, p[son[i]].chi);
    } else {
      p[son[i]].dfs2(chain, chaini);
    }
  }
  if(sum==1 || p[son[max_son]].sum <= sum/2) {
    ans=num;
  } else {
    int ind = std::lower_bound(chain.begin(), chain.end(), sum/2)- chain.begin();
    if(p[chaini[ind]].sum==sum/2) {
      ans=p[chaini[ind]].fa;
    } else {
      ans=p[chaini[ind]].num;
    }
  }
  chain.push_back(sum);
  chaini.push_back(num);
}

int i,j,n,m;

int main() {
  scanf("%d %d", &n, &m);
  forlr(i,2,n+1) {
    scanf("%d", &j);
    p[i].fa=j;
    p[j].son.push_back(i);
    p[i].num=i;
  }
  p[1].num=1;
  p[1].dfs1();
  p[1].dfs2(p[1].ch, p[1].chi);
  while(m--) {
    scanf("%d", &i);
    printf("%d\n", p[i].ans);
  }
  return 0;
}
