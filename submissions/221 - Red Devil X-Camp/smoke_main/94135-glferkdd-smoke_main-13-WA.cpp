#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef long double ld;
ll dx[] = {1, 0, -1, 0, 1, -1, -1, 1};
ll dy[] = {0, 1, 0, -1, 1, -1, 1, -1};
const ll mod = 1e9 + 7;
const ll inf = 1e17;
template<typename A, typename B>
ostream& operator<<(ostream& os, const pair<A, B>& p) {
    return os << "(" << p.first << ", " << p.second << ")";
}
 
template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
    os << "[";
    for (int i = 0; i < v.size(); ++i) {
        os << v[i] << (i == v.size() - 1 ? "" : ", ");
    }
    return os << "]";
}
#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define ff first
#define ss second
#define pb push_back
#define FOR(i, a, b) for (ll i = a; i < b; i++)
#define REP(i, a, b) for (ll i = a; i >= b; i--)
#define FORR(i, a, b, x) for (ll i = a; i < b; i += x)
#define checkbit(i, j) (i & (1 << j))
#define numbits(n) __builtin_popcount(n)
#define srt(v) sort(v.begin(), v.end())
#define rsrt(v) sort(v.rbegin(), v.rend())
#define rev(v) reverse(v.begin(), v.end())
#define all(v) (v).begin(), (v).end()
#define biadj(adj, x, y) adj[x].pb(y); adj[y].pb(x); /*is this not genius? :D*/
#define srtt(v, comp) sort(v.begin(), v.end(), comp)
#define print(n) cout << n << endl; return;
#define szof(v) (ll)v.size()
#define fbo find_by_order
#define ook order_of_key
#define get1(n) ll n; cin >> n;
#define get2(n, m) ll n, m; cin >> n >> m;
#define get3(n, m, k) ll n, m, k; cin >> n >> m >> k;
#define get4(a, b, c, d) ll a, b, c, d; cin >> a >> b >> c >> d;
#define get5(a, b, c, d, e) ll a, b, c, d, e; cin >> a >> b >> c >> d >> e;
#define get6(a, b, c, d, e, f) ll a, b, c, d, e, f; cin >> a >> b >> c >> d >> e >> f;
#define getn(n, v) vi v(n); FOR(i, 0, n) cin >> v[i];
#define printv(v) for (ll i = 0; i < v.size(); ++i) cout << v[i] << (i == v.size() - 1 ? "\n" : " ");
#define lb(v, x) lower_bound(all(v), x)
#define ub(v, x) upper_bound(all(v), x)
#define dbg(x) cerr << #x << " = " << x << "\n";
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<class T> using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T>
using V = vector<T>;
template <typename T>
using Q = queue<T>;
template <typename T>
using PQ = priority_queue<T>;
template <typename T>
using RPQ = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using S = set<T>;
template <typename T1, typename T2>
using P = pair<T1, T2>;
template <typename T1, typename T2, typename T3>
using T = tuple<T1, T2, T3>;
void setio(string name = "") {
 	fastio;
	if (name.size()) {
		freopen((name + ".in").c_str(), "r", stdin);
		freopen((name + ".out").c_str(), "w", stdout);
	}
}
 
void yon(bool b) {
    cout << (b ? "YES" : "NO") << "\n";
    return;
}
 
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
 
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
 
 
//im keeping this...
// ll random(const ordered_set<ll>& os) {
//     vector<ll> v(os.begin(), os.end());
//     random_device rd;
//     mt19937 rng(rd()); 
//     uniform_int_distribution<ll> uni(0, v.size() - 1);
//     ll idx = uni(rng);
//     return v[idx];
// }
//for fun yk
const ll mxx = 1e5;
 
