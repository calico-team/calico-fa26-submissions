#include <bits/stdc++.h>
using namespace std;

template<typename T> using min_pq = std::priority_queue<T, std::vector<T>, std::greater<T>>; //min_pq is a priority queue with minimum top
using ll = long long;

//macros
#define add push_back
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
//#define f first
//#define s second
#define trav(a,x) for (auto& a: x)
#define int long long //automatically makes ints into long longs to avoid overflow. comment if memory is an issue.
#define double long double

//const ll mod = 998244353; //if using a constant mod, define here

// binary exponentiation (computes x^target % modulus in O(log(target)) time), takes long long arguments (target must be < 2^30 ~ 10^9)
static ll binexp(ll x, ll modulus, ll target) {
  vector<ll> bin (30);
  int index = 29;
  while(target > 0) {
    bin[index] = (int) target%2;
    target/=2;
    index--;
  }
  index = 0;
  ll ret = 1;
  while(index < 30) {
    ret *= ret;
    ret %= modulus;
    if(bin[index] == 1) {
      ret *= x;
      ret %= modulus;
    }
    index++;
  }
  return ret;
}

// inverse (computes x^-1 mod modulus in O(log(modulus)) time), depends on binexp
static ll inv(ll x, ll modulus) {
  return binexp(x, modulus, modulus - 2);
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  //freopen("input.txt" , "r" , stdin);
  //freopen("output.txt" , "w", stdout);
    
  string run;
  cin >> run;

  if(run[0] == 'F') {
    int n;
    cin >> n;

    vector<int> deg (n);
    vector<vector<int>> edges (n, vector<int> (0));
    for(int i = 0; i < n - 1; i++) {
      int u, v;
      cin >> u >> v;
      u--; v--;
      edges[u].push_back(v);
      edges[v].push_back(u);
      deg[u]++; deg[v]++;
    }
    
    vector<int> parent (n);
    vector<int> q; q.push_back(0);
    vector<bool> visited (n); visited[0] = true;
    int index = 0;
    while(index < q.size()) {
      int node = q[index];
      for(int i = 0; i < edges[node].size(); i++) {
        int child = edges[node][i];
        if(!visited[child]) {
          visited[child] = true;
          parent[child] = node;
          q.push_back(child);
        }
      }
      index++;
    }

    int sum = 0;
    for(int i = 0; i < n; i++) {
      sum += parent[i];
      sum %= n;
    }

    cout << sum;
    for(int i = 1; i < n; i++) {
      cout << " " << parent[i];
    }
    cout << "\n"; cout.flush();
  } else {
    int n;
    cin >> n;
    vector<int> arr (n);
    for(int i = 0; i < n; i++) {
      cin >> arr[i];
    }

    if(arr[0] != -1) {
      int index = 0;
      int sum = 0;
      for(int i = 1; i < n; i++) {
        if(arr[i] != -1) {
          sum += arr[i];
          sum %= n;
        } else {
          index = i;
        }
      }
      int temp = arr[0] - sum;
      temp %= n;
      if(temp < 0) {temp += n;}
      arr[index] = temp;
    }
    
    for(int i = 1; i < n; i++) {
      cout << (i + 1) << " " << (arr[i] + 1) << "\n";
    }

    cout.flush();
  }
}