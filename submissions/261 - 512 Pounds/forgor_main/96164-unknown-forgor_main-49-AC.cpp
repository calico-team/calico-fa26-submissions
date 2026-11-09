#include <functional>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <fstream>
#include <numeric>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <cctype>
#include <vector>
#include <string>
#include <bitset>
#include <cmath>
#include <queue>
#include <stdio.h>
#include <stack>
#include <ctime>
#include <list>
#include <map>
#include <set>
#include <assert.h>
#define REP(i,n) for(int i=0;i<n;i++)
#define TR(i,x) for(auto i=x.begin();i!=x.end();i++)
#define ALL(x) x.begin(),x.end()
#define SORT(x) sort(ALL(x))
#define CLEAR(x) memset(x,0,sizeof(x))
#define FILL(x,c) memset(x,c,sizeof(x))

using namespace std;

const double eps = 1e-8;

#define PB push_back
#define MP make_pair

typedef map<int,int> MII;
typedef map<string,int> MSI;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<long double> VD;
typedef pair<int,int> PII;
typedef long long int64;
typedef long long ll;
typedef unsigned int UI;
typedef long double LD;
typedef unsigned long long ULL;

const int N = 300007;

vector<int> edges[N];
int parent[N];

void dfs(int x, int par) {
  parent[x] = par;
  for (int to : edges[x]) {
    if (to != par) {
      dfs(to, x);
    }
  }
}

void solve(int caseId) {
  string s;
  cin >> s;
  int n;
  cin >> n;
  if (s == "FIRST") {
    for (int i = 0; i < n - 1; ++i)  {
      int u, v;
      scanf("%d%d", &u, &v);
      --u; --v;
      edges[u].PB(v);
      edges[v].PB(u);
    }
    dfs(0, -1);
    int res = 0;
    for (int i = 1; i < n; ++i) {
      res ^= parent[i];
    }
    parent[0] = res;
    for (int i = 0; i < n; ++i) {
      if (i) cout << " ";
      cout << parent[i];
    }
    cout << endl;
  } else {
    assert(s == "SECOND");
    vector<int> a(n);
    REP(i, n) scanf("%d", &a[i]);
    int at = -1;
    REP(i, n) if (a[i] == -1) {
      at = i;
      break;
    }
    if (at == -1) while (1);
    if (at != 0) {
      a[at] = 0;
      for (int i = 0; i < n; ++i) {
        if (i != at) {
          a[at] ^= a[i];
        }
      }
    }
    for (int i = 1; i < n; ++i) {
      cout << i + 1 << " " << a[i] + 1 << endl;
    }
  }
}

int main() {
  int cases = 1;
  // cin >> cases;
  for (int i = 1; i <= cases; ++i) {
    solve(i);
  }
  return 0;
}