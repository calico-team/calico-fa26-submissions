#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <class T> using ind_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
#define sz(x) (int)(x).size()
#define sq(x) (x) * (x)
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define chmax(x, y) x = max(x, y)
#define chmin(x, y) x = min(x, y)
#define minc(x, y) x = ((x + y) % MOD + MOD) % MOD
#define mdec(x, y) x = ((x - y) % MOD + MOD) % MOD
 
#define ll long long
#define lll __int128_t
#define ld long double
#define pii pair<int,int>
#define vpii vector<pii>
#define pll pair<ll,ll>
#define vpll vector<pll>
#define vi vector<int>
#define vll vector<ll>
#define vb vector<bool>
#define vvi vector<vector<int>>
#define vvll vector<vector<ll>>
 
#define f first
#define s second
#define pb push_back
#define popb pop_back
#define bk back
#define popcnt __builtin_popcount

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) for (int i = 0; i < (a); ++i)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) for (int i = (a)-1; i >= 0; --i)

string to_string(string s) {
    return '"' + s + '"';
}

string to_string(char c) {
    return '\'' + string(1,c) + '\'';
}

string to_string(const char* s) {
  return to_string((string)s);
}
 
string to_string(bool b) {
    return (b ? "true" : "false");
}
 
template <typename T1, typename T2>
string to_string(pair<T1, T2> &p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}
 
template <typename T>
string to_string(T v) {
    int c = 0;
    string res = "{";
    for (const auto &x : v) {
        if (c) res += ", ";
        c = 1;
        res += to_string(x);
    }
    res += "}";
    return res;
}
 
void __print(bool b) { cerr << "]" << endl; }
 
template <typename First, typename... Rest>
void __print(bool b, First F, Rest... R) {
    if (b) cerr << ", ";
    cerr << to_string(F);
    __print(true, R...);
}

#ifdef LOCAL
#define print(...) cerr << "[" << #__VA_ARGS__ << "] : [", __print(false, __VA_ARGS__)
#else
#define print(...) 42
#endif
 
mt19937_64 rv(chrono::steady_clock::now().time_since_epoch().count());
ll rng(ll l, ll r) { return (ll)uniform_int_distribution<ll>(l, r)(rv); }
 
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
 
    size_t operator()(uint64_t x) const {
        static const uint64_t r = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + r);
    }
};

ll MOD = 1e9+7;
int M998 = 998244353;
const ll INF = 3e18;
const double PI = 4 * atan(1); 
 
ll p2(int b) { return (1ll << b); }
int l2(int x) { return 31 - __builtin_clz(x); }
int l2(ll x) { return 63 - __builtin_clzll(x); }
ll min(int a, ll b) { return min((ll)a, b); }
ll min(ll a, int b) { return min(a, (ll)b); }

ll mfix(ll a, ll m = MOD) { return (a % m + m) % m; }
ll msum(ll a, ll b, ll m = MOD) { return ((a + b) % m + m) % m; }
ll mdif(ll a, ll b, ll m = MOD) { return ((a - b) % m + m) % m; }
ll mmul(ll a, ll b, ll m = MOD) { return (__int128)a * b % m; } 
ll mexp(ll b, ll e, ll m = MOD) {
    ll res = 1;
    while (e) {
        if (e % 2) res = mmul(res, b, m);
        b = mmul(b, b, m);
        e /= 2;
    } return res;
}
ll exp(ll b, ll e) { return mexp(b, e, INF); }
ll minv(ll b, ll m = MOD) { return mexp(b, m-2, m); }
ll mdiv(ll a, ll b, ll m = MOD) { return mmul(a, minv(b), m); }

vll fm = {1}, fmi = {1};
ll fac(int n) {
    while (sz(fm) <= n) {
        fm.push_back(fm.back() * sz(fm) % MOD);
        fmi.push_back(minv(fm.back()));
    }
    return fm[n];
}

ll ncr(int n, int r) {
    if (n < r) return 0;
    return fac(n) * fmi[r] % MOD * fmi[n - r] % MOD;
}

ll npr(int n, int r) {
    if (n < r) return 0;
    return fac(n) * fmi[n - r] % MOD;
}

struct DSU {
    vector<int> p, c;

    DSU(int n) : c(n, 1), p(n) { 
        for (int i = 0; i < n; ++i) {
            p[i] = i;
        }
    }

