#include <bits/stdc++.h>

using namespace std;

#define int long long

void encode() {
  int n;
  cin >> n;
  vector<vector<int>> edges(n);
  for (int i = 1; i < n; ++i) {
    int u, v;
    cin >> u >> v;
    edges[u - 1].push_back(v - 1);
    edges[v - 1].push_back(u - 1);
  }
  vector<int> parent(n, -1);
  parent[0] = 0;
  queue<int> q;
  q.push(0);
  while (!q.empty()) {
    int node = q.front();
    q.pop();
    for (int neighbor : edges[node]) {
      if (parent[neighbor] == -1) {
        parent[neighbor] = node;
        q.push(neighbor);
      }
    }
  }
  int x = 0;
  for (int i = 1; i < n; ++i) {
    x ^= parent[i] + 1;
  }
  cout << x << " ";
  for (int i = 1; i < n; ++i) {
    cout << parent[i] + 1 << " ";
  }
  cout << endl;
}

void decode() {
  int n;
  cin >> n;
  vector<int> parent(n);
  int x;
  cin >> x;
  for (int i = 1; i < n; ++i) {
    cin >> parent[i];
    if (parent[i] != -1) {
      x ^= parent[i];
    }
  }
  for (int i = 1; i < n; ++i) {
    if (parent[i] == -1) {
      parent[i] = x;
      break;
    }
  }
  for (int i = 1; i < n; ++i) {
    cout << i + 1 << " " << parent[i] << endl;
  }
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  string s;
  cin >> s;
  if (s == "FIRST") {
    encode();
  } else {
    decode();
  }
}