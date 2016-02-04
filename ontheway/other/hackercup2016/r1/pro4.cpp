#include<stdio.h>
#include<string.h>

#define maxn (1<<20)


int h[30];
int bits[maxn];

int bitarray[32][maxn];

bool p[32][maxn];
bool checked[32][maxn];

int i,j,n,m;

int mp[32][32];

void prepare() {
  h[0]=1;
  for(i=1;i<30;i++)h[i]=h[i-1]*2;
  for(i=1;i<maxn;i++) {
    bits[i]=bits[ i ^(i&(-i))] + 1;
    bitarray[bits[i]][++bitarray[bits[i]][0]] = i;
  }
}

bool make(int a,int now, int m) {
  if(checked[a][now]) {
    return p[a][now];
  }
  checked[a][now]=true;
  if(m==0) {
    return p[a][now]=true;
  }
  int i,j;
  int mm = (1<<m)/2, other;
  for(i=1;i<=bitarray[mm][0];i++) {
    if(bitarray[mm][i] >= h[n])
      break;
    if((bitarray[mm][i] & now) != bitarray[mm][i]) {
      continue;
    }
    if((bitarray[mm][i] & h[a]) != h[a]) {
      continue;
    }
    if(!make(a, bitarray[mm][i], m-1)) {
      continue;
    }
    other = (now ^ bitarray[mm][i]);
    for(j=0;j<n;j++) {
      if(h[j] & other) {
        if(mp[a][j] && make(j, other, m-1)) {
          return p[a][now]=true;
        }
      }
    }
  }
  
  return p[a][now]=false;
}

int main() {
  int ii,nn;
  scanf("%d", &nn);
  prepare();
  for(ii=1;ii<=nn;ii++) {
    printf("Case #%d: \n", ii);
    scanf("%d", &n);
    for(i=0;i<n;i++) {
      for(j=0;j<n;j++) {
        scanf("%d", &mp[i][j]);
      }
    }
    memset(checked,0,sizeof(checked));
    m=0;
    while((1<<m) < n) {
      m++;
    }
    int r,rr;
    bool win=false;
    for(i=0;i<n;i++) {
      // printf("%d: ", i);
      for(r=m;r;r--) {
        rr=(1<<r);
        win=false;
        for(j=1;j<=bitarray[rr][0];j++) {
          if(bitarray[rr][j] >= h[n])
            break;
          if(bitarray[rr][j] & h[i]) {
            if(make(i, bitarray[rr][j], r)) {
              win=true;
              break;
            }
          }
        }
        if(win)
          break;
      }
      if(win) {
        if(r==m) {
          // printf("(r=%d, bit = %d, rr= %d)", r, bitarray[rr][j], rr);
          printf("%d ", 1);
        } else {
          // printf("(r=%d, bit = %d)", r, bitarray[rr][j]);
          printf("%d ", (1 << (m-r-1)) + 1);
        }
      } else {
        printf("%d ", n/2+1);
      }
      for(j=0;j<n;j++) if(i!=j && mp[j][i]) {
        break;
      }
      if(j==n) {
        printf("%d\n", 1);
      } else {
        printf("%d\n", n/2+1);
      }
    }
  }
  return 0;
}
