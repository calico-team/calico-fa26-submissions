/*****************************************
* cf: tipsyGnostalgic                    *
*     2026/11/08 at 18:27:46             *
*     go maroons!                        *
*****************************************/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

/**
 * Data types
 */
#define tY template<typename T>
#define tYu tY using
#define tYS template<typename T, typename S>
#define tYSu tYS using
using str = string;
tYu vec = vector<T>;
tYu minheap = priority_queue<T, vec<T>, greater<T>>;
tYu pbds_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
tYu pbds_map = tree<T, T, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define MAKE_TYPES(alias, ...) \
    using alias = __VA_ARGS__; \
    using v##alias = vec<alias>; \
    using vv##alias = vec<v##alias>

MAKE_TYPES(ll, long long);          
MAKE_TYPES(ld, long double);          
MAKE_TYPES(pll, pair<ll, ll>);

/**
 * Weird macros
 */
#define pb push_back
#define fi first
#define se second
#define all(x) begin(x),end(x)
#define lla(x) rbegin(x),rend(x)

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
struct smhash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        x ^= (x >> 31);
        return x;
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = 
            std::chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

tYSu random_map = unordered_map<T,S,smhash>;
tYu random_set = unordered_set<T,smhash>;

tY auto enumerate(T& container) {
    struct Iterator {
        size_t index;
        decltype(container.begin()) it;
        bool operator!=(const Iterator& other) const { return it != other.it; }
        void operator++() { ++index; ++it; }
        
        struct RefPair { size_t index; decltype(*it) value; };
        RefPair operator*() const { return {index, *it}; }
    };
    struct Enumerable {
        T& container;
        auto begin() { return Iterator{0, container.begin()}; }
        auto end() { return Iterator{0, container.end()}; }
    };
    return Enumerable{container};
}

tY struct y_combinator {
    T f;
    template<class... Args> 
    decltype(auto) operator()(Args&&... args) {
        return f(*this, std::forward<Args>(args)...);
    }
}; struct ycwrap { 
    tY auto operator=(T&& f) { return y_combinator<decay_t<T>>{std::forward<T>(f)}; } 
} recursive;
#define def(name, ...) auto name = recursive = [&](auto& name, ##__VA_ARGS__)

tYS ostream& operator<<(ostream& os, const pair<T,S>& p) { return os << p.fi << " " << p.se; }
tY  ostream& operator<<(ostream& os, const vector<T>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        os << v[i] << " ";
    } return os;
}

/**
 * i/o, debug
 */
#include <cassert> // whyd they remove this :(
#define co cout <<
#define cr cerr <<
#define nl << endl
#define sp << ' '
#define sps << ' ' <<
#define rv(x) return void(co x nl)
#define dbg(x) cr #x << ": " << x nl
#define dbp(i,j) cr "(" << #i << "," << #j << "): " << i << ", " << j nl

/**
 * Modulo stuff
 */
const ll MOD = 1'000'000'007;
// const ll MOD =   998'244'353;

ll modpow(ll a, ll x, ll m = MOD) {
    ll out = 1;
    while(x) {
        if(x&1) out = (out*a)%m;
        a = (a*a)%m;
        x >>= 1;
    }
    return out;
}

ll mdiv(ll p, ll q) { return p * modpow(q,MOD-2) % MOD; }
ll mmul(ll p, ll q) { return p * q % MOD; }
ll madd(ll p, ll q) { return (p + q) % MOD; }
ll msub(ll p, ll q) { return (((p-q)%MOD) + MOD) % MOD; }

/**
 * Miscellaneous
 */
void ckmax(ll &x, ll i) { x = max(x,i); }
void ckmin(ll &x, ll i) { x = min(x,i); }

/***********************************************/

struct DSU {
    vll par,sz;
    DSU(ll n) {
        par = sz = vll(n,1);
        iota(all(par),0);
    }

    ll find(ll x) {
        return x==par[x]?x:par[x]=find(par[x]);
    }

    void hug(ll i, ll j) {
        i = find(i);
        j = find(j);
        if(i==j) return;
        if(sz[i] < sz[j]) swap(i,j);
        par[j] = i;
        sz[i] += sz[j];
    }
};

void solve() {
    ll n, m, k;
    cin >> n >> m >> k;

    vll par(n,0);
    for(ll &x : par) cin >> x, x--;

    vvll adj(n);
    for(int i = 0; i < n; i++) {
        if(par[i] != -1) adj[par[i]].pb(i);
    }

    vll depth(n,0);
    vll height(n,0);

    map<ll,vll> atdepth;

    auto dfs = [&](auto &&self, ll u, ll root) -> void {
        atdepth[depth[u]].pb(u);
        for(ll &v : adj[u]) {
            if(v==par[u]) continue;
            depth[v] = 1 + depth[u];
            self(self,v,root);
        }
    };

    for(int i = 0; i < n; i++) {
        if(par[i] == -1) dfs(dfs,i,i);
    }

    ll ans = 0;
    vec<bool> vis(n,0);
    ll cd = 0;
    set<ll> crack;

    ll i = 0;

    while(m--) {
        // DO K THINGS
        ll cnt = 0;
        if(ans==n) break;
        bool ok = 1;
        while(cnt < k and ok) {
            for(ll &u : atdepth[cd]) {
                if(par[u] != -1 and vis[par[u]]) {ok=0;break;}
                vis[u] = 1;
                crack.insert(u);
                cnt++;
                if(cnt==k) break;
            }

            if(crack.size() == atdepth[cd].size()) {
                // move next layer
                cd++;
                sort(all(atdepth[cd]),[&](ll u, ll v) { return vis[par[u]] < vis[par[v]]; });
            }

            while(cnt < k and ok) {
                for(ll &u : atdepth[cd]) {
                    if(par[u] != -1 and vis[par[u]]) {ok=0;break;}
                    vis[u] = 1;
                    crack.insert(u);
                    cnt++;
                    if(cnt==k) break;
                }
            }
        }

        vll blah;
        for(ll &u : atdepth[cd]) {
            if(crack.find(u) != crack.end());
            else blah.pb(u);
        }
        atdepth[cd] = blah;

        for(ll x : crack) {
            vis[x] = 0;
        }

        ans += crack.size();

        crack.clear();
    }

    // ll ans = 0;
    // for(auto [c,x] : hello) {
        // ans += dsu.sz[dsu.find(c)] == x;
    // }

    // for(bool x : vis) ans += x;
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    cin >> t;

    for(int i = 1; i <= t; i++) {
        // cr "START TC" sps i nl;
        solve();
    }

    return 0;
}