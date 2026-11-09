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

struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};

void solve() {
    ll n, m, q;
    cin >> n >> m >> q;

    vec<array<ll, 3>> earth(q);
    for (ll i = 0; i < q; i++) {
        ll r, c, p;
        cin >> r >> c >> p;
        earth[i] = {r, c, p};
        //earth[i] = {500, 500, 499};
    }

    vec<vec<ll>> block(n, vec<ll>(m, -1));
    
    const ll B = 630; 
    for (ll l = 0; l < q; l += B) { // 100 times max
        vec<LineContainer> bycol(m);
        for (ll i = 0; i < m; i++) bycol[i].add(0, -1e9);
        for (ll i = l; i < min(q, l + B); i++) {
            // p^2 + 1 - R^2 - C^2 - r^2 - c^2 + 2*rR + 2*cC
            auto [R, C, P] = earth[i];
            ll k = P*P + 1 - R*R - C*C; // r is variable here
            ll slope = 2*R;
            bycol[C].add(slope, k);
        }
            
        for (ll i = 0; i < n; i++) {
            LineContainer row;
            row.add(0, -1e9);
            for (ll j = 0; j < m; j++) {
                ll best = bycol[j].query(i) - i*i;
                row.add(2*j, best);
            }
            for (ll j = 0; j < m; j++) {
                ll best = row.query(j) - j*j;
                if (best > 0) block[i][j] = l / B;
            }
        }  
    }
    vec<vec<ll>> ans(n, vec<ll>(m));
    vec<vec<pair<ll, ll>>> byblock(2e4 / B + 2);
    for (ll i = 0; i < n; i++) for (ll j = 0; j < m; j++) {
        if (block[i][j] == -1) continue;
        byblock[block[i][j]].push_back({i, j});
    }
    for (ll l = 0, b = 0; l < q; l += B, b++) { // 100 times max
        for (ll i = l; i < min(q, l + B); i++) {
            for (auto& [x, y] : byblock[b]) {
                const auto& [r, c, p] = earth[i];
                ll felt = p * p + 1 - (r - x) * (r - x) - (c - y) * (c - y);
                if (felt > 0) ans[x][y] = felt;
            }
        }
    }

    
    for (ll i = 0; i < n; i++) for (ll j = 0; j < m; j++) cout << ans[i][j] << " \n"[j == m-1];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll tc = 1;
    cin >> tc;
    for (ll i = 1; i <= tc; i++) {
        solve();
    }
}
