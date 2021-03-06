#include<stdio.h>
#include<algorithm>
#include<vector>
#include<string.h>
using namespace std;
#define maxint 1000000001

typedef long long int LD;

long long int p[1111][33][33][2];

int i,j,n,m,P;

long long int cost[1111][31];

vector<int> edge[1111];

const int N = 2500;
const int INF =2000000000;
bool vst[N] ; 
int up=N;
class Edge {
 public:
  int u, v, cuv, cvu, flow, cost;
  Edge(int cu, int cv, int ccu, int ccv, int cc) 
      : u(cu), v(cv), cuv(ccu), cvu(ccv), flow(0), cost(cc) {}
  int other(int p) const { return p == u ? v : u; }
  int cap(int p) const { return p == u ? cuv-flow : cvu+flow; }
  int ecost(int) const;
  void addFlow(int p, int f) { flow += (p == u ? f : -f); }
};
int Edge::ecost(int p) const {
  if(flow == 0) return cost;
  else if(flow > 0) return p == u ? cost : -cost;
  else return p == u ? -cost : cost;
}

class Network {
 public:
  vector<Edge> eg;
  vector<Edge*> net[N];
  Edge *prev[N];
  int v, s, t;
  int flow, cost, phi[N], dis[N], pre[N];
  void initNet();
  void initFlow();
  bool dijkstra();
  bool Bellman();
 public:
  int getCost() const { return cost; }
  int getFlow() const { return flow; }
  int mincost(int, int);

}minflow;
void Network::initNet() {
  int i;
  for(i = 0; i < v; i++) net[i].clear();
  for(i = eg.size()-1; i >= 0; i--) {
    net[eg[i].u].push_back(&eg[i]);
    net[eg[i].v].push_back(&eg[i]);
  }
}

void Network::initFlow() {
  flow = cost = 0;
  memset(phi, 0, sizeof(int)*up);
  initNet();
}

bool Network::dijkstra() {
  int i;
  for(i = 0; i < v; i++) dis[i] = INF;
  dis[s] = 0; prev[s] = NULL; pre[s] = -1;

  memset(vst,0,sizeof(bool)*up);
  for(i = 1; i < v; i++) {
    int md = INF, u,j;
    for(j = 0; j < v; j++)
      if(!vst[j] && md > dis[j]) { md = dis[j]; u = j; }
    if(md == INF) break;
    vst[u] = true;
    for(j = net[u].size()-1; j >= 0; j--) {
      Edge *ce = net[u][j];
      if(ce->cap(u) > 0) {
        int p = ce->other(u), cw = ce->ecost(u)-phi[u]+phi[p];
        if(dis[p] > dis[u]+cw) { dis[p] = dis[u]+cw; prev[p] = ce; pre[p] = u; }
      }
    }
  }
  return (dis[t] != INF);
}


bool Network::Bellman() {
  int i,j;
  for(i = 0; i < v; i++) dis[i] = INF;
  dis[s] = 0; prev[s] = NULL; pre[s] = -1;
  bool o;
  for(i = 1; i < v; i++) {
    o=1;
    for(j=0;j<(int)eg.size();j++)if(dis[eg[j].u]<INF)if(dis[eg[j].u]+eg[j].cost<dis[eg[j].v])
      dis[eg[j].v]=dis[eg[j].u]+eg[j].cost,o=0;
    if(o)break;
  }
  for(i = 0; i < v; i++) phi[i] -= dis[i];
  return (dis[t] != INF);
}

int Network::mincost(int ss, int tt) {
  s = ss; t = tt; initFlow();
  //Add it if needed.
  // Bellman();
  int c;
  while(dijkstra()) {
    int ex = INF;
    //for(c = t; c != s; c = pre[c]) ex <?= prev[c]->cap(pre[c]);
    for(c = t; c != s; c = pre[c]) ex = (ex<prev[c]->cap(pre[c])?ex:prev[c]->cap(pre[c]));
    for(c = t; c != s; c = pre[c]) prev[c]->addFlow(pre[c], ex);
    flow += ex; cost += ex*(dis[t]-phi[t]);
    for(int i = 0; i < v; i++) phi[i] -= dis[i];
  }
  return cost;
}


