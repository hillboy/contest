#include<stdio.h>
#define maxn 200100
typedef long long int LD;
// binary index tree. bit tree
// must be 1 indexed instead of 0
struct BitTree {
  LD c[maxn];
  LD cc[maxn];
  LD bd;
  inline int lowbit(int x) {
    return x & (-x);
  }

  void modify(int pos, LD x) {
    if(cc[pos] + x >bd) {
      x=bd-cc[pos];
    }
    cc[pos]+=x;
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
}ta,tb;

int i,j,n,m,a,b,k,q;

int main() {
  int q;
  scanf("%d %d %d %d %d", &n, &k, &a, &b, &q);
  ta.bd=a;
  tb.bd=b;
  int c,cc,ccc;
  LD ans;
  while(q--) {
    scanf("%d", &c);
    if(c==1) {
      scanf("%d %d", &cc, &ccc);
      ta.modify(cc,ccc);
      tb.modify(cc,ccc);
    } else {
      scanf("%d", &cc);
      ans = tb.sum(cc-1);
      ans+=ta.sum(n) - ta.sum(cc+k-1);
      printf("%lld\n", ans);
    }
  }
  return 0;
}
