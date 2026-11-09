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
    vector<vector<set<int>>> prios(n, vector<set<int>>(m+1));
    for (int i = 0; i < q; i++) {
        ll x, y, p; cin >> x >> y >> p;
        if (swapped) swap(x, y);
        queries.push_back({x, y, p});
        for (ll j = 0; j < n; j++) {
            if (abs(x-j) <= p) {
                ll d = sqrt(p*p-(x-j)*(x-j)), y1 = max(y-d, 0LL), y2 = min(y+d+1, m);
                if (d >= 0) {
                    prios[j][y1].insert(i);
                    prios[j][y2].insert(i);
                }
            }
        }
    }
    vector<vector<ll>> arr(n, vector<ll>(m, 0));
    for (int i = 0; i < n; i++) {
        set<ll> vs;
        for (int j = 0; j < m; j++) {
            for (auto v : prios[i][j]) {
                if (vs.count(v)) vs.erase(v);
                else vs.insert(v);
            }
            if (!vs.empty()) {
                int idx = *prev(vs.end());
                ll x = queries[idx][0], y = queries[idx][1], p = queries[idx][2];
                arr[i][j] = p*p - ((x-i)*(x-i)+(y-j)*(y-j)) + 1;
            }
        }
    }
    if (swapped) {
        for (int j = 0; j < m; j++) {
            for (int i = 0; i < n; i++) {
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }
    }
    else {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << arr[i][j] << " ";
            }
            cout << endl;
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