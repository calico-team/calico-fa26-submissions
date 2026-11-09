#include<bits/stdc++.h>
using namespace std;
void solve1() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for(int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> a(n + 1, 0);
    vector<int> q;
    q.reserve(n);
    q.push_back(1);
    int sum = 0;
    for(int head = 0; head < (int)q.size(); ++head) {
        int u = q[head];
        for(int v : adj[u]) {
            if(v != 1 && a[v] == 0) {
                a[v] = u;
                sum ^= u;
                q.push_back(v);
            }
        }
    }
    a[1] = sum;
    for(int i = 1; i <= n; ++i) cout << a[i] << (i == n ? "" : " ");
    cout << "\n";
}
void solve2() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    int missing_idx = -1,sum2 = 0;
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
        if(a[i] == -1) missing_idx = i;
        else sum2 ^= a[i];
    }
    if(missing_idx != -1) a[missing_idx] = sum2;
    for(int i = 2; i <= n; ++i) {
        cout << i << " " << a[i] << "\n";
    }
}

int main() {
    string y;
    if(cin >> y) {
        if(y == "FIRST") solve1();
        else solve2();
    }
    return 0;
}