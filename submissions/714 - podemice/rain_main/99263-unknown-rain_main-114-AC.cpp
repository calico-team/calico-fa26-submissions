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

void solve() {
    int n, k;
    cin >> n >> k;
    unordered_map<int, vi> ea, no;
    vi idE, idN;
    int tot = 0;
    rep(i, 0, n) {
        int x, y, z;
        char c;
        cin >> x >> y >> z >> c;
        int id = x + y;
        if (c == 'E') {
            if (ea.count(id) == 0) {
                ea.insert({id, vi()});
                idE.pb(id);
            }
            ea[id].pb(x);
        } else {
            if (no.count(id) == 0) {
                no.insert({id, vi()});
                idN.pb(id);
            }
            no[id].pb(y);
        }
        
        tot += k;
    }

    rep(i, 0, sz(idE)) {
        sort(all(ea[idE[i]]));
        reverse(all(ea[idE[i]]));
    }
    rep(i, 0, sz(idN)) {
        sort(all(no[idN[i]]));
        reverse(all(no[idN[i]]));
    }

    // x + y = id
    rep(i, 0, sz(idE)) {
        int id = idE[i];
        if (no.count(id) == 0) continue;
        for (auto &x : ea[id]) {
            // <= y
            auto lo = lower_bound(all(no[id]), id - x, [](int x, int y) { return x > y; });
            // < y - k + 1
            auto hi = upper_bound(all(no[id]), id - x - k + 1, [](int x, int y) { return x > y; });
            tot -= (hi - lo);
        }
    }
    cout << tot << endl;
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t; cin >> t;
    while (t--) solve();
}