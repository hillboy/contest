#include<stdio.h>
#include<algorithm>
#include<set>
#include<vector>
using namespace std;
#define maxn 100010
typedef double LD;

vector<int> np[maxn];

int i,j,n,m;

int ind[maxn];
int e[maxn*2], last[maxn*2],t;

int de[maxn];

LD sum[maxn];
int num[maxn];

void adde(int a,int b) {
  t++;
  last[t]=ind[a];
  e[t]=b;
  ind[a]=t;
}

int q[maxn][2];

bool complicated[maxn];


void dfs(int a,int fa) {
  int ii,i;
  num[a]=1;
  for(ii=ind[a];ii;ii=last[ii]) {
    i=e[ii];
    if(i==fa) continue;
    de[i]=de[a]+1;
    dfs(i,a);
    num[a]+=num[i];
    sum[a]+=sum[i]+num[i];
  }
}

// lca stuff
namespace {
  int qt2;

  int que2[maxn*2];
  int rmq[maxn*2][32];

  int num2[maxn], pos2[maxn], nt2, num2_to_a[maxn];
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
  void dfs3(int a, int last) {
    int i;
    num2[a] = nt2;
    num2_to_a[nt2]=a;
    nt2++;
    qt2++;
    que2[qt2]=num2[a];
    pos2[a]=qt2;
    for(i=ind[a]; i; i = ::last[i]) {
      if(e[i] != last) {
        dfs3(e[i], a);
        qt2++;
        que2[qt2]=num2[a];
      }
    }
  }
}
vector<int> pleasesolve[maxn];
set<int> p;
LD anssum[maxn];
int ansnum[maxn];
int tmp;
void dfs2(int a,int fa, int fanum, LD fasum) {
  int ii,i;
  for(ii=0;ii<(int)np[a].size();ii++) {
    i=np[a][ii];
    if(p.find(i)!=p.end()) {
        tmp=q[i][0]+q[i][1]-a;
        pleasesolve[tmp].push_back(i);
        anssum[i]=sum[a];
        ansnum[i]=num[a];
        p.erase(i);
    } else {
      p.insert(i);
    }
  }
  for(ii=ind[a];ii;ii=last[ii]) {
    i=e[ii];
    if(i==fa) continue;
    LD newnum=fanum+num[a]-num[i];
    LD newsum=newnum+fasum+sum[a]-num[i]-sum[i];
    dfs2(i, a, fanum+num[a]-num[i], newsum);
    if(pleasesolve[a].size()>0) {
      int j,jj;
      for(j=0;j<(int)pleasesolve[a].size();j++) {
        jj=pleasesolve[a][j];
        LD s = anssum[jj]*(fanum+num[a]-num[i]) + (fasum+sum[a]-num[i]-sum[i]) * ansnum[jj];
        LD n = ansnum[jj];
        n*=(fanum+num[a]-num[i]);
        anssum[jj]=s/n;
        ansnum[jj]=n;
        complicated[jj]=true;
      }
      pleasesolve[a].clear();
    }
  }
}

inline void make() {
  rmq_init();
  for(i=1;i<=m;i++) {
    if(complicated[i]) {
      printf("%.10lf\n", anssum[i]+abs(de[q[i][0]]-de[q[i][1]])+1);
    } else {
      int a,b,fa;
      a=q[i][0];
      b=q[i][1];
      fa=lca(a,b);
      LD s = sum[q[i][0]]*num[q[i][1]] + sum[q[i][1]]*num[q[i][0]];
      LD n = num[q[i][0]];
      n *= num[q[i][1]];
      printf("%.10lf\n", s/n+1+de[a]+de[b]-de[fa]*2);
    }
  }
}

int main() {
  scanf("%d %d", &n, &m);
  int a,b;
  for(i=1;i<n;i++) {
    scanf("%d %d", &a, &b);
    adde(a,b);
    adde(b,a);
  }
  for(i=1;i<=m;i++) {
    scanf("%d %d", &a, &b);
    q[i][0]=a;
    q[i][1]=b;
    np[a].push_back(i);
    np[b].push_back(i);
  }
  dfs3(1,0);
  dfs(1,0);
  dfs2(1,0,0,0);
  make();
  for(i=1;i<=n;i++) {
  }
  for(i=1;i<=m;i++) {
  }
  return 0;
}
