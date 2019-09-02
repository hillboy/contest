// max match with dinic
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <unordered_map>
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
          if ((j & 1) && f[j ^ 1]) {
            resi.adde(que[i], e[j], f[j ^ 1], j);
            if (!checked[e[j]]) {
              que[++qt] = e[j];
              checked[e[j]] = nowlv;
            }
          } else if (!(j & 1)) {
            resi.adde(que[i], e[j], cap[j] - f[j], j);
            if (!checked[e[j]]) {
              que[++qt] = e[j];
              checked[e[j]] = nowlv;
            }
          }
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

struct rect {
  int x1, x2, y1, y2;
  void input() { scanf("%d %d %d %d", &x1, &y1, &x2, &y2); }
} rects[51];

struct uniqset {
  int n, ed;
  int que[1000];
  void add(int a) { que[++n] = a; }
  uniqset(int m) {
    n = 2;
    que[1] = 1;
    que[2] = m + 1;
  }
  void prepare() {
    sort(&que[1], &que[1 + n]);
    ed = std::unique(&que[1], &que[1 + n]) - que;
    n = ed - 1;
  }
  int find(int a) { return lower_bound(&que[1], &que[ed], a) - que; }
};

bool checked[200][200];

int main() {
  int i, n, m;
  scanf("%d %d", &n, &m);
  uniqset row(n), col(n);
  for (i = 1; i <= m; i++) {
    rects[i].input();
    row.add(rects[i].x1);
    row.add(rects[i].x2 + 1);
    col.add(rects[i].y1);
    col.add(rects[i].y2 + 1);
  }
  row.prepare();
  col.prepare();
  G.init(2 + row.n + col.n, 1, 2);

  for (i = 1; i <= m; i++) {
    int x1 = row.find(rects[i].x1);
    int x2 = row.find(rects[i].x2 + 1);
    int y1 = col.find(rects[i].y1);
    int y2 = col.find(rects[i].y2 + 1);

    for (int x = x1; x < x2; x++) {
      for (int y = y1; y < y2; y++) {
        if (!checked[x][y]) {
          checked[x][y] = 1;
          G.addee(2 + x, 2 + row.n + y, 1000000000);
        }
      }
    }
  }
  for (int x = 1; x < row.n; x++) {
    G.addee(1, 2 + x, row.que[x + 1] - row.que[x]);
  }
  for (int y = 1; y < col.n; y++) {
    G.addee(2 + row.n + y, 2, col.que[y + 1] - col.que[y]);
  }

  LD ans = G.maxflow();
  printf("%d\n", (int)ans);

  return 0;
}
