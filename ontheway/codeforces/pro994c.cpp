#include<stdio.h>
#include<algorithm>

struct point {
  int x,y;

  point from(point a) {
    point aa;
    aa.x = a.x - x;
    aa.y = a.y - y;
    return aa;
  }
};

int cross(point a, point b) {
  return a.x * b.y - a.y * b.x;
}

int sign(int a) {
  if (a>0) return 1;
  if (a<0) return -1;
  return 0;
}

struct square {
  point p[4];
  void input() {
    int i;
    for(i=0;i<4;i++) {
      scanf("%d %d", &p[i].x, &p[i].y);
    }
  }
}a, b;

int i,j,r,k,n,m;

int main() {
  a.input();
  b.input();
  for(i=0;i<4;i++) {
    j=(i+1)%4;
    for(r=0;r<4;r++) if (r!=i && r!=j) {
      n=sign(cross(a.p[i].from(a.p[j]), a.p[i].from(a.p[r])));
    }
    for(r=0;r<4;r++) {
      m=sign(cross(a.p[i].from(a.p[j]), a.p[i].from(b.p[r])));
      if(n*m>=0) {
        break;
      }
    }
    if(r==4) {
      printf("No\n");
      return 0;
    }
  }
  std::swap(a,b);
  for(i=0;i<4;i++) {
    j=(i+1)%4;
    for(r=0;r<4;r++) if (r!=i && r!=j) {
      n=sign(cross(a.p[i].from(a.p[j]), a.p[i].from(a.p[r])));
    }
    for(r=0;r<4;r++) {
      m=sign(cross(a.p[i].from(a.p[j]), a.p[i].from(b.p[r])));
      if(n*m>=0) {
        break;
      }
    }
    if(r==4) {
      printf("No\n");
      return 0;
    }
  }
  printf("Yes\n");
  return 0;
}
