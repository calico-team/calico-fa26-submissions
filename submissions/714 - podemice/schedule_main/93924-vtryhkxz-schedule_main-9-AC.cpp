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
    int n, m, k;
    cin >> n >> m >> k;
    vi prereq(n, -1);
    vc<vi> e(n);
    rep(i, 0, n) {
        int p;
        cin >> p;
        if (p != 0) {
            prereq[i] = p-1;
            e[p-1].pb(i);
        }
    }

    queue<int> q;
    rep(i, 0, n) {
        if (prereq[i] == -1) {
            q.push(i);
        }
    }

    int tot = 0, overflow = 0;
    rep(i, 0, m) {
        int round = sz(q);
        rep(j, 0, round) {
            for (auto &itr : e[q.front()]) q.push(itr);
            q.pop();
        }
        tot += min(round+overflow, k);
        overflow += round-min(round+overflow, k);
    }
    cout << tot << endl;
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t; cin >> t;
    while (t--) solve();
}