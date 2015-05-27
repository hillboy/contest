// simple max flow maxflow
#include<stdio.h>
#include<cstdio>
#include<algorithm>
#include<string>
#include<string.h>
#include<map>
#include<set>
using namespace std;

#define For(i,s,t) for(int i=(s); i<(t); i++)
#define fori(n) For(i,0,n)
#define forj(n) For(j,0,n)
#define fork(n) For(k,0,n)
#define clr(x) memset(x,0,sizeof(x))
#define clr2(x) memset(x,-1,sizeof(x))

typedef int T; const int maxV=900;

#define maxn 900

/*==================================================
  最高标号的预流推进
  ==================================================*/
/* 说明 --------------------------------------------
T: O(V^2*sqrt(E))
M: O(int*4*V^2) 可优化至 O(E)
例子:
int main() {
int V,E,S,T,a,b,c;
cin>>V>>E>>S>>T;
n=V, soure=S, sink=T;
init();
fori(E) cin>>a>>b>>c, adde(a,b,c);
build();
cout<<preflow();
}
--------------------------------------------------*/
#define ForAdj(i,j) 	for(int _t=0, j; j=G[i][_t], _t<D[i]; _t++)
#define AddFlow(i,j,f) 	R[i][j]-=f, R[j][i]+=f, E[i]-=f, E[j]+=f
#define AddL(x) 		L[H[x]][LN[H[x]]++]=x
#define Active(a) 		P[a]=0, AddL(a)
#define SetH(a,h) 		HN[H[a]]--, HN[h]++, H[a]=h
int H[maxV], HN[maxV];
T E[maxV];
T R[maxV][maxV];
T C[maxV][maxV];
int L[maxV*2][maxV], LN[maxV*2]; // L,与G都可优化至M[O(E)]
int G[maxV][maxV], D[maxV], P[maxV];
//构图
int n, soure, sink; // INIT THESES !!
void init() { clr(D); fori(n) forj(n) R[i][j]=0; }
void adde(int a,int b,int w) { if(a!=b) R[a][b]+=w; C[a][b]+=w;}
void build() {
  fori(n) forj(i) if(R[i][j]>0||R[j][i]>0){
    G[i][D[i]++]=j, G[j][D[j]++]=i;
  }
}
int check(int a) {
  int chg=0, ha=H[a];
  while(E[a]>0) {
    if(P[a]==D[a]) { // relabel
      int minh=2*n;
      ForAdj(a,b) if(R[a][b]>0) {minh=(minh<H[b]?minh:H[b]);}
      SetH(a,minh+1); P[a]=0;
    } else {
      int b=G[a][P[a]];
      if(R[a][b]>0 && H[a]==H[b]+1) { // push
        T x=min(E[a],R[a][b]);
        if(E[b]==0 && b!=sink && b!=soure) {
          chg=chg || H[b]>ha;
          Active(b);
        }
        AddFlow(a,b,x);
      } else P[a]++;
    }
  }
  return chg;
}
int pre() { // return if s->t connected
  int Q[maxV], qh=0, qt=0;
  fori(n) H[i]=n;
  Q[qt++]=sink, H[sink]=0;
  while(qh<qt) {
    int i=Q[qh++];
    ForAdj(i,j) if(H[j]==n) Q[qt++]=j, H[j]=H[i]+1;
  }
  if(H[soure]==n) return 0;
  clr(E), clr(LN), clr(HN), clr(P);
  H[soure]=n;
  fori(n) if(i!=soure) HN[H[i]]++;

  ForAdj(soure,i) {
    T x=R[soure][i];  // CARE: AddFlow is a MACRO
    if(x>0) {
      AddFlow(soure,i,x);
      if(i!=sink) Active(i);
    }
  }
  return 1;
}
void update(int h) {
  for(int i=h+1; i<=n; i++) LN[i]=0;
  fori(n) if(i!=soure && H[i]>h && H[i]<=n) {
    SetH(i,n+1);
    if(E[i]>0) Active(i);
  }
}
T preflow() {
  if(!pre()) return 0;
  for(int h=n; h>0; h--) while(LN[h]) {
    int i=L[h][--LN[h]], t=h;
    if(check(i)) {
      h=H[i];
      if(HN[t]==0) update(t), h=(h>n+2?h:n+2);
      break;
    }
  }
  return E[sink];
}

int i,j,m;

int p[maxn], q[maxn];

int main() {
  int a,b,e,sum=0, sum2=0;
  scanf("%d %d", &m, &e);
  init();
  for(i=1;i<=m;i++) {
    scanf("%d", &p[i]);
    sum+=p[i];
    adde(0, i, p[i]);
    adde(i, i+m, p[i]);
  }
  for(i=1;i<=m;i++){
    scanf("%d", &q[i]);
    sum2+=q[i];
    adde(i+m, m+m+1, q[i]);
  }
  while(e--) {
    scanf("%d %d", &a, &b);
    adde(a, b+m, q[b]);
    adde(b, a+m, q[a]);
  }
  n=m+m+2;
  soure=0;
  sink=m+m+1;
  build();
  int ans = preflow();
  if(ans!=sum || ans != sum2) {
    printf("NO\n");
    return 0;
  }
  printf("YES\n");
  for(i=1;i<=m;i++) {
    for(j=1;j<=m;j++) {
      printf("%d ", C[i][j+m] - R[i][j+m]);
    }
    printf("\n");
  }
  return 0;
}
