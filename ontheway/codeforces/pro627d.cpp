#include<stdio.h>
#include<algorithm>
#include<string.h>
using namespace std;

#define maxn 201000

int p[maxn];

bool banned[maxn];

bool checked[maxn], checking[maxn];

int i,j,n,m;

bool pure[maxn];

int subtree_size[maxn];

int subtree_ans[maxn];

int ans;

struct Tree {
  int ind[maxn], e[maxn*2], last[maxn*2],t;
  void adde(int a,int b) {
    t++;
    e[t]=b;
    last[t]=ind[a];
    ind[a]=t;
  }

  void dfs1(int a,int fa) {
    int i,ii;
    pure[a]=true;
    subtree_size[a]=1;
    subtree_ans[a]=0;
    checking[a]=true;
    int max_not_pure = 0, sum_pure=0;
    for(ii=ind[a];ii;ii=last[ii]) {
      i=e[ii];
      if (i==fa)
        continue;
      if(banned[i]) {
        pure[a]=false;
        continue;
      }
      dfs1(i, a);
      if(!pure[i]) {
        pure[a]=false;
        max_not_pure = max(max_not_pure, subtree_ans[i]);
      } else {
        sum_pure += subtree_size[i];
      }
      subtree_size[a]+=subtree_size[i];
    }
    if(!pure[a]) {
      subtree_ans[a] = sum_pure + max_not_pure + 1;
    } else {
      subtree_ans[a] = subtree_size[a];
    }
  }

  void dfs2(int a,int fa, int faans, int fasize, bool fa_pure) {
    checked[a]=true;
    int nowans=subtree_ans[a];
    int ii,i;
    int max1 = 0, max1_i = 0, max2 = 0, max2_i=0,
        sum_pure=0, banned_children=0, banned_child = 0;
    if(fa_pure) {
      sum_pure += fasize;
    } else {
      max1=faans;
    }
    for(ii=ind[a];ii;ii=last[ii]) {
      i=e[ii];
      if(i==fa)
        continue;
      if(banned[i]) {
        fa_pure=false;
        continue;
      }
      if(pure[i]) {
        sum_pure+=subtree_size[i];
      } else {
        banned_children++;
        banned_child = i;
        if(subtree_ans[i] > max2) {
          max2_i=i;
          max2=subtree_ans[i];
        }
        if(max2>max1) {
          swap(max2,max1);swap(max2_i, max1_i);
        }
      }
    }

    if(banned_children > 1)
      fa_pure = false;

    nowans = sum_pure + max1 + 1;
    if(nowans>ans)
      ans=nowans;
    for(ii=ind[a];ii;ii=last[ii]) {
      i=e[ii];
      if(i==fa)
        continue;
      if(banned[i]) {
        continue;
      }
      if (pure[i]) {
        if(fa_pure) {
          if(banned_child) {
            dfs2(i, a, nowans - subtree_size[i], 0, false);
          } else {
            dfs2(i, a, nowans - subtree_size[i], sum_pure - subtree_size[i]+1, true);
          }
        } else {
          dfs2(i, a, nowans - subtree_size[i], 0, false);
        }
      } else {
        if (!fa_pure || (banned_child && i!=banned_child)) {
          if (i==max1_i) {
            dfs2(i, a, nowans - max1 + max2, 0, false);
          } else {
            dfs2(i, a, nowans, 0, false);
          }
        } else {
          if (i==max1_i) {
            dfs2(i, a, nowans - max1 + max2, sum_pure+1, true);
          } else {
            dfs2(i, a, nowans, sum_pure+1, true);
          }
        }
      }
    }
  }
}tree;


bool work() {
  memset(checked, 0, sizeof(checked));
  memset(checking, 0, sizeof(checking));
  int i;
  for(i=1;i<=n;i++) if(!banned[i] && !checking[i]) {
    tree.dfs1(i, 0);
  }
  ans=0;
  for(i=1;i<=n;i++) if(!banned[i] && !checked[i]) {
    tree.dfs2(i, 0, 0, 0, true);
  }
  return ans>=m;
}

void make() {
  int l=1, r=1000001, mid;
  int i;
  while(l<=r) {
    mid=(l+r)/2;
    for(i=1;i<=n;i++) {
      if(p[i]>=mid) {
        banned[i]=false;
      } else {
        banned[i]=true;
      }
    }
    if(work()) {
      l=mid+1;
    } else {
      r=mid-1;
    }
  }
  printf("%d\n", r);
}


int main() {
  scanf("%d %d", &n, &m);
  for(i=1;i<=n;i++) {
    scanf("%d", &p[i]);
  }
  int a,b;
  for(i=1;i<n;i++) {
    scanf("%d %d", &a,&b);
    tree.adde(a,b);
    tree.adde(b,a);
  }
  make();
  return 0;
}
