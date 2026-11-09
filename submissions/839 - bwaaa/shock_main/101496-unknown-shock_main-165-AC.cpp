#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")

typedef long long int ll;

template<typename T>
using minheap = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using maxheap = priority_queue<T>;
template<typename T>
using vec = vector<T>;

#define FOR(i,a,b) for(int i = (a); i < (b); ++i)
#define ROF(i,a,b) for(int i = (a); i >= (b); --i)
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define rot(a, x) rotate(a.begin() + 1, a.begin() + 1 + x, a.end())
#define sz(x) (int)(x).size()

typedef vector<int> vi;

struct dsu {
	vi e;
    vi right;
	dsu(int n) : e(n, -1), right(n) {iota(all(right), 0);}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
        right[a] = max(right[a], right[b]);
		return true;
	}
};

void solve() {
    ll n, m, q;
    cin >> n >> m >> q;
    bool flip = false;
    if (m > n) swap(n, m), flip = true;

    vec<array<ll, 3>> earth(q);
    for (ll i = 0; i < q; i++) {
        ll r, c, p;
        cin >> r >> c >> p;
        //earth[i] = {n/2, m/2, min(n, m)/2};
        if (flip) swap(r, c);
        earth[i] = {r, c, p};
    }
    reverse(all(earth));
    

    vec<dsu> nxt(n, dsu(m));
    vec<vec<ll>> ans(n, vec<ll>(m));
    for (auto [R, C, P] : earth) {
        ll topr = R - P;
        ll botr = R + P;
        for (ll r = topr; r <= botr; r++) {
            ll dr = abs(r - R);
            ll dc = sqrtl(P*P - dr*dr);
            ll cur = C - dc;
            ll mx = C + dc;
            ll bef = -1;
            while (cur <= mx) {
                ll group = nxt[r].find(cur);
                if (!ans[r][cur]) {
                    ll felt = P*P + 1 - (R - r)*(R - r) - (C - cur) * (C - cur);
                    ans[r][cur] = felt;
                }
                ll nxtc = nxt[r].right[group];
                if (bef >= 0) nxt[r].join(bef, cur);
                bef = cur;
                cur = nxtc + 1;
            }
        }
    }

    
    if (!flip) for (ll i = 0; i < n; i++) for (ll j = 0; j < m; j++) cout << ans[i][j] << " \n"[j == m-1];
    else for (ll j = 0; j < m; j++) for (ll i = 0; i < n; i++) cout << ans[i][j] << " \n"[i == n-1];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll tc = 1;
    cin >> tc;
    for (ll i = 1; i <= tc; i++) {
        solve();
    }
}
