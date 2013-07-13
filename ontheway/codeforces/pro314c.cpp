// standard binary index tree
#include<stdio.h>
#include<string.h>
#include<map>
using namespace std;
typedef long long int LD;

#define maxn 1000100
#define div  1000000007
int i,j,n,m;

LD p[maxn],q[maxn];

LD c[maxn];

inline int lowbit(int x) {
  return x & (-x);
}

void modify(int pos, LD x) {
  while (pos < maxn) {
    c[pos] += x;
    c[pos]%=div;
    pos += lowbit(pos);
  }
}

LD sum(int end) {
  LD sum = 0;
  while (end) {
    sum += c[end];
    sum%=div;
    end -= lowbit(end);
  }
  return sum;
}


LD fix(LD a){
  return ((a%div)+div)%div;
}

int main(){
  scanf("%d",&n);
  int now;
  q[0]=1;
  for(i=1;i<=n;i++){
    scanf("%d",&now);
    LD temp=now+sum(now)*now;
    temp=fix(temp);
    modify(now,fix(temp-q[now]));
    q[now]=temp;
    p[i]=now;
  }
  LD ans=0;
  for(i=n;i>=1;i--){
    ans+=q[p[i]];
    q[p[i]]=0;
    ans=fix(ans);
  }
  printf("%d\n",(int)(ans));
  return 0;
}
