#include<stdio.h>
#include<algorithm>
using namespace std;

int main() {
  int n;
  long long int a,b,c;
  scanf("%d", &n);
  while(n--) {
    scanf("%lld %lld", &a, &b);
    if(a-b!=1) {
      printf("NO\n");
      continue;
    }
    a+=b;
    bool dead=false;
    for(c=2;c*c<=a;c++) {
      if(a%c==0) {
        dead=true;
        break;
      }
    }
    if(dead) {
      printf("NO\n");
    } else {
      printf("YES\n");
    }
  }

  return 0;
}
