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

vector<int> e[200005];
vector<int> p(200005);
void dfs(int x, int par){
    p[x] = par;
    for (int y: e[x]){
        if (y == par) continue;
        dfs(y, x);
    }
}

void solve(){
    string s;
    cin >> s;
    if (s == "FIRST"){
        int n;
        cin >> n;
        for (int i = 0; i < n - 1; i++){
            int a, b;
            cin >> a >> b;
            e[a].push_back(b);
            e[b].push_back(a);
        }
        dfs(1, 1);
        for (int i = 1; i <= n; i++){
            cout << p[i] * 2 + (e[i].size() - (i != 1)) % 2 << " ";
        }
        cout << "\n";
    }
    else{
        int n;
        cin >> n;
        vector<int> v(n + 1);
        for (int i = 1; i <= n; i++){
            cin >> v[i];
        }
        vector<int> p(n + 1), child(n + 1);
        int blank = 0;
        for (int i = 1; i <= n; i++){
            if (v[i] != -1 && i != 1){
                p[i] = (v[i] / 2);
                child[p[i]]++;
            }
            else if (v[i] == -1){
                blank = i;
            }
        }
        if (blank != 1){
            for (int i = 1; i <= n; i++){
                if (child[i] % 2 != v[i] % 2){
                    if (i != blank){
                        p[blank] = i;
                    }
                }
            }
        }
        for (int i = 2; i <= n; i++){
            cout << p[i] << " " << i << "\n";
        }
    }
}

signed main() {
    IO
    
    int t = 1;
    //cin >> t;
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
