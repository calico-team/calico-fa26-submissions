#include <bits/stdc++.h>
#define endl '\n'
#define pb push_back
#define ll long long
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())

using namespace std;

const ll MOD = 1e9 + 7;

// just keeping this here in case i need it later
ll gcd(ll a, ll b) {
    if(b == 0) return a;
    return gcd(a, b % a);
}
void fastio() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
ll pw(ll b, ll e) {
    ll r = 1;
    b %= MOD;
    if(b < 0) b += MOD;

    while(e) {
        if(e&1) r = r * b % MOD;
        b = b * b % MOD;
        e >>= 1;
    }

    return r;
}
int n, m, q;
vector<string> g;
vector<int> r1, c1, r2, c2;
vector<ll> ans;
const int INF = 1e9;

// check if cell is active
inline bool ok(int r, int c, int mo) {
    char ch = g[r][c];
    return ch == '.' || (ch == 'B' && mo == 0) || (ch == 'R' && mo == 1);
}
void dnc(int l, int r, vector<int>& qs) {
    if(qs.empty() || l > r) return;

    int mid = (l + r) / 2;
    int w = r - l + 1;
    int s_sz = w * n * 2;
    
    auto id = [&](int row, int c, int mo) {
        return ((c - l) * n + row) * 2 + mo;
    };
    vector<vector<int>> D(2 * n);
    vector<int> qq(s_sz);
    int dr[4] = {1, -1, 0, 0};
    int dc[4] = {0, 0, 1, -1};

    // run bfs
    for(int i = 0; i < n; i++) {
        for(int mo = 0; mo < 2; mo++) {
            int sidx = i * 2 + mo;
            if(!ok(i, mid, mo)) continue;
            
            vector<int>& d = D[sidx];
            d.assign(s_sz, INF);
            int head = 0, tail = 0;
            int s0 = id(i, mid, mo);
            d[s0] = 0;
            qq[tail++] = s0;

            while(head < tail) {
                int u = qq[head++];
                int mo2 = u & 1;
                int t = u >> 1;
                int row = t % n, c = t / n + l;
                int du = d[u];
                //4 firedctons
                for(int k = 0; k < 4; k++) {
                    int nr = row + dr[k], nc = c + dc[k];
                    if(nr < 0 || nr >= n || nc < l || nc > r) continue;
                    if(!ok(nr, nc, mo2)) continue;

                    int v = id(nr, nc, mo2);
                    if(d[v] == INF) {
                        d[v] = du + 1;
                        qq[tail++] = v;
                    }
                }
                if(g[row][c] == '.') {
                    int v = u ^ 1;
                    if(d[v] == INF) {
                        d[v] = du + 1;
                        qq[tail++] = v;
                    }
                }
            }
        }
    }
    // check queries
    vector<int> left_qs, right_qs;
    for(int qi : qs) {
        int ra = r1[qi], ca = c1[qi];
        int rb = r2[qi], cb = c2[qi];

        int a0 = id(ra, ca, 0);
        int b0 = ok(rb, cb, 0) ? id(rb, cb, 0) : -1;
        int b1 = ok(rb, cb, 1) ? id(rb, cb, 1) : -1;

        ll bb = ans[qi];
        for(int s = 0; s < 2 * n; s++) {
            if(D[s].empty()) continue;
            int da = D[s][a0];
            if(da >= INF) continue;

            int db = INF;
            if(b0 >= 0) db = min(db, D[s][b0]);
            if(b1 >= 0) db = min(db, D[s][b1]);
            if(db >= INF) continue;

            bb = min(bb, (ll)da + db);
        }
        ans[qi] = bb;
        // sure
        if(ca < mid && cb < mid) {
            left_qs.pb(qi);
        }
        else if(ca > mid && cb > mid) {
            right_qs.pb(qi);
        }
    }
    D.clear();
    D.shrink_to_fit();

    dnc(l, mid - 1, left_qs);
    dnc(mid + 1, r, right_qs);
}
void solve() {
    cin >> n >> m >> q;
    g.resize(n);
    for(int i = 0; i < n; i++) {
        cin >> g[i];
    }
    r1.resize(q); c1.resize(q); r2.resize(q); c2.resize(q);
    vector<ll> k_lim(q);
    ans.assign(q, (ll)4e18);
    for(int i = 0; i < q; i++) {
        cin >> r1[i] >> c1[i] >> r2[i] >> c2[i] >> k_lim[i];
    }
    vector<int> initial_qs(q);
    iota(all(initial_qs), 0);
    // kick off divide and conquer
    dnc(0, m - 1, initial_qs);
    for(int i = 0; i < q; i++) {
        cout << (ans[i] <= k_lim[i] ? "YES" : "NO") << endl;
    }
}

int main() {
    fastio();
    int T;
    cin >> T;
    while(T--) {
        solve();
    }

    return 0;
}