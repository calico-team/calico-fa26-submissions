#include <bits/stdc++.h>
using namespace std;
#define fir first
#define sec second
template <class TT>
using vc=vector<TT>;

vector<int> solve_phase1(int n, vector<pair<int, int>>& E) {
    const int MOD=5e5;
    vc<int> fa(n+1);
    vc<vc<int>> adj(n+1);
    for(auto x : E){
        int u=x.fir, v=x.sec;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    auto dfs=[&](auto&& dfs, int u)->void
    {
        for(int v : adj[u]){
            if(v == fa[u]) continue;
            fa[v]=u;
            dfs(dfs, v);
        }
    };
    dfs(dfs, 1);
    vc<int> a(n);
    for(int i=2;i <= n;i++){
        a[i-1]=fa[i];
        a[0]=(a[0]+a[i-1])%MOD;
    }
    return a;
}

vector<pair<int, int>> solve_phase2(int n, vector<int>& a) {
    const int MOD=5e5;
    int pos=-1;
    for(int i=0;i < n;i++){
        if(a[i] == -1) pos=i;
    }
    if(pos != 0){
        int sum=0;
        for(int i=1;i < n;i++){
            if(i != pos) sum+=a[i];
        }
        a[pos]=(a[0]-sum+MOD)%MOD;
    }
    vc<pair<int, int>> E;
    for(int i=2;i <= n;i++){
        E.push_back({a[i-1], i});
    }
    return E;
}

int main() {
    string phase;
    cin >> phase;
    int N;
    cin >> N;

    if (phase == "FIRST") {
        vector<pair<int, int>> E(N - 1);
        for (int i = 0; i < N - 1; i++) {
            cin >> E[i].first >> E[i].second;
        }
        vector<int> A = solve_phase1(N, E);
        for (int i = 0; i < N; i++) {
            if (i > 0) cout << ' ';
            cout << A[i];
        }
        cout << '\n';
    } else {
        vector<int> A(N);
        for (int i = 0; i < N; i++) {
            cin >> A[i];
        }
        vector<pair<int, int>> edges = solve_phase2(N, A);
        for (auto& e : edges) {
            cout << e.first << ' ' << e.second << '\n';
        }
    }
}
