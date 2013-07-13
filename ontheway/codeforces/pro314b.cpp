#include<stdio.h>
#include<string.h>

#define maxn 200

int i,j,r,n,m,nn,mm,start,nstartm;

char s1[maxn],s2[maxn];

int p[maxn],q[maxn],qq[maxn],qqq[maxn];

bool make(){
  for(i=1;i<=n;i++){
    p[i]=0;
    r=i;
    for(j=1;j<=m;j++){
      while(s1[r]!=s2[j]){
        r++;
        if(r>n){
          p[i]++;
          if(p[i]>m)
            return 0;
          r=1;
        }
      }
      if(j<m){
        r++;
        if(r>n){
          p[i]++;
          if(p[i]>m)
            return 0;
          r=1;
        }
      }
    }
    q[i]=r;
  }
  return 1;
}

void make2(){
  for(i=1;i<=n;i++){
    if(p[i]==0){
      qq[i]=1;
      j=q[i];
      qqq[i]=q[i];
      while(1){
        j++;
        if(j>n)
          break;
        if(p[j]>0)
          break;
        j=q[j];
        qqq[i]=j;
        qq[i]++;
      }
    } else {
      qq[i]=1;
    }
  }
}

int main(){
  int x,y;
  scanf("%d %d",&x,&y);
  scanf("%s %s",&s1[1],&s2[1]);
  n=strlen(&s1[1]);
  m=strlen(&s2[1]);
  if(!make()){
    printf("0\n");
    return 0;
  }
  make2();
  int ans=0,last=n;
  while(x>=0){
    last++;
    if(last>n){
      x--;
      last=1;
      if(x<0){
        break;
      }
    }
    if(p[last]==0){
      ans+=qq[last];
      last=qqq[last];
    }else
    if(x>=p[last]){
      ans++;
      x-=p[last];
      last=q[last];
    }
  }
  printf("%d\n",ans/y);
  return 0;
}
