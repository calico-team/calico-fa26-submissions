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

const int N = 10000007;
const int M = 30;

struct Trie {
  int lastNode;
  int ch[N][2];
  int count[N];

  void clear() {
    ch[0][0] = ch[0][1] = -1;
    count[0] = 0;
    lastNode = 1;
  }

  int nextNode() {
    ch[lastNode][0] = ch[lastNode][1] = -1;
    count[lastNode] = 0;
    return lastNode++;
  }

  void insert(int x, int val) {
    int cur = 0;
    count[cur] += val;
    for (int i = M - 1; i >= 0; --i) {
      int bit = (x >> i) & 1;
      if (ch[cur][bit] == -1) {
        ch[cur][bit] = nextNode();
      }
      cur = ch[cur][bit];
      count[cur] += val;
    }
  }

  int getMaxXor(int x) {
    int ret = 0;
    int cur = 0;
    for (int i = M - 1; i >= 0; --i) {
      int bit = (x >> i) & 1;
      assert(ch[cur][bit] != -1 || ch[cur][1 - bit] != -1);
      if (ch[cur][1 - bit] != -1 && count[ch[cur][1 - bit]] > 0) {
        ret ^= 1 << i;
        cur = ch[cur][1 - bit];
      } else {
        assert(count[ch[cur][bit]] > 0);
        cur = ch[cur][bit];
      }
    }
    return ret;
  }
} cycleTrie, pathTrie;


vector<int> undEdges[N];
bool vis[N];
vector<int> component;

void dfs(int x) {
  vis[x] = true;
  component.push_back(x);
  for (int to : undEdges[x]) {
    if (!vis[to]) {
      dfs(to);
    }
  }
}

int a[N], v[N];
int ans[N];

bool inCycle[N];
bool inStack[N];
vector<int> revEdge[N];
vector<int> st;
vector<int> prefix;
vector<int> cycle;

void findCycle(int x) {
  inStack[x] = true;
  st.push_back(x);
  if (!inStack[a[x]]) {
    findCycle(a[x]);
  } else {
    for (int i = st.size() - 1; i >= 0; --i) {
      cycle.push_back(st[i]);
      if (st[i] == a[x]) break;
    }
    reverse(cycle.begin(), cycle.end());
  }
  inStack[x] = false;
}

void dfs2(int x, int cycleBase, int pathCur) {
  pathCur ^= v[x];
  if (!inCycle[x]) {
    int pathMax = pathTrie.getMaxXor(pathCur);
    int cycleMax = cycleTrie.getMaxXor(pathCur ^ cycleBase);
    // cerr << "node " << x << ": pathMax=" << pathMax << ", cycleMax=" << cycleMax << endl;
    ans[x] = max(pathMax, cycleMax);
  }
  pathTrie.insert(pathCur, 1);
  for (int to : revEdge[x]) {
    if (!inCycle[to]) {
      dfs2(to, cycleBase, pathCur);
    }
  }
  pathTrie.insert(pathCur, -1);
}

void process(const vector<int>& nodes) {
  // cerr << "Component:";
  // for (int v : nodes) {
  //   cerr << " " << v;
  // }
  // cerr << endl;

  st.clear();
  cycle.clear();
  findCycle(nodes[0]);
  // cerr << "Cycle length: " << cycle.size() << endl;
  for (int v : cycle) {
    assert(!inCycle[v]);
    inCycle[v] = true;
  }

  prefix.clear();
  int cur = 0;
  for (int i = 0; i < cycle.size() * 2; ++i) {
    cur ^= v[cycle[i % cycle.size()]];
    prefix.push_back(cur);
  }

  cycleTrie.clear();
  for (int i = 0; i < cycle.size() * 2; ++i) {
    cycleTrie.insert(prefix[i], 1);
  }

  cur = 0;
  for (int i = 0; i < cycle.size(); ++i) {
    pathTrie.clear();
    dfs2(cycle[i], cur ^ v[cycle[i]], 0);

    ans[cycle[i]] = cycleTrie.getMaxXor(cur);
    // cerr << "cycle node " << cycle[i] << ": cycleMax=" << ans[cycle[i]] << endl;

    cur ^= v[cycle[i]];
  }

  for (int v : cycle) {
    inCycle[v] = false;
  }
}

void solve(int caseId) {
  int n;
  cin >> n;
  REP(i, n) {
    vis[i] = false;
    ans[i] = 0;
    undEdges[i].clear();
    revEdge[i].clear();
  }
  REP(i, n) {
    scanf("%d", &a[i]);
    --a[i];

    undEdges[i].PB(a[i]);
    undEdges[a[i]].PB(i);
    revEdge[a[i]].PB(i);
  }
  REP(i, n) scanf("%d", &v[i]);

  REP(i, n) {
    if (!vis[i]) {
      component.clear();
      dfs(i);
      process(component);
    }
  }

  REP(i, n) {
    if (i) cout << " ";
    cout << ans[i];
  }
  cout << endl;
}

int main() {
  int cases = 1;
  cin >> cases;
  for (int i = 1; i <= cases; ++i) {
    solve(i);
  }
  return 0;
}