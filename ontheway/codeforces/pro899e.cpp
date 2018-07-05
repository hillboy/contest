#include<stdio.h>
#include<vector>
#include<algorithm>

#define maxn 201000
int fa[maxn], next[maxn], sum[maxn], previous[maxn];

bool dead[maxn];

int i,j,n,m;

int p[maxn];

std::vector<std::pair<int, int>> q;

int findfa(int a) {
  if(fa[a]==a) {
    return a;
  }
  return fa[a]=findfa(fa[a]);
}

void merge(int a, int b) {
  if(sum[a] > sum[b])
    std::swap(a,b);
  fa[a]=b;
  sum[b] += sum[a];
  next[b] = std::max(next[b], next[a]);
  previous[b] = std::min(previous[b], previous[a]);
  auto pir = std::make_pair(sum[b], -b);
  q.push_back(pir);
  std::push_heap(q.begin(), q.end());
}

int main() {
  scanf("%d", &n);
  for(i=1;i<=n;i++) {
    scanf("%d", &p[i]);
    fa[i]=i;
    sum[i]=1;
    next[i]=i+1;
    previous[i]=i-1;
    auto pir = std::make_pair(1, -i);
    q.push_back(pir);
    std::push_heap(q.begin(), q.end());
  }
  for (i=1;i<=n;i++) {
    if (p[i]==p[i+1]) {
      merge(findfa(i), findfa(i+1));
    }
  }
  m=0;
  while(q.size() != 0) {
    auto pir = q[0];
    std::pop_heap(q.begin(), q.end());
    q.pop_back();
    i = findfa(-pir.second);
    if (dead[i])
      continue;
    int pre = previous[i], nxt = next[i];
    if (pre>0) pre=findfa(pre);
    if (nxt<=n) nxt = findfa(nxt);
    if (pre >0 && nxt <=n &&p[pre] == p[nxt]) {
      merge(pre, nxt);
    } else {
      next[pre] = nxt;
      previous[nxt]= pre;
    }
    dead[i]=true;
    m++;
  }
  printf("%d\n", m);
  return 0;
}
