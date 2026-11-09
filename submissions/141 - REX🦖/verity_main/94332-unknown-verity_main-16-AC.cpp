#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = long double; // or double, if TL is tight
using pii = pair<int,int>;
using pll = pair<ll,ll>;
#define mp make_pair
#define f first
#define s second
template<typename T> 
using V = vector<T>; 
template<typename T, size_t SZ>
using AR = array<T,SZ>; 
using vi = V<int>;
using vb = V<bool>;
using vl = V<ll>;
using vd = V<db>;
using vs = V<string>;
using vpii = V<pii>;
using vpll = V<pll>;
using vvi = V<vi>;
using vvl = V<vl>;
#define sz(x) int((x).size())
#define all(x) begin(x), end(x)
#define rall(x) x.rbegin(), x.rend() 
#define sor(x) sort(all(x)) 
#define rz resize
#define ins insert 
#define pb push_back
#define eb emplace_back
#define ft front()
#define bk back()
#define lb lower_bound
#define ub upper_bound
template<typename T>
int lwb(V<T>& a, const T& b) { return int(lb(all(a),b)-begin(a)); }
template<typename T>
int upb(V<T>& a, const T& b) { return int(ub(all(a),b)-begin(a)); }
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define rep(a) F0R(_,a)
#define each(a,x) for (auto& a: x)
template<typename T1, typename T2>
istream& operator>>(istream& is, pair<T1, T2>& p) {
	is >> p.f >> p.s;
	return is;
}
template<typename T>
istream& operator>>(istream& is, V<T>& a) {
	each(x, a) is >> x;
	return is;
}
template<typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) {
	os << p.f << " " << p.s << "\n"; return os;
}
template<typename T>
ostream& operator<<(ostream &os, const V<T>& a) {
	each(x, a) os << x << " ";
	os << '\n';
	return os;
}
const int MOD = 1e9+7; // 998244353;
const int MOD9 = 1e9+9;
const int MOD998 = 998244353;
const ll INF = 1e18; 
const db PI = acos((db)-1);
const int dx[4] = {1,0,-1,0}; 
const int dy[4] = {0,1,0,-1};
mt19937_64 rng((uint64_t)chrono::steady_clock::now().time_since_epoch().count());
int pct(int x) { return __builtin_popcount(x); } 
int clz(int x) { return __builtin_clz(x); } 
int ctz(int x) { return __builtin_ctz(x); } 
ll p2(int b) { return (1ll << b); }
int l2(int x) { return 31 - clz(x); }
int l2(ll x) { return 63 - clz(x); }
ll sq(ll x) { return 1ll * x * x; }
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
ll inv(ll b, ll m = MOD) { return mexp(b, m-2, m); }
ll mdiv(ll a, ll b, ll m = MOD) { return mmul(a, inv(b), m); }
ll cdiv(ll a, ll b) { return a/b+((a^b)>0&&a%b); } 
template<typename T> 
bool ckmin(T& a, const T& b) {
	return b < a ? a = b, 1 : 0; } 
template<typename T> 
bool ckmax(T& a, const T& b) {
	return a < b ? a = b, 1 : 0; } 
//DSU
template<typename T> 
struct DSU {
	int cc;  vector<T> e; 
	DSU(T N) : e(N, -1) { cc = N; }
	T get(T x) { 	return e[x] < 0 ? x : e[x] = get(e[x]); } 
	bool sameSet(int a, int b) { return get(a) == get(b); }
	T size(int x) { return -e[get(x)]; }
	bool unite(T x, T y) {
		x = get(x), y = get(y); if (x == y) return 0;
		cc--;
		if (e[x] > e[y]) swap(x,y);
		e[x] += e[y]; e[y] = x; return 1;
	}
};
//Segment Tree
template<typename T>
struct SegTree {
	static const T unit = 0;
	T f(T a, T b) { return a + b; } 
	vector<T> s; int n;
	SegTree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { 
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};
//Fenwick Tree/BIT
template<typename T> 
struct BIT {
	vector<T> s;
	BIT(int n) : s(n) {}
	void update(int pos, T dif) {
		for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
	}
	T query(int pos) {
		T res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos-1];
		return res;
	}
	T lower_bound(T sum) {
		if (sum <= 0) return -1;
		T pos = 0;
		for (T pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= sz(s) && s[pos + pw-1] < sum)
				pos += pw, sum -= s[pos-1];
		}
		return pos;
	}
};
void setIO(string s = "") {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	// return; // for interactive problems
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("err.txt", "w", stderr);
	freopen("out.txt", "w", stdout);
	#else
	if (sz(s)) {
		freopen((s+".in").c_str(), "r", stdin);
		freopen((s+".out").c_str(), "w", stdout);
		//wow samuel needs to debug whatever i do here :D
	}
	#endif
}
void solve(int tc) {
    int n, k; cin >> n >> k;
    V<char> a(k); cin >> a; 
    string ans(n, '?');
    F0R(i, k) {
        cout << string(n, a[i]) << endl; 
        string s; cin >> s;
        if (s == "CORRECT") return;
        F0R(j, n) {
            if (s[j] != '_') ans[j] = a[i]; 
        }
    }
    cout << ans << endl; 
    string goon; cin >> goon; 
}
int main() {
	setIO();
	int t = 1; cin >> t;
	FOR(i, 1, t+1) solve(i);
	cerr << "Time : " << (double)1000 * (double) clock() / CLOCKS_PER_SEC << "ms" << endl;
	return 0;
}