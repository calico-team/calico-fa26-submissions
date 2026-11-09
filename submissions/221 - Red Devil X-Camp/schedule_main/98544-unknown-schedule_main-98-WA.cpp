#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve(){
    ll n, m, k;

    cin >> n >> m >> k;

    priority_queue<pair<ll, ll>> pq;
    vector<vector<ll>> adj(n+1);
    vector<ll> root;
    vector<bool> visited(n+1);

    for(ll i = 1; i<=n; i++){ll x; cin >> x; (x == 0) ? root.push_back(i) : adj[x].push_back(i);}
    for(ll v : root) pq.push({adj[v].size(), v});

    for(ll i = 0; i<m; i++){
        ll s_mx = min(k, (ll)pq.size());

        for(ll j = 0; j<s_mx; j++){

            ll node = pq.top().second;
            pq.pop();

            if(visited[node]) continue;
            visited[node] = true;

            for(ll c : adj[node]){
                if(visited[c]) continue;

                pq.push({adj[c].size(), c});
            }

        }
    }

    ll cnt = 0;
    for(ll i = 1; i<=n; i++) if(visited[i]) cnt++;

    cout << cnt << '\n';
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll t;
    cin >> t;

    while(t--) solve();
}