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

void solve(){
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> p(n + 1);
    vector<vector<int>> e(n + 1);
    for (int i = 1; i <= n; i++){
        cin >> p[i];
        e[p[i]].push_back(i);
    }
    queue<int> child;
    queue<int> no_child;
    for (int x: e[0]){
        if (e[x].size() == 0) no_child.push(x);
        else child.push(x);
    }
    int cnt = 0, it = 0;
    while (it < m && !(child.empty() && no_child.empty())){
        it++;
        int rep = child.size();
        rep = min(rep, k);
        int rep2 = min((int)no_child.size(), k - rep);
        for (int j = 0; j < rep; j++){
            cnt++;
            for (int y: e[child.front()]){
                if (e[y].size() == 0) no_child.push(y);
                else child.push(y);
            }
            child.pop();
        }
        for (int j = 0; j < rep2; j++){
            cnt++;
            no_child.pop();
        }
    }
    cout << cnt << "\n";
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
