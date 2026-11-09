#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <bit>
#include <map>
#include <set>
#include <deque>
using namespace std;
using ll = long long;

vector<vector<ll>> adj; 
vector<ll> a;

const ll MOD = 1000001;

void tour(ll node, ll parent) {
    a[node] = parent;
    for (ll child : adj[node]) {
        if (child == parent) continue;
        tour(child, node);
    }
}

void solve1() {
    ll n;
    cin >> n;
    adj.resize(n, vector<ll>());
    for (ll i = 0; i < n - 1; i++) {
        ll v, u;
        cin >> v >> u;
        v--; u--;
        adj[v].push_back(u);
        adj[u].push_back(v);
    }

    a.resize(n, 0);
    tour(0, -1);
    ll sum = 0;
    for (ll i = 1; i < n; i++) {
        sum += a[i];
    }
    a[0] = sum % 1000001;
    for (ll i = 0; i < n; i++) {
        cout << a[i] << ' ';
    }
}

void solve2() {
    ll n;
    cin >> n;
    a.resize(n);
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }
    ll idx = 0;
    ll sum = 0;
    a[0] = -a[0];
    for (ll i = 0; i < n; i++) {
        if (a[i] == -1) {
            idx = i;
            continue;
        }
        sum += a[i];
    }
    a[idx] = (((-sum) % MOD) + MOD) % MOD;
    for (ll i = 1; i < n; i++) {
        cout << (i + 1) << ' ' << (a[i] + 1) << '\n';
    }
}

ll main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    if (s.find("FIRST") != string::npos) solve1();
    else solve2();
}