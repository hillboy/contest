#include<stdio.h>
#include<algorithm>
using namespace std;

typedef long long int LD;

int c_(LD a) {
  int c2=0,c5=0;
  LD now;
  now = a;
  while(now) {
    now/=2;
    c2+=now;
  }
  now = a;
  while(now) {
    now/=5;
    c5+=now;
  }
  return min(c2,c5);
}

int find0(int a) {
  if(a==0) {
    return 1;
  }
  int l = 1, r = 1000000, mid;
  while(l<=r) {
    mid=(l+r)/2;
    if(c_(mid) >=a) {
      r = mid -1;
    } else {
      l=mid+1;
    }
  }
  return l;
}

int n, ans1, ans2;

int main() {
  scanf("%d", &n);
  if(n==0) {
    printf("4\n");
    for(n=1;n<=4;n++) {
      printf("%d ", n);
    }
    return 0;
  }
  ans1=find0(n);
  ans2=find0(n+1);
  if(c_(ans1) != n) {
    printf("0\n");
    return 0;
  }
  printf("%d\n", ans2-ans1);
  while(ans1<ans2) {
    printf("%d ", ans1);
    ans1++;
  }
  return 0;
}
