#include<stdio.h>
#include<algorithm>
using namespace std;
#define maxn 1001000

struct point{
  int a,b;
}p[maxn];
int i,j,n,m;
bool cmp(point a,point b){
  return a.a<b.a;
}
int main(){
  scanf("%d",&n);
  for(i=0;i<n;i++){
    scanf("%d %d",&p[i].a,&p[i].b);
  }
  sort(p,p+n,cmp);
  long long int now=0;
  int nowsize=-1;
  for(i=0;i<n;i++){
    while(now>1&&nowsize<p[i].a){
      nowsize++;
      if(now%4)
        now=now/4+1;
      else
        now=now/4;
    }
    nowsize=p[i].a;
    if (p[i].b>now)
      now=p[i].b;
    // printf("%lld %d\n",now,nowsize);
  }
  while(now>1){
    nowsize++;
      if(now%4)
        now=now/4+1;
      else
        now=now/4;
  }
  if (nowsize == p[n-1].a)
    nowsize++;
  printf("%d\n",nowsize);
  return 0;
}
