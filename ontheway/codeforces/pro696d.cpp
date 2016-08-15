#include <iostream>
#include <string.h>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include <map>
#include <string>
#include <math.h>
using namespace std;

#define forlr(i,l,r) for(i=l;i<r;i++)
#define forrl(i,r,l) for(i=r-1;i>=l;i--)
#define for0r(i,r) forlr(i,0,r)

#define forltr(i,l,r) for(i=l;i<=r;i++)
#define for1tr(i,r) forltr(i,1,r)
#define forrtl(i,r,l) for(i=r;i>=l;i--)

#define forcnt(n) for(int cnt=n; cnt; cnt--)


typedef long long int LD;

#define maxn 300

char s[maxn][maxn];

int ga[maxn];

char ss[maxn];

int s_num;

LD m;

int i,j,n;


struct Trie {
  static int total_num;
  int num = -1;
  LD gain;
  Trie* children[26];
  Trie* back;
  void add(char* s);
  void get_gain(int depth) {
    int i,j,r,l;
    for0r(i,26) {
      if(children[i]) {
        ss[depth]=i+'a';
        for0r(j, s_num) {
          l=strlen(s[j]);
          if(l<= depth+1) {
            for1tr(r,l) {
              if(s[j][l-r] != ss[depth+1-r]) {
                break;
              }
            }
            if(r==l) {
              children[i]->gain += ga[j];
            }
          }
        }
        children[i]->get_gain(depth+1);
      }
    }
  }
} p[maxn*maxn];

void Trie::add(char* s) {
  if(num<0) {
    num = total_num++;
  }
  if(!(*s)) {
    return;
  }
  int a = (*s) - 'a';
  if(!children[a]) {
    children[a] = &p[total_num];
  }
  children[a]->add(s+1);
}

int Trie::total_num = 0;





int main() {
  ios_base::sync_with_stdio(false);
  std::cin >> s_num >> m;
  for0r(i, s_num) {
    cin >> ga[i];
  }
  for0r(i, s_num) {
    cin >> s[i];
    p[0].add(s[i]);
  }
  p[0].get_gain(0);

  return 0;
}