ll fastpow(ll a, ll b, ll m) {
    //a ^ b % m
    ll res = 1;
    a %= m;
    while (b > 0) {
        if (b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}
 
ll fib(ll n) {
    V<ll> dp(n + 1);
    dp[0] = dp[1] = 1;
    FOR(i, 2, n + 1) dp[i] = dp[i - 1] + dp[i - 2];
    return dp[n];
}
 
ll fact(ll n) {
    V<ll> dp(n + 1);
    dp[1] = 1;
    FOR(i, 2, n + 1) dp[i] = i * dp[i - 1];
    return dp[n];
}
 
ll comb(ll n, ll k) {
    return (fact(n) / (fact(k) * fact(n - k)));
}
 
bool isprime(ll x) {
    if (x < 2) return 0;
    if (x < 4) return 1;
    if (x % 2 == 0 || x % 3 == 0) return 0;
    for (ll i = 5; i * i <= x; i += 6) {
        if (x % i == 0 || x % (i + 2) == 0) return 0;
    }
    return 1;
}
 
void compress(V<ll> &v) {
    srt(v);
    v.erase(unique(all(v)), v.end());
}
 
ll sieve[mxx];
void sieveprimes() {
    iota(sieve, sieve + mxx, 0);
    for (ll i = 2; i * i < mxx; i++) if (sieve[i] == i) for (ll j = i * i; j < mxx; j += i) if (sieve[j] == j) sieve[j] = i;
}
 
V<ll> factors(ll n) {
    V<ll> factors;
    while (n > 1) {
        factors.pb(sieve[n]);
        n /= sieve[n];
    }
    return factors;
}
 
ll kadane(V<ll>& v) {
    ll n = v.size();
    ll curr = v[0];
    ll best = v[0];
    FOR(i, 1, n) {
        ll x = v[i];
        curr = max(curr + x, x);
        best = max(best, curr);
    }
    return best;
}
 
ld doublekadane(ld v[], ll n) {
    //doesnt this sound kinda wierd lol
    ld curr = v[1];
    ld best = v[1];
    FOR(i, 2, n - 1) {
        ld x = v[i];
        curr = max(curr + x, x);
        best = max(best, curr);
    }
    return best;
}
 
V<V<ll>> build(V<V<ll>>& v) {
    ll n = szof(v), m = szof(v[0]);
    V<V<ll>> psum(n, V<ll>(m));
    FOR(i, 0, n) {
        FOR(j, 0, m) {
            bool ii = (i > 0), jj = (j > 0);
            psum[i][j] = v[i][j];
            if (ii) psum[i][j] += psum[i - 1][j];
            if (jj) psum[i][j] += psum[i][j - 1];
            if (ii && jj) psum[i][j] -= psum[i - 1][j - 1];
        }
    }
    return psum;
}
 
ll query(V<V<ll>>& psum, ll x1, ll y1, ll x2, ll y2) {
    ll ret = psum[x2][y2];
    bool x11 = (x1 > 0), y11 = (y1 > 0);
    if (x11) ret -= psum[x1 - 1][y2];
    if (y11) ret -= psum[x2][y1 - 1];
    if (x11 && y11) ret += psum[x1 - 1][y1 - 1];
    return ret;
}
 
struct SegTree {
    ll n;
    V<ll> tree;
    void init(ll x) {
        n = x;
        tree.assign(4 * n + 1, 0LL);
    }
    void update(ll node, ll start, ll end, ll idx, ll val) {
        //ie change idx to new val
        if (start == end) { tree[node] = val; return; }
        ll mid = (start + end) / 2;
        if (idx <= mid) update(2 * node, start, mid, idx, val);
        else update(2 * node + 1, mid + 1, end, idx, val);
        tree[node] = tree[2 * node] + tree[2 * node + 1]; //CHANGE FOR DIFFERENT QUERIES
    }
    ll query(ll node, ll start, ll end, ll l, ll r) {
        //ie find sum of range l->r
        if (r < start || end < l) return 0;
        if (l <= start && end <= r) return tree[node];
        ll mid = (start + end) / 2;
        return query(2 * node, start, mid, l, r) + query(2 * node + 1, mid + 1, end, l, r);
    }
};
 
ll euclidiansquared(ll x1, ll y1, ll x2, ll y2) {
    return ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}
 
struct DSU {
    V<ll> p, s;
    // ll num, mx2;
    void init(ll n/*, map<ll, ll>& info*/) {
        p = V<ll>(n + 1, -1);
        s = V<ll>(n + 1);
        FOR(i, 0, n + 1) s[i] = 1/*CHANGE*/;
        // num = ;
        // mx2 = num;
    }
    ll find(ll x) {
        return (p[x] < 0 ? x : p[x] = find(p[x]));
    }
    bool same(ll x, ll y) {
        return (find(x) == find(y));
    }
    ll sz(ll x) {
        return s[find(x)];
    }
    bool unite(ll x, ll y) {
        x = find(x), y = find(y);
        if (x == y) return 0;
        if (s[x] < s[y]) swap(x, y);
        s[x] += s[y];
        p[y] = x;
        // --num;
        // mx2 = max(mx2, s[x]);
        return 1;
    }
    bool check(ll n) {
        bool f = 1;
        FOR(i, 1, n + 1) if (sz(i) % 2) {
            f = 0;
            break;
        }
        return f;
    }
    void reset(V<ll>& res, map<ll, ll>& info) {
        for (auto x : res) {
            p[x] = -1;
            s[x] = info[x];
        }
    }
};
 
struct Edge {
    ll a, b, c;
};
 
bool mstcomp(Edge x, Edge y) {
    return x.c < y.c;
}
 
//KRUSKAL
ll kruskal(vector<Edge>& edges, ll n/*, map<ll, ll> info*/) {
    srtt(edges, mstcomp);
    DSU dsu;
    dsu.init(n/*, info*/);
    ll ans = 0;
    ll cnt = 0;
    for (auto [n1, n2, w] : edges) {
        if (dsu.unite(n1, n2)) {
            ans += w; 
            ++cnt;
        }
        if (cnt == n - 1) break;
    }
    return (cnt == n - 1 ? ans : -1);
}
 
/*
Q<ll> q;
V<bool> visited(n + 1, 0);
FOR(i, 1, n + 1) {
    if (visited[i]) continue;
    q.push(i);
    visited[i] = 1;
    while (!q.empty()) {
        auto curr = q.front; q.pop();
        for (auto u : adj[curr]) {
            if (visited[u]) continue;
            visited[u] = 1;
            q.push(u);
        }
    }
}
*/

void solve() {
    ll n,r;cin>>n>>r;
    V<ll>v(n);
    FOR(i,0,n)cin>>v[i];
    ll c1=-1,c2=-1;
    //-1:charged
    //1-r: how much time lef is needed
    FOR(i,0,n){
        if(c1==-1){
            c1=r;
            if(c2!=-1){
                c2-=v[i]-v[i-1];
                if(c2<=0)c2=-1;
            }
        }
        else if(c2==-1){
            c2=r;
            if(c1!=-1){
                c1-=v[i]-v[i-1];
                if(c1<=0)c1=-1;
            }
        }
        else{
            cout<<"NO"<<"\n";
            return;
        }
    }
    cout<<"YES"<<"\n";
    return;
}
 
//NOTES
/*
REMEMBER TO SET THE FIRST NODE YOU CHECKED IN BFS AS VISITED 
ie q.push(1); visited[1] = 1;
 
array out of bounds
 
Remember to do V<ll> or Q<ll> instead of vi or qi; get used to new template!
 
did u add unordered_map<ll, ll, custom_hash> ?
 
0-idx vs 1-idx
 
* vs + and i vs j and x vs y and make sure you have not changed a variable for another similar variable
 
did you comment out/comment in the cin >> t?
 
did u do the dp state before or after the dfs? try bottom-up AND top-down
 
+= vs =
 
take in all the input! otherwise it might cause undefined behavior
 
CHECK UR MATH!!!!

check whether you have to make an original array

upper_bound/lower_bound
*/
 
signed main() {
    setio("");
    ll t = 1;
    cin >> t;
    while (t--) solve();
}
// Bessie says hi vvv
 
/*
\|/          (___)    
     `\------(o o) \|/        \|/
       ||    (___)        \|/
       ||w--||     \|/          \|/
   \|/        \|/        \|/
*/
//yay thanks Chongtian