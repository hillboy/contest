#include<stdio.h>

bool ok(int a, int b, int c) {
  return ((b-a)* (c-a)) > 0;
}

int main() {
  int n, ax,ay, bx, by, cx,cy;
  scanf("%d %d %d %d %d %d %d", &n, &ax, &ay, &bx, &by, &cx, &cy);
  if (!ok(ax, bx, cx)) {
    printf("NO\n");
    return 0;
  }
  if (!ok(ay, by, cy)) {
    printf("NO\n");
    return 0;
  }
  printf("YES\n");

  return 0;
}
