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

LD cost[maxn][maxn];

void mul(LD a[maxn][maxn], LD b[maxn][maxn], LD c[maxn][maxn]) {
  int i,j,r;
  for0r(i,n) {
    for0r(j,n) {
      c[i][j]=-1;
    }
  }
  for0r(r,n) {
    for0r(i,n) if(a[i][r]>=0) {
      for0r(j,n) if(b[r][j]>=0) {
        if(a[i][r] + b[r][j] > c[i][j])
          c[i][j] = a[i][r] + b[r][j];
      }
    }
  }
}

void cp(LD a[maxn][maxn], LD b[maxn][maxn]) {
  int i,j;
  for0r(i,n) {
    for0r(j,n) {
      b[i][j]=a[i][j];
    }
  }
}

void output(LD a[maxn][maxn]) {
  int i,j;
  for0r(i,n) {
    for0r(j,n) {
      cout << a[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

void mypow(LD a[maxn][maxn], LD ans[maxn][maxn], LD nn) {
  LD tmp[maxn][maxn];
  bool fir = true;
  while(nn) {
    if(nn&1) {
      if(fir) {
        cp(a, ans);
        fir = false;
      } else {
        mul(ans, a, tmp);
        cp(tmp, ans);
      }
    }
    mul(a, a, tmp);
    cp(tmp, a);
    nn>>=1;
  }
}



struct Trie {
  static int total_num;
  static Trie* root;
  int letter;
  int num = -1;
  int gain;
  Trie* children[26];
  Trie* back;
  Trie* fa;
  Trie* jump[26];
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
            if(r==l+1) {
              children[i]->gain += ga[j];
            }
          }
        }
        children[i]->get_gain(depth+1);
      }
    }
  }
  Trie* get_back();
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
    children[a]->fa = this;
    children[a]->letter = a;
  }
  children[a]->add(s+1);
}

Trie* Trie::get_back() {
  if(back)
    return back;
  if(this==root) {
    return root;
  }
  if(this->fa == root) {
    this -> back = root;
  } else {
    Trie* a = fa->get_back();
    while(a!=root && !a->children[letter]) {
      a=a->get_back();
    }
    if (a->children[letter]) {
      back = (a->children[letter]);
    } else {
      back = root;
    }
  }
  int i;
  back->get_back();
  for0r(i,26) {
    if(!children[i]) {
      jump[i] = back->jump[i];
    } else {
      jump[i] = children[i];
    }
  }
  return back;
}

int Trie::total_num = 0;
Trie* Trie::root = nullptr;





int main() {
  ios_base::sync_with_stdio(false);
  std::cin >> s_num >> m;
  for0r(i, s_num) {
    cin >> ga[i];
  }
  Trie::root = &p[0];
  for0r(i, s_num) {
    cin >> s[i];
    Trie::root->add(s[i]);
  }
  Trie::root->get_gain(0);
  for0r(i, 26) {
    Trie::root->jump[i] = Trie::root->children[i];
  }
  n = Trie::total_num;
  for0r(i,n)
      for0r(j,n) {
        cost[i][j] = -1;
      }
  for0r(i, Trie::total_num) {
    p[i].get_back();
    for0r(j,26) {
      if(p[i].jump[j]) {
        if(cost[i][p[i].jump[j]->num]<0)
          cost[i][p[i].jump[j]->num] = 0;
        cost[i][p[i].jump[j]->num] += p[i].jump[j]->gain;
      }
    }
  }
  LD ans[maxn][maxn];
  mypow(cost, ans, m);
  LD ans_num = 0;
  for0r(i,n) {
    if(ans[0][i]>ans_num)
      ans_num = ans[0][i];
  }
  cout << ans_num << endl;
  return 0;
}
