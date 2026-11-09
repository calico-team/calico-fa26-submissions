#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <cmath>
#include <numeric>
#include <queue>
#include <stack>
#include <iomanip>
#include <array>
#include <functional>
#include <bitset>
using namespace std;

void baseIO(string s = "") {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    if (s.size()) {
        freopen((s + ".in").c_str(), "r", stdin);
        freopen((s + ".out").c_str(), "w", stdout);
    }
}

int subcount = 376;

#define ll long long
#define db long double
#define all(x) (x).begin(), (x).end()

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }

    vector<vector<int>> adj(n);
    for (int i = 0; i < n; i++) {
        if (p[i] == 0) continue;
        adj[p[i] - 1].push_back(i);
    }

    priority_queue<pair<int, int>> pq;
    for (int i = 0; i < n; i++) {
        if (p[i] == 0) {
            pq.push({adj[i].size(), i});
        }
    }

    int ans = 0;
    while (m--) {
        vector<int> nc;
        for (int i = 0; i < k && !pq.empty(); i++) {
            auto [cnt, j] = pq.top();
            pq.pop();

            nc.push_back(j);
            ans++;
        }

        for (int x : nc) {
            for (int nxt : adj[x]) {
                pq.push({adj[nxt].size(), nxt});
            }
        }
    }

    cout << ans;
}

signed main() {
    baseIO();

    int t;
    cin >> t;
    while (t--){
        solve(), cout << endl;
    }

    return 0;
}