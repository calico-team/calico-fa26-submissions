#include <bits/stdc++.h>
#define fore(v,l,r) for(ll v = (l); v < (r); v++)
#define sz(v) ll((v).size())
#define all(v) (v).begin(), (v).end()
#define pb push_back
using namespace std;
using ll = long long;
using vi = vector<ll>;
using ii = pair<ll,ll>;
constexpr ll INF = 1e18;

void solve() {
    int N, M, K; cin >> N >> M >> K;
    vector<vi> g(N);
    vi P(N);
    fore(i,0,N) {
        cin >> P[i]; P[i]--;
        if(P[i] != -1)
            g[P[i]].pb(i);    
    }

    vi sum(N,1), vis(N,0);
    auto dfs = [&](auto& f, int n) -> void {
        vis[n] = 1;
        for(auto k : g[n]) {
            if(!vis[n]) f(f, k);
            sum[n] += sum[k];
        }
    };

    fore(i,0,N) if(!vis[i])
        dfs(dfs, i);

    priority_queue<ii> greedy;
    fore(i,0,N) {
        if(P[i] == -1)
            greedy.push({sum[i], i});
    }

    ll ans = 0;
    fore(m,0,M) {
        if(greedy.empty()) break;
        vector<ii> as;
        fore(i,0,K) {
            if(greedy.empty()) break;
            auto[sm, n] = greedy.top();

            greedy.pop(); ans++;
            for(auto& k : g[n])
                as.pb({sum[i], k});
        }
        for(auto p : as) greedy.push(p);
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while(t--) solve();
    return 0;
}