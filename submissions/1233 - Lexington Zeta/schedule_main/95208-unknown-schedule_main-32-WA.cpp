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

vector<vector<int>> e;
vector<int> dep;

void dfs(int x, int par){
    for (int y: e[x]){
        dfs(y, x);
        dep[x] = max(dep[y] + 1, dep[x]);
    }
}

void solve(){
    int n, m, k;
    cin >> n >> m >> k;
    e.resize(n + 1);
    dep.resize(n + 1);
    vector<int> p(n + 1);
    priority_queue<pair<int, int>> pq;
    for (int i = 1; i <= n; i++){
        cin >> p[i];
        e[p[i]].push_back(i);
    }
    for (int x: e[0]){
        pq.push({e[x].size(), x});
    }
    int cnt = 0, it = 0;
    while (it < m && !pq.empty()){
        it++;
        vector<pair<int, int>> newp;
        for (int i = 0; i < k && !pq.empty(); i++){
            pair<int, int> p = pq.top();
            pq.pop();
            for (int y: e[p.second]){
                newp.push_back({e[y].size(), y});
            }
            cnt++;
        }
        for (pair<int, int> p: newp){
            pq.push(p);
        }
    }
    cout << cnt << "\n";
    e.clear();
    dep.clear();
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
