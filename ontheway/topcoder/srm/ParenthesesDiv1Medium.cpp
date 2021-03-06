#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include<string.h>

using namespace std;
#define maxn 1000000

typedef pair<int,int> point;

point p[maxn];

int i,j,n,m;

int qq[maxn],t;

bool ll[3000], rr[3000];

int pp[maxn];

int num[maxn];


class ParenthesesDiv1Medium {
public:
	int minSwaps(string s, vector <int> L, vector <int> R) {
    m=L.size();
    n=0;
    t=0;
    for(i=0;i<m;i++) {
      memset(ll,0,sizeof(ll));
      memset(rr,0,sizeof(rr));
      for(j=0;j<m;j++) {
        if(!((L[j]>L[i] && R[j]<R[i]))) {
          if(L[j]>L[i] && L[j] <=R[i]) {
            ll[L[j]]=1;
            rr[L[j]-1]=1;
          }
          if(R[j]>=L[i] && R[j]<R[i]) {
            ll[R[j]+1]=1;
            rr[R[j]]=1;
          }
        }
      }
      ll[L[i]]=1;
      rr[R[i]]=1;
      t=0;
      for(j=0;j<(int)s.size();j++) {
        if(ll[j]&&rr[j])
          return -1;
        if(ll[j] || rr[j]) {
          qq[t++]=j;
        } 
      }

      for(j=0;j<t;j+=2) {
        p[n++]=make_pair(qq[j], qq[j+1]);
      }
    }
    j=0;
    int a=0,b=0;
    for(i=0;i<(int)s.size();i++) {
      if(s[i]=='(')
        a++;
      else
        b++;
    }

    printf("%d\n", n);
//    for(i=0;i<n;i++)
//      printf("%d %d\n", p[i].first, p[i].second);
    memset(pp,0,sizeof(pp));
    memset(num,0,sizeof(num));

    for(i=0;i<n;i++) {
      pp[p[i].first]=-1;
      pp[p[i].second]=1;
    }
    
    t=0;
    int ansa = 0, ansb=0;
    int len=0;
    for(i=0;i<(int)s.size();i++) {
      if(pp[i]==-1) {
        t++;
        num[t]=0;
      }
      if(t) {
        len++;
        if(s[i]=='(') {
          num[t]++;
        } else {
          if(num[t]) {
            num[t]--;
          } else  {
            ansa++;
            num[t]++;
          }
        }
        if(pp[i]==1) {
          if(num[t])
            ansb+=num[t];
          t--;
        }
      }
    }
    if(len/2 >  min(a,b))
      return -1;
    int ans = min(ansa,ansb);
    printf("%d %d\n", ansa, ansb);
    ans += max(ansa, ansb) - ans;

		return ans;
	}
};


// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
bool KawigiEdit_RunTest(int testNum, string p0, vector <int> p1, vector <int> p2, bool hasAnswer, int p3) {
	cout << "Test " << testNum << ": [" << "\"" << p0 << "\"" << "," << "{";
	for (int i = 0; int(p1.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << p1[i];
	}
	cout << "}" << "," << "{";
	for (int i = 0; int(p2.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << p2[i];
	}
	cout << "}";
	cout << "]" << endl;
	ParenthesesDiv1Medium *obj;
	int answer;
	obj = new ParenthesesDiv1Medium();
	clock_t startTime = clock();
	answer = obj->minSwaps(p0, p1, p2);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << p3 << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << answer << endl;
	if (hasAnswer) {
		res = answer == p3;
	}
	if (!res) {
		cout << "DOESN'T MATCH!!!!" << endl;
	} else if (double(endTime - startTime) / CLOCKS_PER_SEC >= 2) {
		cout << "FAIL the timeout" << endl;
		res = false;
	} else if (hasAnswer) {
		cout << "Match :-)" << endl;
	} else {
		cout << "OK, but is it right?" << endl;
	}
	cout << "" << endl;
	return res;
}
int main() {
	bool all_right;
	all_right = true;
	
	string p0;
	vector <int> p1;
	vector <int> p2;
	int p3;
	
	{
	// ----- test 0 -----
	p0 = ")(";
	int t1[] = {0,0,0,0};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	int t2[] = {1,1,1,1};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	p3 = 1;
	all_right = KawigiEdit_RunTest(0, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 1 -----
	p0 = "(())";
	int t1[] = {0,2};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	int t2[] = {1,3};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	p3 = 1;
	all_right = KawigiEdit_RunTest(1, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 2 -----
	p0 = "(((())";
	int t1[] = {0,2};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	int t2[] = {1,3};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	p3 = 2;
	all_right = KawigiEdit_RunTest(2, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 3 -----
	p0 = "(((((((((";
	int t1[] = {0,2};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	int t2[] = {1,3};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	p3 = -1;
	all_right = KawigiEdit_RunTest(3, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 4 -----
	p0 = "()()()()";
	int t1[] = {0,0,0,0,2,2,2,4,4,6};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	int t2[] = {1,3,5,7,3,5,7,5,7,7};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	p3 = 0;
	all_right = KawigiEdit_RunTest(4, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 5 -----
	p0 = ")()(()()((())()()()()()()))(()())()()()(";
	int t1[] = {3,5,17,25,35};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	int t2[] = {12,10,30,30,38};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	p3 = 3;
	all_right = KawigiEdit_RunTest(5, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	if (all_right) {
		cout << "You're a stud (at least on the example cases)!" << endl;
	} else {
		cout << "Some of the test cases had errors." << endl;
	}
	return 0;
}
// END KAWIGIEDIT TESTING
//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!
