#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;

/** for blitz */
// ifstream cin("input.txt");
// ofstream cout("output.txt");

const ll MOD = 999983;

void dfs(int cur, int parent, vi &p, vector<vi> &adj) {
    p[cur] = parent;
    for (auto v: adj[cur]) {
        if (v == parent) continue;
        dfs(v, cur, p, adj);
    } 
}

void sol1() {
    int n;
    cin >> n;
    vector<vi> adj(n+1);
    rep(i, 0, n-1) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vi p(n+1);
    dfs(1, 0, p, adj);

    rep(i, 2, n+1) {
        p[1] += p[i];
        p[1] %= MOD;
    }

    rep(i, 1, n+1) cout << p[i] << " ";
    cout << endl;
}

void sol2() {
    int n;
    cin >> n;

    vi a(n+1);
    rep(i, 1, n+1) cin >> a[i];

    if (a[1] != -1) {
        int idx = 0;
        rep(i, 2, n+1) {
            if (a[i] == -1) {
                idx = i;
                break;
            }
        }

        a[idx] = a[1];
        rep(i, 2, n+1) {
            if (i == idx) continue;
            a[idx] += MOD - a[i];
            a[idx] %= MOD;
        }
    }

    rep(i, 2, n+1) {
        cout << i << " " << a[i] << endl;
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    cin >> s;
    if (s == "FIRST") {
        sol1();
    } else {
        sol2();
    }
}