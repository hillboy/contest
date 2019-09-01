// https://www.spoj.com/problems/FASTFLOW/
#include <algorithm>
#include <stdio.h>
#include <string.h>
#define maxn 5011
#define maxm 61000

using namespace std;

typedef long long int LD;

struct Graph {
  int n, et, ind[maxn], e[maxm], last[maxm];

  inline void adde(int a, int b) {
    last[++et] = ind[a];
    e[et] = b;
    ind[a] = et;
  }

  inline void init(int nn) {
    n = nn, et = 1;
    memset(ind, 0, sizeof(int) * (n + 1));
  }
};

struct FlowGraph : public Graph {
  int S, T;

  LD cap[maxm], f[maxm];

  inline void adde(int a, int b, LD c) {
    Graph::adde(a, b);
    f[et] = 0, cap[et] = c;
  }

  inline void addee(int a, int b, LD c) { adde(a, b, c), adde(b, a, c); }

  inline void init(int nn, int s, int t) {
    Graph::init(nn);
    S = s, T = t;
  }
};

struct ResiGraph : public FlowGraph {
  int ek[maxm];
  bool checked[maxn];

  void adde(int a, int b, LD c, int k) {
    FlowGraph::adde(a, b, c);
    ek[et] = k;
  }

  LD dfs(int a, LD flow) {
    if (flow == 0) {
      return 0;
    }
    if (a == T)
      return flow;

    LD ans = 0, now;

    for (int i = ind[a]; i; i = last[i])
      if (!checked[e[i]] && cap[i] - f[i]) {
        now = dfs(e[i], std::min(flow, cap[i] - f[i]));
        ans += now, f[i] += now, flow -= now;
      }
    if (flow)
      checked[a] = true;
    return ans;
  }

  LD blocking_flow() {
    LD upper_bound = 0;
    memset(checked, 0, sizeof(bool) * (n + 1));
    for (int i = ind[S]; i; i = last[i]) {
      upper_bound += cap[i];
    }
    return dfs(S, upper_bound);
  }
};

struct DinicGraph : public FlowGraph {
  ResiGraph resi;
  int que[maxn], nowqt, qt, checked[maxn];

  LD cf() {
    resi.init(n, S, T);
    memset(checked, 0, sizeof(int) * (n + 1));
    qt = nowqt = 1;
    que[1] = S;
    checked[S] = 1;

    for (int i = 1, j = 0, nowlv = 2; i <= qt; i++) {
      if (i > nowqt) {
        nowlv++, nowqt = qt;
        if (checked[T]) {
          break;
        }
      }
      for (j = ind[que[i]]; j; j = last[j])
        if ((!checked[e[j]] || checked[e[j]] == nowlv) && f[j] < cap[j]) {
          if (!checked[e[j]]) {
            que[++qt] = e[j];
            checked[e[j]] = nowlv;
          }

          if (f[j ^ 1]) {
            resi.adde(que[i], e[j], f[j ^ 1], j);
          } else {
            resi.adde(que[i], e[j], cap[j] - f[j], j);
          }

          // For directed graph, use:
          // TODO: test this
          // if ((j & 1) && f[j ^ 1]) {
          //   resi.adde(que[i], e[j], f[j ^ 1], j);
          // } else if (!(j & 1)) {
          //   resi.adde(que[i], e[j], cap[j] - f[j], j);
          // }
        }
    }

    LD incr = resi.blocking_flow();
    if (incr == 0) {
      return 0;
    }

    for (int i = 1, j, k; i <= n; i++) {
      for (j = resi.ind[i]; j; j = resi.last[j])
        if (resi.f[j]) {
          k = resi.ek[j];
          if (f[k ^ 1]) {
            f[k ^ 1] -= resi.f[j];
          } else {
            f[k] += resi.f[j];
          }
        }
    }
    return incr;
  }

  LD maxflow() {
    LD ans = 0, now = cf();
    while (now) {
      ans += now;
      now = cf();
    }
    return ans;
  }
} G;

int main() {
  int i, n, m, a, b;
  long long int c;
  scanf("%d %d", &n, &m);
  G.init(n, 1, n);
  for (i = 1; i <= m; i++) {
    scanf("%d %d %lld", &a, &b, &c);
    if (a != b)
      G.addee(a, b, c);
  }
  printf("%lld\n", G.maxflow());
  return 0;
}
