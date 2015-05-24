#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
#define maxn 201000

typedef long long int LD;

// binary index tree. bit tree
// must be 1 indexed instead of 0
struct BitTree {
  LD c[maxn];
  inline int lowbit(int x) {
    return x & (-x);
  }

  void modify(int pos, LD x) {
    while (pos < maxn) {
      c[pos] += x;
      pos += lowbit(pos);
    }
  }
  LD sum(int end) {
    LD sum = 0;
    while (end) {
      sum += c[end];
      end -= lowbit(end);
    }
    return sum;
  }
}tree;

int i,j,n,m,k;

pair<int, int> p[maxn];

int ans[maxn];

int main() {
  scanf("%d",&n);
  for(i=1;i<=n;i++) {
    scanf("%d",&j);
    p[i].first = j;
    p[i].second = i;
  }
  sort(&p[1], &p[1+n]);
  i=j=1;
  for(i=1;i<=n;i++) {
    for(k=1;k<n;k++){
      int l = k*(p[i].second-1)+2;
      if (l>n)
        break;
      int r = k*p[i].second+1;
      if(r>n)
        r=n;
      ans[k] += tree.sum(r) - tree.sum(l-1);
    }
    tree.modify(p[i].second, 1);
  }
  for(i=1;i<n;i++){
    printf("%d ", ans[i]);
  }
  printf("\n");
  return 0;
}
