#pragma GCC optimize("O3")
#pragma GCC optimization("Ofast,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAX = 1e18;
const ll MOD = 1e9 + 7;
bool testcases = true;

void solve() {
    ll n, m, q; cin >> n >> m >> q;
    bool swapped = false;
    if (m < n) {
        swap(n, m);
        swapped = true;
    }
    vector<array<ll, 3>> queries;
    vector<vector<int>> nxt(n, vector<int>(m+1));
    vector<vector<ll>> arr(n, vector<ll>(m, 0));
    for (int i = 0; i < n; i++)iota(nxt[i].begin(), nxt[i].end(), 0);
    for (int i = 0; i < q; i++) {
        ll x, y, p; cin >> x >> y >> p;
        if (swapped) swap(x, y);
        queries.push_back({x, y, p});
    }
    for (int _ = q-1; _ >= 0; _--) {
        auto [x, y, p] = queries[_];
        for (ll i = 0; i < n; i++) {
            if (abs(x-i) <= p) {
                ll d = sqrt(p*p-(x-i)*(x-i));
                int y1 = max(y-d, 0LL), y2 = min(y+d, m-1);
                if (d >= 0) {
                    int idx = y1;
                    while (idx <= y2) {
                        if (nxt[i][idx] != idx) {
                            int j = idx;
                            while (nxt[i][j] != j) j = nxt[i][j];
                            while (nxt[i][idx] != idx) {
                                int tmp = nxt[i][idx];
                                nxt[i][idx] = j;
                                idx = tmp;
                            }
                            idx = j;
                            continue;
                        }
                        arr[i][idx] = p*p-(x-i)*(x-i)-(y-idx)*(y-idx)+1;
                        int j = idx+1;
                        while (nxt[i][j] != j) j = nxt[i][j];
                        nxt[i][idx] = j;
                        idx = j;
                    }
                }
            }
        }
    }
    if (swapped) {
        for (int j = 0; j < m; j++) {
            for (int i = 0; i < n; i++)
                cout << arr[i][j] << ' ';
            cout << '\n';
        }
    }
    else {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
                cout << arr[i][j] << ' ';
            cout << '\n';
        }
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t = 1;
    if (testcases) cin >> t;
    for (int i = 1; i <= t; i++) solve();
    return 0;
}