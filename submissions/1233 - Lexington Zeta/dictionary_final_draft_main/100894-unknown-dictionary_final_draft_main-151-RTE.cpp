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

struct trie{
    vector<array<int, 2>> nxt;
    vector<int> cnt;
    int it = 1;
    trie(){
        nxt.push_back({-1, -1});
        cnt.push_back(0);
    }
    void clear(){
        nxt.clear();
        nxt.push_back({-1, -1});
        cnt.push_back(0);
        it = 1;
    }
    void insert(int x){
        int cur = 0;
        for (int i = 29; i >= 0; i--){
            if (nxt[cur][(x >> i) & 1] == -1){
                nxt[cur][(x >> i) & 1] = it;
                it++;
                nxt.push_back({-1, -1});
                cnt.push_back(0);
            }
            cur = nxt[cur][(x >> i) & 1];
            cnt[cur]++;
        }
    }
    void remove(int x){
        int cur = 0;
        for (int i = 29; i >= 0; i--){
            int prv = cur;
            cur = nxt[cur][(x >> i) & 1];
            cnt[cur]--;
            if (cnt[cur] == 0){
                nxt[prv][(x >> i) & 1] = -1;
            }
        }
    }
    int get_max(int x){
        int cur = 0, ans = 0;
        for (int i = 29; i >= 0; i--){
            if (nxt[cur][((x >> i) & 1) ^ 1] != -1){
                cur = nxt[cur][((x >> i) & 1) ^ 1];
                ans += (1 << i);
            }
            else{
                cur = nxt[cur][((x >> i) & 1)];
            }
        }
        return ans;
    }
};

vector<int> ans, prec;
int cur = 0;
trie tt;
int r = 0;
vector<trie> ts;
vector<int> vis;

void dfs(int x, vector<vector<int>> &e, vector<int> &cnd, vector<int> &v){
    cur ^= v[x];
    tt.insert(cur);
    ans[x] = max(ans[x], tt.get_max(cur));
    ans[x] = max(ans[x], ts.back().get_max(cur ^ prec[r] ^ v[r]));
    vis[x] = 1;
    for (int y: e[x]){
        if (!cnd[y]){
            dfs(y, e, cnd, v);
        }
    }
    tt.remove(cur);
    cur ^= v[x];
}

void solve(){
    int n;
    cin >> n;
    ans.resize(n + 1);
    prec.resize(n + 1);
    vis.resize(n + 1);
    for (int i = 1; i <= n; i++){
        ans[i] = 0; prec[i] = 0; vis[i] = 0;
    }
    vector<int> a(n + 1), v(n + 1), from(n + 1), cnd(n + 1); // prec = includes first node in cycle
    vector<vector<int>> e(n + 1);
    for (int i = 1; i <= n; i++){
        cin >> a[i];
        e[a[i]].push_back(i);
    }
    for (int i = 1; i <= n; i++){
        cin >> v[i];
    }
    ts.clear();
    for (int i = 1; i <= n; i++){
        if (!vis[i]){
            stack<int> nodes;
            nodes.push(i);
            vis[i] = 1;
            int cur = a[i];
            while (!vis[cur]){
                vis[cur] = 1;
                nodes.push(cur);
                cur = a[cur];
            }
            vector<int> cyc;
            while (nodes.top() != cur){
                cyc.push_back(nodes.top());
                nodes.pop();
            }
            cyc.push_back(cur);
            reverse(cyc.begin(), cyc.end());
            int cx = 0;
            for (int i = 0; i < 2 * cyc.size(); i++){
                if (i < cyc.size()){
                    prec[cyc[i]] = cx;
                    cnd[cyc[i]] = 1;
                }
                cx ^= v[cyc[i % cyc.size()]];
                tt.insert(cx);
            }
            ts.push_back(tt);

            for (int rt: cyc){
                tt.clear();
                r = rt;
                dfs(rt, e, cnd, v);
            }
            tt.clear();
        }
    }
    for (int i = 1; i <= n; i++){
        cout << ans[i] << " ";
    }
    cout << "\n";
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
