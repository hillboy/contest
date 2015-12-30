#include<stdio.h>

inline int leq(int a1,int a2,int b1,int b2){
  return a1<b1||a1==b1&&a2<=b2;
}

inline int leq(int a1,int a2,int a3,int b1,int b2,int b3){
  return a1<b1||a1==b1&&leq(a2,a3,b2,b3);
}

//stable sort a[0..n-1] to b[0..n-1] with keys in 0..K from r
void radixPass(int a[],int b[],int r[],int n,int K){
  //count occurrences
  int *c=new int[K+1];
  //counter array
  int i;
  for(i=0; i<=K; i++) c[i]=0;//reset counters
  for(i=0; i<n; i++) c[r[a[i]]]++;//count occurrences
  int sum=0;
  for( i=0; i<=K; i++) //exclusive prefix sums
  {int t=c[i]; c[i]=sum; sum+=t;}
  for( i=0; i<n; i++) b[c[r[a[i]]]++]=a[i];//sort
  delete[] c;
}

//find the suffix array SA of s[0..n-1] in {1..K}^n
//require s[n]=s[n+1]=s[n+2]=0,n>=2
void suffixArray(int s[],int SA[],int n,int K){
  int n0=(n+2)/3,n1=(n+1)/3,n2=n/3,n02=n0+n2;
  int* s12 =new int[n02+3];  s12[n02]= s12[n02+1]= s12[n02+2]=0;
  int* SA12=new int[n02+3]; SA12[n02]=SA12[n02+1]=SA12[n02+2]=0;
  int* s0  =new int[n0];
  int* SA0 =new int[n0];
  int i,j;

  //generate positions of mod 1 and mod 2 suffixes
  //the "+(n0-n1)" adds a dummy mod 1 suffix if n%3 == 1
  //...for the convience of calculating s0[]
  for(i=0,j=0; i<n+(n0-n1); i++) if(i%3!=0) s12[j++]=i;

  //lsb radix sort the mod 1 and mod 2 triples
  radixPass(s12 ,SA12,s+2,n02,K);
  radixPass(SA12,s12 ,s+1,n02,K);
  radixPass(s12 ,SA12,s  ,n02,K);

  //find lexicographic names of triples
  int name=0,c0=-1,c1=-1,c2=-1;
  for(i=0; i<n02; i++){
    if(s[SA12[i]]!=c0||s[SA12[i]+1]!=c1||s[SA12[i]+2]!=c2){
      name++;
      c0=s[SA12[i]];
      c1=s[SA12[i]+1];
      c2=s[SA12[i]+2];
    }
    if(SA12[i]%3==1) s12[SA12[i]/3]   =name; //left half
    else             s12[SA12[i]/3+n0]=name; //right half
  }

  //recurse if names are not yet unique
  if(name<n02){
    suffixArray(s12,SA12,n02,name);
    //stor unique names in s12 using the suffix array
    for(int i=0; i<n02; i++) s12[SA12[i]]=i+1;
  }else
    for(int i=0; i<n02; i++) SA12[s12[i]-1]=i;

  //stable sort the mod 0 suffixes from SA12by their first character
  for(i=0,j=0; i<n02; i++) if(SA12[i]<n0) s0[j++]=3*SA12[i];
  radixPass(s0,SA0,s,n0,K);

  //merge sort SA0 suffixes and sorted SA12 suffixes
  for(int p=0,t=n0-n1,k=0; k<n; k++){ //the dummy mod 1 suffix is at the front of SA12[]
    int i=(SA12[t]<n0 ? SA12[t]*3+1 : (SA12[t]-n0)*3+2);
    int j=SA0[p];
    if(SA12[t]<n0?leq(s[i],s12[SA12[t]+n0],s[j],s12[j/3]):

       leq(s[i],s[i+1],s12[SA12[t]-n0+1],s[j],s[j+1],s12[j/3+n0]))
    {
      SA[k]=i; t++;
      if(t==n02) for(k++; p<n0; p++,k++) SA[k]=SA0[p];
    }else{
      SA[k]=j; p++;
      if(p==n0) for(k++; t<n02; t++,k++)
        SA[k]=(SA12[t]<n0 ? SA12[t]*3+1 : (SA12[t]-n0)*3+2);
    }
  }
  delete[] s12; delete[] SA12; delete[] SA0; delete[] s0;
}


#define  maxn 5100

int i,j,n,m;

int mp[maxn],sa[maxn],rank[maxn], height[maxn];

void GetHeight(int s[],int SA[],int height[],int n){
  int i,h;
  for(i=0; i<n; i++) rank[SA[i]]=i;
  height[n-1]=0;
  for(i=0,h=0; i<n; i++){
    if(rank[i]==n-1) continue;
    int j=SA[rank[i]+1];
    while(s[i+h]==s[j+h]) h++;
    height[rank[i]]=h;
    if(h>0) h--;
  }
}

struct RMQ {
  static int q[maxn][30];
  static int nbits[maxn+1];
  int i,j,n,m;
  // p indexed  0 .. n - 1
  void init(int p[maxn], int nn) {
    n = nn;
    int x=1,xx=1;
    q[0][0]=p[0];
    for(i=1;i<n;i++) {
      q[i][0]=p[i];
      nbits[i] = nbits[i-1];
      if(i == (i&-i))
        nbits[i]++;
    }
    nbits[i] = nbits[i-1];
    if(i == (i&-i))
      nbits[i]++;
    while(1) {
      for(i=0;i<n;i++){
        q[i][xx]=q[i][xx-1];
        j=i-x;
        if(j>=0) {
          if(q[j][xx-1] < q[i][xx])
            q[i][xx]=q[j][xx-1];
        }
      }
      x+=x;
      if(x>n)
        break;
      xx++;
    }
  }

  int ask(int l, int r) {
    int x=r-l+1;
    int xx=nbits[x]-1;
    int ans = q[l+(1<<xx)-1][xx];
    if(q[r][xx] < ans)
      ans=q[r][xx];
    return ans;
  }

}rmq;
int RMQ::q[maxn][30];
int RMQ::nbits[maxn];

bool same(int i,int j,int len) {
  if(i==j)
    return true;
  int a=rank[i],b=rank[j];
  if(a>b) {
    a=rank[j],b=rank[i];
  }
  b--;
  return rmq.ask(a,b) >=len;
}

#define div 1000000007

int p[2][maxn];

inline void add(int& a, int b) {
  a+=b;
  if(a>=div)
    a-=div;
}

void make() {
  int len,now=0,other;
  int a,b;
  for(len=1;len<=n;len++) {
    other=now;
    now=1-now;
    for(i=0;i<n;i++) {
      p[now][i]=p[other][i];
      if(i-len+1==0) {
        add(p[now][i],1);
      } else if(i-len>=0) {
        a=i-len+1;
        if(mp[a]==1) {
          continue;
        }

        if(i-len-len+1>=0) {
          b=a-len;
          if(!same(a,b,len) && rank[b]<rank[a]) {
            add(p[now][i],p[now][i-len]);
          } else {
            add(p[now][i],p[other][i-len]);
          }
        } else {
          add(p[now][i],p[other][i-len]);
        }
      }
    }
  }
  printf("%d\n", (int)p[now][n-1]);
}

int main() {
  scanf("%d",&n);
  char a;
  for(i=0;i<n;i++) {
    scanf(" %c", &a);
    mp[i]=a-'0'+1;
  }
  suffixArray(mp, sa, n, 12);
  GetHeight(mp, sa, height, n);
  rmq.init(height, n);
  make();
  return 0;
}
