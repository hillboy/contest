#include<stdio.h>
#include<string.h>

#define maxn 201000

char aa[maxn], bb[maxn], a[maxn], b[maxn];
char temp[maxn];

void make(char a[], char aa[], int l, int r) {
  int i;
  if( (r-l+1) % 2) {
    for(i=l;i<=r;i++)
      aa[i]=a[i];
    return;
  }
  int mid=(l+r)/2;
  make(a, aa, l, mid);
  make(a, aa, mid+1, r);
  int cmp=0;
  for(i=0;i<(r-l+1)/2;i++) {
    if(aa[l+i] != aa[mid+1+i]) {
      cmp = (aa[l+i] > aa[mid+1+i]) ? 1:-1;
      break;
    }
  }
  if(cmp>0) {
    memcpy(temp, &aa[l], sizeof(char)*(r-l+1)/2);
    memcpy(&aa[l], &aa[mid+1], sizeof(char)*(r-l+1)/2);
    memcpy(&aa[mid+1], temp, sizeof(char)*(r-l+1)/2);
  }
}

int n;

int main() {
  scanf("%s %s", a, b);
  n=strlen(a);
  make(a, aa, 0, n-1);
  make(b, bb, 0, n-1);
  if(strcmp(aa,bb)==0){
    printf("YES\n");
  } else {
    printf("NO\n");
  }
  return 0;
}
