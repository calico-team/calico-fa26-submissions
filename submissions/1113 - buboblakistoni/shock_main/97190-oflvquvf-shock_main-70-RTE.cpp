// #pragma GCC optimize("Ofast,unroll-loops")
// #pragma GCC target("avx2")
#include <algorithm>
#include <bits/stdc++.h>
 
using namespace std;
using namespace std::chrono;


ostream& operator<<(ostream& o, const __int128& x) {
    if (x == numeric_limits<__int128>::min()) return o << "-170141183460469231731687303715884105728";
    if (x < 0) return o << "-" << -x;
    if (x < 10) return o << (char)(x + '0');
    return o << x / 10 << (char)(x % 10 + '0');
}
 
void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(__int128 x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}
template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...) 
#endif

int setbit(int x) {return __builtin_popcount(x);}
int setbit(long long x) {return __builtin_popcountll(x);}
int highbit(int x) {return (x==0?-1:31-__builtin_clz(x));}
int highbit(long long x) {return (x==0?-1:63-__builtin_clzll(x));}
int lowbit(int x) {return (x==0?-1:__builtin_ctz(x));}
int lowbit(long long x) {return (x==0?-1:__builtin_ctzll(x));}
#define ll long long
#define int ll
#define inf ((int)1e9 + 5)
#define inf_long_long (9223372036854775807LL/4)
#define endl "\n"
#define mod 1000000007
#define fastinput ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pb push_back
#define umap unordered_map
#define pii pair<int,int>
#define ppiii pair<pii, int>
#define pipii pair<int, pii>
#define sz(x) ((int) x.size())
#define forn(i,a,b) for(int i=a;i<=b;i++)
#define for0(i,a,b) for(int i=a;i>=b;i--)
#define all(x) x.begin(), x.end()
typedef tuple<int,int,int> tiii;
typedef __int128 i128;
template<typename T,typename U>
T ceil(T x, U y) {return (x>0?(x+y-1)/y:x/y);}
vector<int> factorials;
vector<int> invf;
int bpm(int a, int b) {if (b==0) {return 1;} int ret = bpm(a, b/2); ret = (1LL * ret * ret) % mod; if (b%2==1) {ret = (1LL * ret * a) % mod;} return ret;}
int gcd(int a, int b) {if (a==0) {return b;} if (b==0) {return a;}return gcd(b%a, a);}
int lcm(int a, int b) {return a/gcd(a,b)*b;}
int inv(int a) {return bpm(a, mod-2);}
void calcfacmod(int n) {factorials.resize(n+1);factorials[0] = 1;for (int i = 1; i <= n; i++) {factorials[i] = factorials[i-1]*i;factorials[i]%=mod;}}
mt19937_64 rngg(time(0));
ll RNG() {return rngg()%inf_long_long;} // IF CHANGE INT -> THEN CHANGE
void calcfac(int n) {calcfacmod(n);}

template<typename T>
void modpos(T &a) {T amt = (-a)/mod;amt++; amt = max(T(0), amt); a += amt*mod; a%=mod;}

int chs(int a, int b) {if (a<b || b < 0) {return 0;}if (b==a || b==0) {return 1;}return (((factorials[a]*invf[b])%mod)*invf[a-b])%mod;}
void calcinvfac(int n) {invf.resize(n);invf[n - 1] = inv(factorials[n - 1]);for (int i = n - 1; i > 0; i--) {invf[i - 1] = (invf[i] * i) % mod;}}
int ceil(int a, int b) {return (a / b) + (!!(a % b));}
// int paths(int a, int b) {return choose(a+b, a);}
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// template<typename T> 
// using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>; // remove #define int ll before use



// struct SegmentTree {
//     int n;
//     vector<int> a, st, lazy;

//     SegmentTree(int _n) : n(_n), st(4*n), lazy(4*n) {}

//     SegmentTree(const vector<int> &_a) : n((int) _a.size()), a(_a), st(4*n), lazy(4*n) {
//         build(1, 0, n-1);
//     }

