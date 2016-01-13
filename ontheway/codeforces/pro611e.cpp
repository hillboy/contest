#include<stdio.h>
#include<algorithm>
#include<set>
using namespace std;

#define maxn 201000

int i,j,n,m;

int  p[maxn];

multiset<int> pp;

int q[10];
int a,b,c,ta,tb,tc;

int preans=0;
multiset<int>::iterator ii;

void make1() {

  while(pp.size()>0) {
    ii=pp.end();
    ii--;
    if(*ii <= a+b) {
      break;
    }
    preans++;
    pp.erase(ii);
  }
}
void make2() {
  while(pp.size()>0) {
    ii=pp.end();
    ii--;
    if(*ii <= a+c) {
      break;
    }
    n--;
    preans++;
    pp.erase(ii);

    ii=pp.lower_bound(c+1);
    if(ii!=pp.begin()) {
      ii--;
      pp.erase(ii);
    }
  }
}

void make3() {
  int tmp = max(b+c, a);
  while(pp.size() > 0) {
    ii=pp.end();
    ii--;
    if(*ii <= tmp) {
      break;
    }
    preans++;
    pp.erase(ii);

    ii=pp.lower_bound(b+1);
    if(ii!=pp.begin()) {
      ii--;
      pp.erase(ii);
    }
  }
}

void make41() {
  while(pp.size() > 0) {
    ii=pp.end();
    ii--;
    if(*ii <= a) {
      break;
    }
    preans++;
    pp.erase(ii);

    ii=pp.lower_bound(a+1);
    if(ii!=pp.begin()) {
      ii--;
      pp.erase(ii);
    }
  }
}

int count42() {
  if(pp.size()==0)
    return 0;
  ii=pp.end();
  ii--;
  int ans = 0;
  while(1) {
    if(*ii>b+c)
      ans++;
    else
      break;
    if(ii!=pp.begin()) {
      ii--;
    } else {
      break;
    }
  }
  return ans;
}

void make42() {
  while(pp.size() > 0) {
    ii=pp.end();
    ii--;
    if(*ii <= b+c) {
      break;
    }
    preans++;
    pp.erase(ii);

    ii=pp.lower_bound(b+c+1);
    if(ii!=pp.begin()) {
      ii--;
      if(*ii<=b) {
        pp.erase(ii);
        ii=pp.lower_bound(c+1);
        if(ii!=pp.begin()) {
          ii--;
          pp.erase(ii);
        }
      } else {
        pp.erase(ii);
      }
    }
  }
}

int findit(int a, int n) {
  int k = lower_bound(p, p+n, a+1) - p;
  return k;
}

int make6(int ta,int tb, int tc, int n) {
  int k=findit(b,n);
  tb+=(n-k);
  tc+=n-k;
  n=k;

  if(n>0) {
    k=findit(c,n);
    tb+=(n-k);
    n=k;
  }
  if(tb-tc < n) {
    int tmp= n-(tb-tc);
    tb+= tmp/2 + tmp %2;
  }
  return max(ta,max(tb,tc));
}

void make5(int start) {
  if(pp.size()==0) {
    printf("%d\n", preans);
    return;
  }
  n=0;
  for(ii=pp.begin();ii!=pp.end();ii++) {
    p[n++]=*ii;
  }
  int tta;
  int ans = -1, temp;
  for(tta=start;tta<=n;tta++) {
    temp=make6(tta,0,0,n-tta);
    if(ans<0||temp<ans)
      ans=temp;
  }
  printf("%d\n", ans+preans);
}

int main() {
  scanf("%d", &n);
  scanf("%d %d %d", &q[1], &q[2], &q[3]);
  for(i=0;i<n;i++) {
    scanf("%d", &p[i]);
    pp.insert(p[i]);
  }
  sort(p,p+n);
  sort(q+1,q+4);
  a=q[3];b=q[2];c=q[1];
//  printf("%d %d %d\n", a,b,c);
  if(a+b+c<p[n-1]){
    printf("-1\n");
    return 0;
  }
  make1();
  make2();
  make3();
  if(b+c>=a) {
    make41();
    make5(0);
  } else if (b+c < a) {
    make5(count42());
  }
  return 0;
}
