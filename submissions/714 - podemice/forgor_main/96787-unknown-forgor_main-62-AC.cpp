#include <bits/stdc++.h>
using namespace std;

#define int long long
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define eb emplace_back
#define pb push_back
#define vc vector
#define fs first
#define sd second

typedef pair<int, int> pii;
typedef vector<int> vi;

void dfs(int cur, int pa, vc<vi>& e, vi& parents) {
    parents[cur] = pa;
    for (auto &itr : e[cur]) {
        if (itr == pa) continue;
        dfs(itr, cur, e, parents);
    }
}

void phase1() {
    int n;
    cin >> n;
    vc<vi> e(n);
    rep(i, 0, n-1) {
        int u, v;
        cin >> u >> v; u--; v--;
        e[u].pb(v);
        e[v].pb(u);
    }
    vi pa(n, -1);
    dfs(0, -1, e, pa);
    int sum = 0;
    rep(i, 1, n) {
        cout << pa[i] << " ";
        sum += pa[i];
    }
    cout << sum % n << endl;
}

void phase2() {
    int n;
    cin >> n;
    vi pa(n, -1);
    int sum = 0, idx = -1;
    rep(i, 1, n) {
        int a;
        cin >> a;
        if (a != -1) {
            pa[i] = a;
            sum += a;
        } else {
            idx = i;
        }
    }

    int d;
    cin >> d;
    if (idx != -1) {
        // cout << d << " " << sum << endl;
        pa[idx] = (d - (sum%n) + n) % n;
    }

    rep(i, 1, n) {
        cout << (i+1) << " " << (pa[i]+1) << endl;
    }
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string s;
    cin >> s;
    if (s == "FIRST") phase1();
    else phase2();
}