//     int merge(int aa, int bb) {
//         return max(aa, bb); // change this to the wanted kind
//     }

//     int lazycalc(int val, int l, int r) {
//         return val;
//     }

//     void build(int p, int l, int r) {
//         if (l == r) {
//             st[p] = a[l];
//             return;
//         }
//         int m = (l + r) / 2;
//         build(2*p, l, m);
//         build(2*p+1, m+1, r);
//         st[p] = merge(st[2*p], st[2*p+1]);
//     }

//     void push(int p, int l, int r) {
//         if (lazy[p]) {
//             st[p] = lazycalc(lazy[p], l, r);
//             if (l != r) {
//                 lazy[2*p] = lazy[p];
//                 lazy[2*p+1] = lazy[p];
//             }
//             lazy[p] = 0;
//         }
//     }

//     int query(int p, int l, int r, int i, int j) {
//         push(p, l, r);
//         if (i > r || j < l)
//             return 0; // change for return value
//         if (i <= l && r <= j)
//             return st[p];
//         int m = (l + r) / 2;
//         return merge(query(2*p, l, m, i, j), query(2*p+1, m+1, r, i, j));
//     }

//     int query(int i, int j) {
//         return query(1, 0, n-1, i, j);
//     }

//     void update(int p, int l, int r, int i, int j, int val) {
//         push(p, l, r);
//         if (i > r || j < l)
//             return;
//         if (i <= l && r <= j) {
//             lazy[p] += val;
//             push(p, l, r);
//             return;
//         }
//         int m = (l + r) / 2;
//         update(2*p, l, m, i, j, val);
//         update(2*p+1, m+1, r, i, j, val);
//         st[p] = merge(st[2*p], st[2*p+1]);
//     }

//     void update(int i, int j, int val) {
//         update(1, 0, n-1, i, j, val);
//     }
// };

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    int rv=0;
    if (n>m) {
        swap(n,m);
        rv=1;
    }
    priority_queue<pair<int, pii> > pq;
    vector<pipii> pt(q);
    for (int i = 0; i < q; i++) {
        cin >> pt[i].second.first >> pt[i].second.second >> pt[i].first;
        if (rv) {
            swap(pt[i].second.first,pt[i].second.second);
        }
    }
    auto ds = [&](int x, int y, int j) {
        int p = pt[j].first;
        int r = pt[j].second.first;
        int c = pt[j].second.second;
        int ret = p*p-(x-r)*(x-r)-(y-c)*(y-c)+1;
        assert(ret > 0);
        return ret;
    };
    vector<vector<int> > gd(n, vector<int>(m, 0));
    // SegmentTree st(m);
    vector<pii> ops;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < q; j++) {
            int p = pt[j].first;
            int r = pt[j].second.first;
            int c = pt[j].second.second;
            int lf = p*p-(r-i)*(r-i);
            if (lf>=0) {
                int df = sqrt(lf);
                int lp = max(0LL, c-df);
                int rp = min(m-1, c+df);
                ops.pb({lp, j+1});
                ops.pb({rp+1,-(j+1)});
                // debug(i, r, c, p, lf, df, lp, rp);
                // st.update(lp, rp, j+1);
            }
        }
        sort(all(ops));
        int ps = 0;
        set<int> ms;
        for (int j = 0; j < m; j++) {
            while (ps<sz(ops)&&ops[ps].first<=j) {
                if(ops[ps].second<0) {
                    ms.erase(-ops[ps].second);
                } else {
                    ms.insert(ops[ps].second);
                }
                ps++;
            }
            int id = *ms.begin();
            if (!id) {
                gd[i][j] = 0;
                // cout << 0 << " ";
            } else {
                gd[i][j] = ds(i, j, id-1);
            }
        }
        // cout << endl;
    }
    if (rv) {
        swap(n, m);
    }
    // debug(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << (rv?gd[j][i]:gd[i][j]) << " ";
        }
        cout << endl;
    }
}

signed main() {
    fastinput;
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}