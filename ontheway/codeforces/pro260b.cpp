#include<stdio.h>
#include<string>
#include<string.h>
#include<map>
using namespace std;
#define maxn 100100
char s[maxn];
map<string,int> p;
string ss="00-00-0000";

bool correct(string s){
  int a,b,c,i;
  if(sscanf(s.c_str(),"%d-%d-%d",&a,&b,&c)!=3)
    return 0;
  if(ss.size()!=s.size())
    return 0;
  for(i=0;i<s.size();i++){
    if(ss[i]=='-'){
      if(s[i]!='-')
        return 0;
    } else {
      if(s[i]<'0'||s[i]>'9')
        return 0;
    }
  }
  if(c<2013||c>2015)
    return 0;
  if(b<1||b>12)
    return 0;
  if(b<8){
    if(b&1){
      i=31;
    } else {
      i=30;
    }
  } else {
    if(b&1)
      i=30;
    else
      i=31;
  }
  if(b==2){
    i=28;
  }
  if(a<1||a>i)
    return 0;
  return 1;
}
int main(){
  scanf("%s",s);
  string now="";
  int i;

  for(i=0;s[i];i++){
    if(now.size()==ss.size())
      now=now.substr(1);
    now+=s[i];
    if(correct(now)){
      if(p.find(now)!=p.end())
        p[now]++;
      else
        p[now]=1;
    }
  }
  int ans=0;
  map<string,int>::iterator ii;
  for(ii=p.begin();ii!=p.end();ii++){
    if((ii->second)>ans){
      ans=ii->second;
      now=ii->first;
    }
  }
  printf("%s\n",now.c_str());
  return 0;
}