    int get(int v) {
        if (p[v] == v) return v;
        return p[v] = get(p[v]);
    }

    int size(int v) { return c[get(v)]; }

    bool same(int x, int y) { return get(x) == get(y); }

    bool unite(int x, int y) {
        x = get(x); y = get(y); 
        if (x == y) return 0;
        if (c[x] > c[y]) swap(x, y);
        p[x] = y;
        c[y] += c[x];
        return 1;
    }
};

template <class T> struct BIT {
	int len;
	vector<T> bit, v;

	BIT(int n) : len(n), bit(n + 1), v(n) {}

	void edit(int ind, T val) { add(ind, val - v[ind]); }

	void add(int ind, T val) {
		v[ind] += val;
		ind++;
		for (; ind <= len; ind += ind & -ind) { bit[ind] += val; }
	}

	T sum(int ind) { // [0, ind]
		ind++;
		T total = 0;
		for (; ind > 0; ind -= ind & -ind) { total += bit[ind]; }
		return total;
	}

    T sum(int l, int r) { // [l, r)
        return sum(r - 1) - sum(l - 1);
    }
};

template<typename T> struct SegTree {
    vector<T> v; int len;

    T id = 0;
    T oper(T a, T b) { // associative operation
        return a + b;
    }

    SegTree(int n) : len(n), v(n*2) { for (int i = 0; i < n*2; ++i) v[i] = id; }
    SegTree(vector<T> v_) : len(sz(v_)), v(v_) {}

    void edit(int ind, const T &val) {
        ind += len; v[ind] = val;
        while (ind > 1) {
            ind /= 2;
            v[ind] = oper(v[ind<<1], v[ind<<1|1]);
        }
    }

    T query(int l, int r) { // [l,r)
        T resl = id, resr = id; l += len; r += len;
        while (l < r) {
            if (l%2) resl = oper(resl, v[l++]);
            if (r%2) resr = oper(v[--r], resr);
            l /= 2; r /= 2;
        }
        return oper(resl, resr);
    }

    T get(int ind) { return v[ind + len]; }

    void inc(int ind, T val) { edit(ind, get(ind) + val); } 
};
 
/* CODE BEGINS HERE */

// REMEMBER TO SET N PROPERLY 
const int N = 3e5 + 5;

void solve(int tc_ = 0) {
    int n, r; cin >> n >> r;
    vll a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vvll dp(n, vll(2));
    dp[0][0] = dp[0][1] = r;
    for (int i = 1; i < n; i++) {
        dp[i][0] = dp[i][1] = -1;
        ll d = a[i] - a[i-1];
        // used 0 before
        if (dp[i-1][0] != -1) {
            ll h0 = d;
            ll h1 = dp[i-1][0];
            if (h0 > r) {
                h0 = r;
                h1 += h0 - r;
            }
            if (h1 > r) h1 = r;
            if (h0 == r) {
                dp[i][0] = h1;
            }
            if (h1 == r) {
                dp[i][1] = h0;
            }

        }
        // used 1 before
        if (dp[i-1][1] != -1) {
            ll h0 = dp[i-1][1] + d;
            ll h1 = 0;
            if (h0 > r) {
                h0 = r;
                h1 += h0 - r;
            }
            if (h1 > r) h1 = r;
            if (h0 == r) {
                chmax(dp[i][0], h1);
            }
            if (h1 == r) {
                chmax(dp[i][1], h0);
            }
        }
    }
    cout << (dp[n-1][0] != -1 || dp[n-1][1] != -1 ? "YES\n" : "NO\n");
}


void init() {
    
}

void setio(string s = "") {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // return; // uncomment for interactive problems, REMEMBER TO RECOMMENT
    #ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("err.txt", "w", stderr);
    freopen("out.txt", "w", stdout);
    #else
    if (sz(s)) {
        freopen((s+".in").c_str(), "r", stdin);
        freopen((s+".out").c_str(), "w", stdout);
    }
    #endif
}
 
int32_t main() {
    setio();
    init();

    int t = 1;
    cin >> t;
    for (int i = 0; i < t; ++i) solve(i);
 
    cerr << "Time : " << (double) clock() / CLOCKS_PER_SEC << "s" << endl;
    return 0;
}   