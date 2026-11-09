#include <bits/stdc++.h>
#include <cassert>
using namespace std;

// clang-format off
#define int long long
#define double long double
#define pii pair<int, int>
#define endl "\n"
#define prec(i) fixed << setprecision(i)
#define all(v) (v.begin()), (v.end())
#define rall(v) (v.rbegin()), (v.rend())
#define pc __builtin_popcountll
const int INF = 1e18;
const int MOD = 1e9 + 7;
// const int MOD = 998244353;

#ifndef ONLINE_JUDGE
template<class...T>ostream& operator<<(ostream&s,const pair<T...>&p){return s<<"("<<p.first<<", "<<p.second<<")";}
#define PR(C) template<class...T>ostream& operator<<(ostream&s,const C<T...>&v){s<<"{";int n=0;for(auto&x:v)s<<(n++?", ":"")<<x;return s<<"}";}
PR(vector)PR(set)
template<class...T>ostream& operator<<(ostream&s,const map<T...>&v){s<<"{";int n=0;for(auto&[k,x]:v)s<<(n++?", ":"")<<k<<": "<<x;return s<<"}";}
template<class T,class...U>void _dbg(const T&x,const U&...y){cerr<<x;((cerr<<", "<<y),...);cerr<<endl;}
#define dbg(...) do{cerr<<"["<<#__VA_ARGS__<<"]: ";_dbg(__VA_ARGS__);}while(0)
#else
#define dbg(...)
#endif

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i <= (int)(n); i++)
#define each(i, v) for (auto& i : (v))

int cdiv(int a, int b) { return a / b + ((a ^ b) > 0 && a % b); }
int fdiv(int a, int b) { return a / b - ((a ^ b) < 0 && a % b); }

template <class T> bool chmax(T& a, T b, bool isok = true) { return isok && a < b ? a = b, 1 : 0; }
template <class T> bool chmin(T& a, T b, bool isok = true) { return isok && b < a ? a = b, 1 : 0; }
// clang-format on

const int N = 2e5 + 10;
vector<int> g[N];
int a[N];

void dfs(int u, int p) {
    a[u] = u ^ p;
    each(v, g[u]) if (v != p) {
        dfs(v, u);
    }
}

void first_stuff(int n) {
    // int n;
    // cin >> n;

    rep(i, n - 1) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, -1);
    for (int i = 2; i <= n; i++) {
        a[1] ^= a[i];
    }

    rep1(i, n) {
        cout << a[i] << " ";
    }

    cout << endl;
}

void second(int n) {
    pii oop; // {cur, idx}
    int cur = 0;
    rep1(i, n) {
        cin >> a[i];
        if (a[i] == -1) {
            oop = {cur, i};
        } else {
            cur ^= a[i];
        }
    }

    a[oop.second] = cur;
    for (int i = 2; i <= n; i++) {
        cout << i << " " << (a[i] ^ i) << endl;
    }
}

void solve(int tc) {
    string p;
    cin >> p;

    int n;
    cin >> n;

    if (p == "FIRST") {
        first_stuff(n);
    } else {
        second(n);
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    // cin >> t;

    rep1(tc, t) {
        solve(tc);
    }
}
