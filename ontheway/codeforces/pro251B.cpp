#include<stdio.h>
#include<string.h>
#define maxn 200

int p[maxn],q[maxn],tp[maxn],tpp[maxn];

int color[maxn];

int len[maxn],delta[maxn];

int i,j,r,k,n,m,C;

bool make0(){
  for(i=1;i<=C;i++){
    if(delta[i])
      return 0;
  }
  if(m){
    printf("NO\n");
  }else
    printf("YES\n");
  return 1;
}
bool make1(){
  for(i=1;i<=C;i++){
    if(len[i]>2)
      return 0;
  }
  if(m>1){
    printf("NO\n");
  }else
    printf("YES\n");
  return 1;
}
bool makeA(){
  for(i=m;i>0;i-=2){
    for(j=1;j<=C;j++){
      if(i%len[j]!=delta[j]){
        break;
      }
    }
    if(j>C){
      for(r=0;r<i;r++){
        for(j=1;j<=C;j++){
          if(r%len[j]!=delta[j]){
            break;
          }
        }
        if(j>C)
          break;
      }
      if(r>=i){
        printf("YES\n");
        return 1;
      }
    }
  }
  return 0;
}
bool makeB(){
  for(i=m;i>0;i-=2){
    for(j=1;j<=C;j++){
      // printf("%d %d %d\n",len[j],((-i)%len[j]+len[j])%len[j],delta[j]);
      if(((-i)%len[j]+len[j])%len[j]!=delta[j]){
        break;
      }
    }
    if(j>C){
      for(r=0;r<i;r++){
        for(j=1;j<=C;j++){
          if(((-r)%len[j]+len[j])%len[j]!=delta[j]){
            break;
          }
        }
        if(j>C)
          break;
      }
      if(r>=i){
        printf("YES\n");
        return 1;
      }
    }
  }
  return 0;
}

int main(){
  scanf("%d %d",&n,&m);
  for(i=1;i<=n;i++){
    scanf("%d",&p[i]);
    tp[i]=i;
  }
  for(i=1;i<=n;i++){
    scanf("%d",&q[i]);
  }

  memset(delta,-1,sizeof(delta));
  for(i=1;i<=n;i++){
    if(color[i]==0){
      j=i;
      C++;
      while(1){
        color[j]=C;
        j=p[j];
        len[C]++;
        if(j==i)
          break;
      }
      for(r=0;r<len[C];r++){
        bool same=true;
        j=i;
        while(1){
          if(tp[j]!=q[j])
            same=false;
          tpp[j]=tp[p[j]];
          j=p[j];
          if(j==i)
            break;
        }
        if(same){
          delta[C]=r;
          break;
        }
        j=i;
        while(1){
          tp[j]=tpp[j];
          j=p[j];
          if(j==i)
            break;
        }
      }
      if(delta[C]<0){
        printf("NO\n");
        return 0;
      }
    }
  }
  if(make0()){
    return 0;
  }
  if(make1()){
    return 0;
  }
  if(makeA()){
    return 0;
  }
  if(makeB()){
    return 0;
  }
  printf("NO\n");
  return 0;
}
