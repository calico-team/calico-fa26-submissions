#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll next() {
    ll temp; cin >> temp; return temp;
}


vector<vector<int>> adj {{}};
vector<int> par {0};
vector<int> chi {0};
vector<bool> vis {false};

void dfs(int node) {
    if (vis[node]) { return; }
    vis[node] = true;
    for (int i : adj[node]) {
        if (vis[i]) { continue; }
        chi[node]++;
        par[i] = node;
        dfs(i);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string ss; cin >> ss;
    if (ss[0] == 'F') {
        int n = next(); adj = {{}}; par = {0}; chi = {0}; vis = {false};
        for (int i=0; i<n; i++) {
            adj.push_back({});
            par.push_back(0);
            chi.push_back(0);
            vis.push_back(false);
        }
        for (int i=0; i<n-1; i++) {
            int temp1 = next(), temp2 = next();
            adj[temp1].push_back(temp2);
            adj[temp2].push_back(temp1);
        }
        dfs(1);
        for (int i=1; i<=n; i++) {
            ll temp = 1000000 * par[i] + chi[i];
            cout << temp;
            if (i != n)
                cout << ' ';
        }
        cout << '\n';
    }
    else {
        int n = next(), ban = 0;
        vector<ll> chi1 {0};
        vector<ll> chi2(n+1,0);
        vector<ll> par {0};
        for (int i=0; i<n; i++) {
            ll temp = next();
            if (temp == -1) { ban = i+1; chi1.push_back(0); par.push_back(-1); continue;}
            chi1.push_back(temp % 1000000);
            par.push_back(temp / 1000000);
        }
        for (int i=1; i<=n; i++) {
            if (par[i] == -1) { continue; }
            chi2[par[i]]++;
        }
        int banp = 1;
        for (int i=1; i<=n; i++) {
            if (chi1[i] != chi2[i] && chi1[i] > chi2[i]) {
                par[ban] = i;
                banp = 2;
            }
        }
        bool work = (banp == 1);
        if (work) {
            for (int i=2; i<=n; i++) {
                cout << par[i] << ' ' << i << '\n';
            }
        }
        else {
            for (int i=2; i<=n; i++) {
                cout << par[i] << ' ' << i << '\n';
            }
        }
    }
    return 0;
}