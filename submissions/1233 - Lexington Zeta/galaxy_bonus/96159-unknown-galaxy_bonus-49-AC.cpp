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

int n, m;
vector<int> to;

int find(int x){
    if (to[x] == x) return x;
    return to[x] = find(to[x]);
}
int trans(int a, int b){
    return a * m + b;
}

void solve(){
    int q;
    cin >> n >> m >> q;
    to.resize(n * m + 1);
    vector<string> v(n);
    for (int i = 0; i < n; i++){
        cin >> v[i];
    }
    for (int i = 0; i <= n * m; i++){
        to[i] = i;
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (i != 0){
                if (v[i][j] == '.' || v[i][j] == v[i - 1][j]){
                    int ra = find(trans(i, j)), rb = find(trans(i - 1, j));
                    if (ra != rb){
                        to[ra] = rb;
                    }
                }
            }
            if (j != 0){
                if (v[i][j] == '.' || v[i][j] == v[i][j - 1]){
                    int ra = find(trans(i, j)), rb = find(trans(i, j - 1));
                    if (ra != rb){
                        to[ra] = rb;
                    }
                }
            }
            if (i != n - 1){
                if (v[i][j] == '.' || v[i][j] == v[i + 1][j]){
                    int ra = find(trans(i, j)), rb = find(trans(i + 1, j));
                    if (ra != rb){
                        to[ra] = rb;
                    }
                }
            }
            if (j != m - 1){
                if (v[i][j] == '.' || v[i][j] == v[i][j + 1]){
                    int ra = find(trans(i, j)), rb = find(trans(i, j + 1));
                    if (ra != rb){
                        to[ra] = rb;
                    }
                }
            }
        }
    }
    for (int i = 0; i < q; i++){
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        if (find(trans(a, b)) == find(trans(c, d))){
            cout << "YES\n";
        }
        else{
            cout << "NO\n";
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
