// Nov 09 2026, 08:20

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fastIO cin.tie(NULL); ios::sync_with_stdio(NULL)
#define fi first
#define se second

vector<vector<int>> adjlist;
vector<int> par;
void dfs(int u = 0, int p = -1) {
    par[u] = p;
    for(auto v : adjlist[u]) if(v != p) {
        dfs(v, u);
    }
}

int main() {
    fastIO;

    string s; cin >> s;
    if(s == "FIRST") {
        ll n; cin >> n;
        adjlist = vector<vector<int>>(n);
        par = vector<int>(n);
        for(int i = 1; i < n; i++) {
            int a, b; cin >> a >> b; a--, b--;
            adjlist[a].push_back(b);
            adjlist[b].push_back(a);
        }

        dfs();
        ll parsum = 0;
        for(int i = 1; i < n; i++) {
            cout << par[i] << ' ';
            parsum = (parsum + par[i]) % n;
        }

        cout << parsum << '\n';
    } else {
        ll n; cin >> n;
        vector<ll> a(n); for(auto &i : a) cin >> i;

        if(a[n-1] != -1) {
            ll allsum = a[n-1];

            for(int i = 0; i < n - 1; i++) if(a[i] != -1) allsum = (allsum + n - a[i]) % n;
            allsum = (allsum + n) % n;
            for(int i = 0; i < n - 1; i++) if(a[i] == -1) a[i] = allsum;
        }

        for(int i = 0; i < n - 1; i++) {
            cout << i + 2 << ' ' << a[i] + 1 << '\n';
        }
    }

    return 0;
}