#include<stdio.h>
#define maxn 201000
#define div 1000000007

typedef long long int LD;

inline LD pow(LD a,LD n) {
  LD ans = 1, now = a;
  while(n) {
    if(n&1) {
      ans *= now; ans %= div;
    }
    now *= now;
    now%=div;
    n>>=1;
  }
  return ans;
}

inline LD reverse(LD a) {
  return pow(a, div - 2);
}

struct BitTree1 {
  // to update d

  int* c;
  int n;
  BitTree1(int* cc) {
    n=0;
    c=cc;
  }
  inline int lowbit(int x) {
    return x & (-x);
  }

  void append(int x) {
    n++;
    int pos = n;
    c[pos]=n;
    int start = pos-lowbit(pos);

  }

  void modify(int pos, int x, int y) {
    // *x/y
    LD tmp;
    while (pos <= n) {
      tmp=c[pos];
      tmp =  (tmp * x) % div;
      tmp = (tmp * reverse(y)) % div;
      c[pos] = tmp;
      pos += lowbit(pos);
    }
  }
  LD sum(int end) {
    if(end>n)
      end=n;
    LD sum = 0;
    while (end) {
      sum *= c[end];
      end -= lowbit(end);
    }
    return sum;
  }
};

struct BitTree2 {
  // to update d

  int* c;
  int* sum;
  int n;
  BitTree2(int* cc, int* s, int nn) {
    n=nn;
    c=cc;
    sum=s;
  }
  inline int lowbit(int x) {
    return x & (-x);
  }

  void modify(int pos, int delta) {
    // v[pos] += delta
    LD tmp;
    int start,now=pos, lb;
    LD d=1, presum=0;
    while (pos <= n) {
      lb = lowbit(pos);
      start = pos - lb;
      while(now>start) {
        presum*=c[now];
        presum+=sum[now];
        presum %= div;
        d *= c[now];
        d%=div;
        now-=lowbit(now);
      }
      tmp=(sum[pos] - presum + div) * reverse(d) % div;
      tmp += delta + div;
      tmp = (tmp * d % div + presum) % div;
      sum[pos]=tmp;
      pos+=lb;
    }
  }

  void modifyd(int pos, int x, int y) {
    // at pos, *x/y
    LD tmp;
    int start,now=pos-1, lb;
    LD d=1, presum=0;
    while (pos <= n) {
      lb = lowbit(pos);
      start = pos - lb;
      while(now>start) {
        presum*=c[now];
        presum+=sum[now];
        presum %= div;
        d *= c[now];
        d%=div;
        now-=lowbit(now);
      }
      tmp=(sum[pos] - presum + div) * reverse(d) % div;
      tmp = tmp * x %div;
      tmp = tmp * reverse(y) % div;
      tmp = (tmp * d % div + presum) % div;
      sum[pos]=tmp;
      pos+=lb;
    }
  }

  LD cal(int end) {
    if(end>n)
      end=n;
    LD ans = 0;
    while (end) {
      ans*=c[end];
      ans += sum[end];
      ans %= div;
      end -= lowbit(end);
    }
    return ans;
  }
};

struct TreeNode {
  static int last[maxn],t;
  static int cspace[maxn], sumspace[maxn], ct, sumt;
  int ind,v,d,v0,d0,fa,sz,num;
  void add(int f,int);

  int chainfa,chainsz;
  BitTree1* bt1 = NULL;
  BitTree2* bt2 = NULL;

  inline int chainpos();

  int getPower();

  int dfs1(int cfa);
}nodes[maxn];

int TreeNode::getPower() {
  if(num == chainfa) {
    return bt2->cal(chainsz);
  }
  int cfa = chainfa;
  LD ans = nodes[cfa].bt2->cal(nodes[cfa].chainsz) -
    nodes[cfa].bt2->cal(chainpos()-1);
  ans = (ans + div) %div;
  int coe = nodes[cfa].bt1->sum(chainpos()-1);
  ans*=reverse(coe);
  ans%=div;
  return ans;
}

inline int TreeNode::chainpos(){
  return nodes[chainfa].chainsz-chainsz+1;
}

int TreeNode::dfs1(int cfa) {
  if(cfa==-1) {
    cfa=num;
  }
  chainfa = cfa;

  if(sz == 1) {
    chainsz = 1;
  } else {
    int i=ind, maxsz=0,maxsznum;
    while(i) {
      if(nodes[i].sz > maxsz) {
        maxsz = nodes[i].sz;
        maxsznum = nodes[i].num;
      }
      i=last[i];
    }
    chainsz = 1+nodes[maxsznum].dfs1(chainfa);
    i=ind;
    while(i) {
      if(nodes[i].num != maxsznum) {
        nodes[i].dfs1(-1);
      }
      i=last[i];
    }
  }
  if(num == chainfa) {
    bt1 = new BitTree1(&cspace[ct-1], chainsz);
    bt2 = new BitTree2(&cspace[ct-1], &sumspace[sumt-1], chainsz);
    ct+=chainsz;
    sumt+=chainsz;
  }
  return chainsz;
}

void TreeNode::add(int f,int vv) {
  v0=vv;
  t++;
  num=t;
  fa=f;
  TreeNode& fnode = nodes[fa];
  last[t]=fnode.ind;
  fnode.ind=t;
}

int TreeNode::last[maxn];
int TreeNode::cspace[maxn];
int TreeNode::sumspace[maxn];
int TreeNode::t, TreeNode::ct=1, TreeNode::sumt=1;
int D[maxn];

int qry[maxn][2],qn;

void addWeight(int a, int w) {
  if(a<1)
    return;
  int cfa = nodes[a].chainfa;
  int oldfav = nodes[cfa].getPower(), newfav;

  nodes[cfa].bt2->modify(nodes[a].chainpos(), w);
  newfav = nodes[cfa].getPower();
  newfav -= oldfav;
  if(newfav < 0) newfav += div;

  if(nodes[cfa].fa) {
    addWeight(nodes[cfa].fa, newfav);
  }
}

void addDegree(int a) {
  nodes[a].d++;
  int cfa = nodes[a].chainfa;
}

void addNode(int a) {
  nodes[a].d=1;

}

int main() {
  int v,i,a,b,c;
  scanf("%d %d",&v, &qn);
  nodes[1].v0=v;
  TreeNode::t=1;
  for(i=1;i<=qn;i++) {
    scanf("%d", &a);
    if(a==1) {
      scanf("%d %d",&b,&c);
      qry[i][0]=a;
      qry[i][1]=TreeNode::t+1;
      nodes[TreeNode::t+1].add(b,c);
    } else {
      scanf("%d", &b);
      qry[i][0]=a;
      qry[i][1]=b;
    }
  }
  for(i=TreeNode::t;i;i--) {
    nodes[i].sz++;
    nodes[nodes[i].fa].sz += nodes[i].sz;
  }
  return 0;
}
