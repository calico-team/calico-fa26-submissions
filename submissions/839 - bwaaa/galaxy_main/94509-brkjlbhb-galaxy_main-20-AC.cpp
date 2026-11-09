#include <bits/stdc++.h>
using namespace std;

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
	dsu(int n) : e(n, -1) {}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
		return true;
	}
};

void solve() {
    ll n, m, q;
    cin >> n >> m >> q;
    vec<string> g(n);
    for (ll i = 0; i < n; i++) cin >> g[i];

    auto conn = [&](char x, char y) {
        if (x == '.' or y == '.') return true;
        
        return x == y;
    };

    dsu dsu(n*m);
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            if (i > 0 and conn(g[i][j], g[i-1][j])) dsu.join(i*m + j, (i-1)*m + j);
            if (j > 0 and conn(g[i][j], g[i][j-1])) dsu.join(i*m + j, i*m + j-1);
        }
    }

    for (ll i = 0; i < q; i++) {
        ll x, y, s, t;
        cin >> x >> y >> s >> t;
        if (dsu.sameSet(x*m + y, s*m + t)) cout << "YES\n";
        else cout << "NO\n";
    }


}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll tc = 1;
    cin >> tc;
    for (ll i = 1; i <= tc; i++) {
        solve();
    }
}
