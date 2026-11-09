#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <bit>
#include <map>
#include <set>
#include <deque>
using namespace std;
using ull = unsigned long long;

vector<vector<int>> adj; 
vector<int> a;

void tour(int node, int parent) {
    a[node] = parent;
    for (int child : adj[node]) {
        if (child == parent) continue;
        tour(child, node);
    }
}

void solve1() {
    int n;
    cin >> n;
    adj.resize(n, vector<int>());
    for (int i = 0; i < n - 1; i++) {
        int v, u;
        cin >> v >> u;
        v--; u--;
        adj[v].push_back(u);
        adj[u].push_back(v);
    }

    a.resize(n, 0);
    tour(0, -1);
    int sum = 0;
    for (int i = 1; i < n; i++) {
        sum += a[i];
    }
    a[0] = sum % 1000001;
    for (int i = 0; i < n; i++) {
        cout << a[i] << ' ';
    }
}

void solve2() {
    int n;
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int idx = 0;
    int sum = 0;
    a[0] = -a[0];
    for (int i = 0; i < n; i++) {
        if (a[i] == -1) {
            idx = i;
            continue;
        }
        sum += a[i];
    }
    a[idx] = (-sum) % 1000001;
    for (int i = 1; i < n; i++) {
        cout << (i + 1) << ' ' << (a[i] + 1) << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    if (s.find("FIRST") != string::npos) solve1();
    else solve2();
}