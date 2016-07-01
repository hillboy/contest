#include<iostream>
#include<string.h>
#include<algorithm>
#include<map>
#include<set>
#include<vector>
#include<map>
#include<string>
using namespace std;

#define forlr(x,l,r) for(x=l;x<(int)r;++x)
#define for1(x,y) forlr(x,0,y)
#define forn(x) for1(x,n)

int i,j,n,m;

string s;

int main() {
  ios_base::sync_with_stdio(false);
  cin  >> s;
  cout << s;
  std::reverse(s.begin(), s.end());
  cout << s << endl;
  return 0;
}
