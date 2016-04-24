#include<stdio.h>
#include<string.h>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

#define maxn 100010

int i,j,n,m;

vector<int> all_events[maxn];

int et;


map<int, int > events;


int qry[maxn][3];

struct ConstTree {

  ConstTree(const vector<int>& a) : org(a){
    leaf_name.clear();
    int k = make(0, 0, a.size()-1);
    sum.resize(k+1);
//    fill(sum.begin(), sum.end(), 0);
  };

  
  const vector<int>& org;

  vector<int> sum;

  map<int,int> leaf_name;

  int make(int a, int l, int r) {
    if(l==r) {
      leaf_name[org[l]]=a;
      return a;
    }
    int mid=(l+r)/2;
    return max(make(a*2+1,l,mid), make(a*2+2,mid+1,r));
  }

  void update(int a, int now) {
    a=leaf_name[a];
    while(1) {
      sum[a]+=now;
      if(a==0)
        break;
      a=(a-1)/2;
    }
  }

  int findans(int a, int l, int r, int pos) {
    if(pos==r) {
      return sum[a];
    }
    int mid=(l+r)/2;
    if(mid>=pos) {
      return findans(a*2+1, l, mid, pos);
    } else {
      return findans(a*2+2, mid+1, r, pos) + sum[a*2+1];
    }
  }

  int getans(int a) {
    int k = std::lower_bound(org.begin(), org.end(), a) - org.begin();
    return findans(0, 0, org.size() - 1, k);
  }
};

map<int, ConstTree*> p;

inline void prepare() {
  for(auto i : events) {
    j=i.second;
    sort(all_events[j].begin(), all_events[j].end());
    p[i.first] = new ConstTree(all_events[j]);
  }
}


int main() {
  {
    scanf("%d", &n);
    for(i=1;i<=n;i++) {
      scanf("%d %d %d", &qry[i][0], &qry[i][1], &qry[i][2]);
      if(events.count(qry[i][2])==0) {
        events[qry[i][2]]=et++;
      }
      j=events[qry[i][2]];
      all_events[j].push_back(qry[i][1]);
    }
  }
  /*
  n=100000;
  for(i=1;i<=n;i++) {
    qry[i][0]=1;
    qry[i][1]=i;
    qry[i][2]=i;
    events[qry[i][2]].push_back(qry[i][1]);
  }
  */
  prepare();
  for(i=1;i<=n;i++) {
    if(qry[i][0]==1) {
      p[qry[i][2]]->update(qry[i][1],1);
    }
    if(qry[i][0]==2) {
      p[qry[i][2]]->update(qry[i][1],-1);
    }
    if(qry[i][0]==3) {
      printf("%d\n", p[qry[i][2]]->getans(qry[i][1]));
    }
  }

  return 0;
}
