
#include <bits/stdc++.h>
using namespace std;

#define abysr ios_base::sync_with_stdio(0); cin.tie(0);
#define ll long long
#define vll vector<long long>
#define endl "\n"

int main() {

    abysr

    string phase;
    cin >> phase;

    if (phase == "FIRST") {
        ll n;
        cin >> n;

        vector<vll> adj(n + 1);

        for (int i = 0; i < n - 1; i++) {
            ll u, v;
            cin >> u >> v;

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vll par(n + 1, 0);

        queue<ll> q;
        q.push(1);
        par[1] = -1;

        while (!q.empty()) {
            ll curr = q.front();
            q.pop();

            for (ll v : adj[curr]) {
                if (par[v] == 0) {
                    par[v] = curr;
                    q.push(v);
                }
            }
        }

        ll xsum = 0;

        for (int i = 2; i <= n; i++) {
            xsum ^= par[i];
        }

        for (int i = 1; i <= n; i++) {
            if (i == 1) {
                cout << 500000 + xsum;
            } else {
                cout << par[i];
            }

            cout << (i == n ? endl : " ");
        }
    }

    else if (phase == "SECOND") {
        ll n;
        cin >> n;

        vll a(n + 1);

        ll root = -1;
        ll mis = -1;

        for (int i = 1; i <= n; i++) {
            cin >> a[i];

            if (a[i] >= 500000) {
                root = i;
            }

            if (a[i] == -1) {
                mis = i;
            }
        }

        if (root == -1) {
            root = mis;

            for (int i = 1; i <= n; i++) {
                if (i != root) {
                    cout << i << " " << a[i] << endl;
                }
            }
        }

        else {
            ll cxor = 0;

            for (int i = 1; i <= n; i++) {
                if (i != root && i != mis) {
                    cxor ^= a[i];
                }
            }

            ll txor = a[root] - 500000;
            ll mis_par = txor ^ cxor;

            for (int i = 1; i <= n; i++) {
                if (i == root) continue;

                if (i == mis) {
                    cout << i << " " << mis_par << endl;
                } else {
                    cout << i << " " << a[i] << endl;
                }
            }
        }
    }

    return 0;
}
