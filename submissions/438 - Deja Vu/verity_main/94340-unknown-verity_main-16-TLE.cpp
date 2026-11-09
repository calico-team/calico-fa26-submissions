//! author: Arslan Yanybayev

#include "bits/stdc++.h"

#ifdef NOIRFLUX
#include "/home/parad0x/Desktop/cp/debug.h"
#else
#define debug(...)
#define timer()
#endif

using namespace std;

#define tt debug

#define ll long long
#define ld long double
#define ull unsigned long long
#define uint unsigned int

#define pii pair<int, int>
#define pll pair<ll, ll>
#define pil pair<int, ll>
#define pli pair<ll, int>

using vi = vector<int>;
using vll = vector<ll>;

using minpq = priority_queue<pii, vector<pii>, greater<pii>>;
using maxpq = priority_queue<pii>;
using minpql = priority_queue<pll, vector<pll>, greater<pll>>;
using maxpql = priority_queue<pll>;

#define INF 1000000000
#define LINF 4000000000000000000LL
#define NINF (-INF)
#define NLINF (-LINF)

#define mask(i) (1LL << (i))
#define bit(x, i) (((x) >> (i)) & 1LL)

#define setbit(x, i) ((x) |= mask(i))
#define clrbit(x, i) ((x) &= ~mask(i))
#define flipbit(x, i) ((x) ^= mask(i))

#define pcnt(x) __builtin_popcountll(x)
#define ctz(x) __builtin_ctzll(x)
#define clz(x) __builtin_clzll(x)

#define lowbit(x) ((x) & -(x))
#define rmvlow(x) ((x) &= (x) - 1)

#define ispow2(x) ((x) > 0 && ((x) & ((x) - 1)) == 0)

#define fullmask(n) ((1LL << (n)) - 1)
#define rangemask(l, r) (((1LL << ((r) - (l) + 1)) - 1) << (l))

#define subset(a, b) (((a) & (b)) == (a))
#define disjoint(a, b) (((a) & (b)) == 0)
#define delmask(x, m) ((x) &= ~(m))

#define ff first
#define ss second

#define ft front
#define bk back

#define pb push_back
#define eb emplace_back
#define pp pop_back

#define pf push_front
#define ppf pop_front

#define sz(v) (int)(v).size()
#define empty(v) (v).empty()
#define clr(v) (v).clear()

#define lbi(v, x) (int)(lower_bound(all(v), x) - (v).begin())
#define ubi(v, x) (int)(upper_bound(all(v), x) - (v).begin())

#define uniq(v) ((v).erase(unique(all(v)), (v).end()))

#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()

#define lb lower_bound
#define ub upper_bound

#define shuf(v) shuffle(all(v), rng)

#define iota0(v) iota(all(v), 0)
#define iota1(v) iota(all(v), 1)

#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define per(i, r, l) for (int i = (r); i >= (l); --i)

#define rep0(i, n) for (int i = 0; i < (n); ++i)
#define rep1(i, n) for (int i = 1; i <= (n); ++i)

#define each(x, a) for (auto &x : (a))

#define gcd(a, b) __gcd((a), (b))
#define lcm(a, b) ((a) / gcd((a), (b)) * (b))

template<class T>
bool umin(T& a, T b) {
    if (a > b) {
        a = b;
        return 1;
    }
    return 0;
}

template<class T>
bool umax(T& a, T b) {
    if (a < b) {
        a = b;
        return 1;
    }
    return 0;
}

#define wr cout << "------------------------" << endl

#define dbg(x) cerr << #x << " = " << (x) << '\n'

#define dbg2(x) \
    cerr << #x << " = (" << (x).ff << ", " << (x).ss << ")\n"

#define dbgv(v) do { \
    cerr << #v << " = "; \
    for (auto &x : (v)) cerr << x << ' '; \
    cerr << '\n'; \
} while (0)

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

void solution();

signed main() {

    // ios::sync_with_stdio(false);cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        solution();
    }
    return 0;
}

string ans;
vector<char> cand;
int n;

bool ask(string s) {
    cout << s << '\n';
    string res; cin >> res;
    rep0(i, n) if (res[i] != '_') ans[i] = res[i];
    return res == "CORRECT";
}

void solution(){
    int k; cin >> n >> k;
    ans = "";
    rep0(i, n) ans += "$";
    cand.resize(k);
    each(c, cand) cin >> c;
    each(c, cand) if (ask(string(n, c))) break;
}