struct G {
  int n,m;
  LD cost[1111][33];
  void init() {
    n=m=0;
  }
  LD solve() {
    if(n>m) {
      return maxint;
    }
    minflow.v = n+m+2;
    minflow.eg.clear();
    int i,j;
    for(i=0;i<n;i++) {
      minflow.eg.push_back(Edge(0,i+1,1,0,0));
    }
    for(i=0;i<m;i++) {
      minflow.eg.push_back(Edge(n+i+1,n+m+1,1,0,0));
    }
    for(i=0;i<n;i++)
      for(j=0;j<m;j++) {
        if(cost[i][j]<maxint)
          minflow.eg.push_back(Edge(i+1,n+j+1,1,0,cost[i][j]));
      }

    LD ans = minflow.mincost(0,minflow.v-1);
    if (minflow.flow != n) {
      return maxint;
    } else {
      return ans;
    }
  }

}gg;

void make(int a, int nowcolor, int bancolor) {
  p[a][nowcolor][bancolor][0]= p[a][nowcolor][bancolor][1] = cost[a][nowcolor];
  p[a][nowcolor][bancolor][1] += P;
  int i,j,r,c;
  gg.init();
  gg.m=m;
  for(i=0;i<(int)edge[a].size();i++) {
    c=edge[a][i];
    LD ans=maxint;
    gg.n++;
    for(j=1;j<=m;j++) if(j!=bancolor) {
      gg.cost[gg.n-1][j-1]=maxint;
      LD& temp = gg.cost[gg.n-1][j-1];
      for(r=1;r<=m;r++) {
        ans = min(ans, p[c][j][r][1]);
        temp = min(temp,p[c][j][r][1]); 
        if(r==nowcolor) {
          ans = min(ans, p[c][j][r][0]);
          temp = min(temp,p[c][j][r][0]); 
        }
      }
    } else {
      gg.cost[gg.n-1][j-1]=maxint;
      for(r=1;r<=m;r++) {
        ans = min(ans, p[c][j][r][1]);
        if(r==nowcolor) {
          ans = min(ans, p[c][j][r][0]);
        }
      }
    }
    p[a][nowcolor][bancolor][1] += ans;
  }

  if(gg.n)
    p[a][nowcolor][bancolor][0] += gg.solve();
}

void make2(int a, int fa) {
  for(int i=(int)edge[a].size()-1;i>=0;i--) {
    if(edge[a][i] != fa) 
      make2(edge[a][i], a);
    else 
      edge[a].erase(edge[a].begin() + i);
  }
  int i,j;
  for(i=1;i<=m;i++) {
    for(j=1;j<=m;j++)
      make(a, i, j);
  }
}


int main() {
  int ii,nn;
  scanf("%d", &nn);
  for(ii=1;ii<=nn;ii++) {
    printf("Case #%d: ", ii);
    scanf("%d %d %d", &n, &m, &P);
    for(i=1;i<=n;i++)
      for(j=1;j<=m;j++)
        scanf("%lld", &cost[i][j]);
    m++;
    for(i=1;i<=n;i++)
      cost[i][m]=1000001;
    for(i=1;i<=n;i++) {
      edge[i].clear();
    }
    for(i=1;i<n;i++) {
      int a,b;
      scanf("%d %d", &a, &b);
      edge[a].push_back(b);
      edge[b].push_back(a);
    }
    make2(1,0);
    LD ans = maxint;
    for(i=1;i<=m;i++)  {
      ans=min(ans, p[1][i][m][0]);
      ans=min(ans, p[1][i][m][1]);
    }
    printf("%lld\n", ans);
  }
  return 0;
}
