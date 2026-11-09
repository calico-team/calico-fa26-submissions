#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back

int main() {
    string input_phase; cin >> input_phase;
	ll n; cin >> n;

    if (input_phase == "FIRST") {
        vector<vector<ll>> adj(n + 1);
        for (ll i = 0; i < n - 1; i ++) {
            ll u, v; cin >> u >> v;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        vector<ll> p(n + 1, -1);
        p[1] = 0;
        queue<ll> q;
        q.push(1);

        while (!q.empty()) {
            ll c = q.front(); q.pop();
            for (ll a : adj[c]) {
                if (p[a] == -1) {
                    p[a] = c; q.push(a);
                }
            }
        }
        ll s = 0;
        for (ll i = 2; i <= n; i++) {
            s ^= p[i];
        }

        cout << s;
        for (ll i = 2; i <= n; i++) {
            cout << " " << p[i];
        }
        cout << '\n';
    } else {
        vector<ll> a(n + 1);
        for (ll i = 1; i <= n; i++) {
            cin >> a[i];
        }
        if (a[1] != -1) {
            ll s = a[1];
            ll x = -1;

            for (ll i = 2; i <= n; i++) {
                if (a[i] == -1) {
                    x = i;
                } else {
                    s ^= a[i];
                }
            }
            a[x] = s;
        }
        for (ll i = 2; i <= n; i++) {
            cout << i << " " << a[i] << '\n';
        }
    }
}
