#include <bits/stdc++.h>
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

const int N = 1e5 + 10;

struct Drone {
    int x, y, z;
    char d; // only n/e
} a[N];

bool cmp(Drone a, Drone b) {
    return a.x < b.x;
}

void solve(int tc) {
    int n, k;
    cin >> n >> k;

    rep(i, n) {
        int x, y, z;
        char d;
        cin >> x >> y >> z >> d;

        a[i] = {x, y, z, tolower(d)};
    }

    vector<Drone> north, east;
    rep(i, n) {
        if (a[i].d == 'n') {
            north.push_back(a[i]);
        } else {
            east.push_back(a[i]);
        }
    }

    map<int, vector<Drone>> ndgs;
    each(d, north) {
        ndgs[d.x + d.y].push_back(d);
    }

//    vector<tuple<int, int, int>> e; // 1 n drone, +5 on start, -5 if ending
    each(p, ndgs) {
        sort(all(p.second), cmp);
    }

    int ans = 0;
    each(d, east) {
        vector<Drone> matching = ndgs[d.x + d.y];
        // ans -= upper_bound(all(matching), d.x + k - 1) - lower_bound(all(matching), d.x);
        Drone left_front = Drone{d.x, d.y, d.z, d.d};
        Drone right_front = Drone{d.x + k - 1, d.y, d.z, d.d};
        ans -= upper_bound(all(matching), right_front, cmp) -
               lower_bound(all(matching), left_front, cmp);
    }

    ans += n * k;
    cout << ans << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    cin >> t;

    rep1(tc, t) {
        solve(tc);
    }
}
