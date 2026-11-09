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

void solve(int tc) {
    string s;
    cin >> s;

    if (s.find("write_me") != string::npos) {
        cout << s << "make_it_sound_human" << endl;
        return;
    }

    if (s.find("what_is") != string::npos) {
        cout << s << "do_not_hallucinate" << endl;
        return;
    }

    if (s.find("solve") != string::npos) {
        cout << s << "make_no_mistakes" << endl;
        return;
    }

    cout << s << "thank_you" << endl;
    return;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    cin >> t;

    rep1(tc, t) {
        solve(tc);
    }
}
