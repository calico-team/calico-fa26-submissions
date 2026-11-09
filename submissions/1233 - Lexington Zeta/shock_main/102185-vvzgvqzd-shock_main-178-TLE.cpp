#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops,inline")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt")
using namespace std;

#define IO cin.tie(0);cin.sync_with_stdio(0);
#define int long long
#define double long double
#define F first
#define S second
#define pb push_back
#define all(a) a.begin(),a.end()
#define SZ(a) ((int)a.size())

using ll=long long;
using pii=pair<int, int>;
using pipii=pair<int, pii>;
using ppi=pair<pii, int>;
using ppipi=pair<pii,pii>;

template<typename T> using min_heap=priority_queue<T,vector<T>,greater<T>>;
template<typename T> using max_heap=priority_queue<T>;
template<typename T> using vv=vector<vector<T>>;
template<typename T> using vvv=vector<vector<vector<T>>>;

using vi=vector<int>;
using vpi=vector<pii>;
using vvi=vv<int>;
using vvpi=vv<pii>;
using vvvi=vvv<int>;
using vvvpi=vvv<pii>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rd(int l, int r){ return uniform_int_distribution<int>(l, r)(rng);}
template<typename T, typename S> T ifloor(T a, S b){return a/b-(a%b&&(a^b)<0);}
template<typename T, typename S> T iceil(T a, S b){return ifloor(a+b-1,b);}
void FIO(string s){freopen((s+".in").c_str(),"r",stdin);freopen((s+".out").c_str(),"w",stdout);}


void solve() {
    int n, m, q;
    cin >> n >> m >> q;

    vi r(q), c(q), p(q);
    int sw = 0;
    if (n > m){
        swap(n, m);
        sw = 1;
    }
    for (int i = 0; i < q; ++i) {
        cin >> r[i] >> c[i] >> p[i];
        if (sw){
            swap(r[i], c[i]);
        }
    }
    
    vvi ans(n, vi(m, 0));
    for (int x = 0; x < n; ++x) {
        // find active intervals
        vi f(q);
        for (int i = 0; i < q; ++i) {
            f[i] = p[i] * p[i] - (x - r[i]) * (x - r[i]) - c[i] * c[i] + 1;
        }

        vpi intervals(q);
        set<pair<int, int>> open; // y, priority
        set<pair<int, int>> close; // y, priority
        for (int i = 0; i < q; ++i) {
            intervals[i].F = max(min((int)floor(c[i] - sqrt(c[i] * c[i] + f[i]) + 1), m - 1), 0LL);
            intervals[i].S = max(min((int)ceil(c[i] + sqrt(c[i] * c[i] + f[i]) - 1), m - 1), 0LL);
    
            if (c[i] * c[i] + f[i] > 0) {
                open.insert({intervals[i].F, i});
                close.insert({intervals[i].S, i});
            }
        }
    
        // do weird set things
        set<int> active;
        for (int y = 0; y < m; ++y) {
            while (open.size() > 0 && (*open.begin()).F == y) {
                active.insert((*open.begin()).S);
                open.erase(open.begin());
            }
    
            if (active.size() > 0) {
                int it = *active.rbegin();
                ans[x][y] = p[it] * p[it] - (x - r[it]) * (x - r[it]) - (y - c[it]) * (y - c[it]) + 1;
            }
            
            while (close.size() > 0 && (*close.begin()).F == y) {
                active.erase((*close.begin()).S);
                close.erase(close.begin());
            }
        }
    }

    if (!sw){
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << ans[i][j] << ' ';
        }
        cout << "\n";
    }
    }
    else{
        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){
                cout << ans[j][i] << ' ';
            }
        cout << "\n";
        }
    }
}

signed main() {
    IO
    
    int t = 1;
    cin >> t;
    while (t--){
        solve();
    }
}

/*
 ____   ___    ___     ____  _____          ____    ____   ___
|      |   |  |   \   |        |     /|    |       |      |   \
|      |   |  |    |  |____    |      |    |   _   |____  |___/
|      |   |  |    |  |        |      |    |    |  |      |  \
|____  |___|  |___/   |____    |    __|__  |____|  |____  |   \
 
*/
