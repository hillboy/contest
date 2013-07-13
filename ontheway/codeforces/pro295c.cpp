#include<stdio.h>
#define maxn 55
#define div 1000000007
int p[maxn][maxn][2];
long long int ans[maxn][maxn][2];
bool checked[maxn][maxn][2];
bool checking[maxn][maxn][2];

int que[maxn*maxn*2][3];

int i,j,n,m,A,B;

long long int C[maxn][maxn];

void prepare(){
  C[0][0]=1;
  for(i=1;i<maxn;i++){
    C[i][0]=1;
    for(j=1;j<=i;j++){
      C[i][j]=C[i-1][j-1]+C[i-1][j];
      if(C[i][j]>=div)
        C[i][j]-=div;
    }
  }
}
int de=1;
void make2(){
  int ii=1,t=1,i,j,nowp;
  int a,b,side;
  que[1][0]=A;que[1][1]=B;
  ans[A][B][0]=1;
  p[A][B][0]=1;
  while(ii<=t){
    a=que[ii][0];
    b=que[ii][1];
    side=que[ii][2];
    nowp=p[a][b][side];
    if(side==0){
      for(i=0;i<=a;i++){
        if(i>m)
          break;
        for(j=0;j<=b;j++){
          if(i+j>0&&i+2*j<=m){
            if(p[a-i][b-j][1-side]==0){
              p[a-i][b-j][1-side]=nowp+1;
              ans[a-i][b-j][1-side]+=C[a][i]*C[b][j]%div*ans[a][b][side]%div;
              if(ans[a-i][b-j][1-side]>=div)
                ans[a-i][b-j][1-side]-=div;
              t++;
              que[t][0]=a-i;
              que[t][1]=b-j;
              que[t][2]=1-side;
            } else if  (p[a-i][b-j][1-side]==nowp+1){
              ans[a-i][b-j][1-side]+=C[a][i]*C[b][j]%div*ans[a][b][side]%div;
              if(ans[a-i][b-j][1-side]>=div)
                ans[a-i][b-j][1-side]-=div;
            }
          }
        }
      }
    } else {
      int aa=A-a,bb=B-b;
      for(i=0;i<=aa;i++){
        if(i>m)
          break;
        for(j=0;j<=bb;j++){
          if(i+j>0&&i+2*j<=m){
            if(p[a+i][b+j][1-side]==0){
              p[a+i][b+j][1-side]=nowp+1;
              ans[a+i][b+j][1-side]+=C[aa][i]*C[bb][j]%div*ans[a][b][side]%div;
              if(ans[a+i][b+j][1-side]>=div)
                ans[a+i][b+j][1-side]-=div;
              t++;
              que[t][0]=a+i;
              que[t][1]=b+j;
              que[t][2]=1-side;
            } else if  (p[a+i][b+j][1-side]==nowp+1){
              ans[a+i][b+j][1-side]+=C[aa][i]*C[bb][j]%div*ans[a][b][side]%div;
              if(ans[a+i][b+j][1-side]>=div)
                ans[a+i][b+j][1-side]-=div;
            }
          }
        }
      }
    }
    ii++;
  }
}

void make(int a,int b,int side){
  if(checked[a][b][side])
    return;
  if(de){
    printf("%d %d %d\n",a,b,side);
  }
  checked[a][b][side]=1;
  checking[a][b][side]=1;
  p[a][b][side]=-1;
  int i,j,nowans=-1;
  if(side==0){
    for(i=0;i<=a;i++){
      if(i>m)
        break;
      for(j=0;j<=b;j++){
        if(i+j>0&&i+2*j<=m){
          if(checking[a-i][b-j][1-side])
            continue;
          make(a-i,b-j,1-side);
          if(p[a-i][b-j][1-side]>-1){
            if(nowans<0||nowans>p[a-i][b-j][1-side])
              nowans=p[a-i][b-j][1-side];
          }
        }
      }
    }
    if(nowans<0){
      checking[a][b][side]=0;
      return;
    }
    p[a][b][side]=nowans+1;
    for(i=0;i<=a;i++){
      if(i>m)
        break;
      for(j=0;j<=b;j++){
        if(i+j>0&&i+2*j<=m){
          if(checking[a-i][b-j][1-side])
            continue;
          if(p[a-i][b-j][1-side]==nowans){
            ans[a][b][side]+=ans[a-i][b-j][1-side]*C[a][i]%div*C[b][j]%div;
            ans[a][b][side]%=div;
          }
        }
      }
    }
  } else {
    if (a==0&&b==0){
      p[a][b][side]=0;
      ans[a][b][side]=1;

      checking[a][b][side]=0;
      return;
    }
    int aa=A-a,bb=B-b;
    for(i=0;i<=aa;i++){
      if(i>m)
        break;
      for(j=0;j<=bb;j++){
        if(i+j>0&&i+2*j<=m){
          if(checking[a+i][b+j][1-side])
            continue;
          make(a+i,b+j,1-side);
          if(p[a+i][b+j][1-side]>-1){
            if(nowans<0||nowans>p[a+i][b+j][1-side])
              nowans=p[a+i][b+j][1-side];
          }
        }
      }
    }
    if(nowans<0){
      checking[a][b][side]=0;
      return;
    }
    p[a][b][side]=nowans+1;
    for(i=0;i<=aa;i++){
      if(i>m)
        break;
      for(j=0;j<=bb;j++){
        if(i+j>0&&i+2*j<=m){
          if(checking[a+i][b+j][1-side])
            continue;
          if(p[a+i][b+j][1-side]==nowans){
            ans[a][b][side]+=ans[a+i][b+j][1-side]*C[aa][i]%div*C[bb][j]%div;
            ans[a][b][side]%=div;
          }
        }
      }
    }

  }
  if (de) {
    printf("- %d %d %d\n",a,b,side);
    printf("%d %d\n",p[a][b][side],int(ans[a][b][side]));
  }

  checking[a][b][side]=0;
}

int main(){
  prepare();
  scanf("%d %d",&n,&m);
  m/=50;
  for(i=1;i<=n;i++){
    scanf("%d",&j);
    if(j==50)
      A++;
    else
      B++;
  }
  make2();
  printf("%d\n",int(p[0][0][1])-1);
  printf("%I64d\n",ans[0][0][1]);
  return 0;
}
