#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include <map>
#include <string>
#include <math.h>
using namespace std;

#define forlr(i,l,r) for(i=l;i<r;i++)
#define forrl(i,r,l) for(i=r-1;i>=l;i--)
#define for0r(i,r) forlr(i,0,r)

#define forltr(i,l,r) for(i=l;i<=r;i++)
#define for1tr(i,r) forltr(i,1,r)
#define forrtl(i,r,l) for(i=r;i>=l;i--)

#define forcnt(n) for(int cnt=n; cnt; cnt--)

#define X(x) (x).first
#define Y(x) (x).second

#define mymemset(x, val) memset(x, val, sizeof(x))
#define sz(x) ((int)x.size())

typedef long long int LD;

#define maxn 1000000

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
   // eg must be clear before same instance used again.
  vector<Edge> eg;
  vector<Edge*> net[N];
  Edge *prev[N];
  // v is the number of nodes. indexed as 0..v-1
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
  return (dis[t] < 0);
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
  return (dis[t] < 0);
}

int Network::mincost(int ss, int tt) {
  s = ss; t = tt; initFlow();
  //Add it if needed.

  if(!Bellman()) {
    return 0;
  }
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
int i,j,n,m;
int g[111][111], f[111][111];
int main() {
  scanf("%d %d", &n, &m);
  int u,v,c,ff;
  forcnt(m) {
    scanf("%d %d %d %d", &u, &v, &c, &ff);
    u--;v--;
    g[u][v] += c;
    ::f[u][v] += ff;
  }

  LD ans = 0;
  for0r(i, n) {
    for0r(j, n) {
      ans += f[i][j];
      if(::f[i][j] <= g[i][j]) {
        minflow.eg.push_back(Edge(i, j, f[i][j], 0, -1));
        if(g[i][j] > f[i][j])
          minflow.eg.push_back(Edge(i, j, g[i][j] - f[i][j], 0, 0));
        minflow.eg.push_back(Edge(i, j, 100000000, 0, 2));
      } else {
        ans += g[i][j] -f[i][j];
        minflow.eg.push_back(Edge(i, j, f[i][j] - g[i][j], 0, -2));
        minflow.eg.push_back(Edge(i, j, g[i][j], 0, -1));
        minflow.eg.push_back(Edge(i, j, 100000000, 0, 2));
      }
    }
  }
  minflow.v = n;
  ans += minflow.mincost(0, minflow.v -1);
  printf("%d %d\n", minflow.getCost(), minflow.getFlow());
  printf("%d\n", (int)ans);
  return 0;
}
