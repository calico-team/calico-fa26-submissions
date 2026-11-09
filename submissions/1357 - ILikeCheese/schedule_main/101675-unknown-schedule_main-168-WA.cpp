#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    ll N,M,K; cin >> N >> M >> K;
    vector<ll> P(N);
    for (ll i=0; i<N; i++) cin >> P[i];
    ll ans = count(P.begin(),P.end(),0);
    vector<ll> curr = {0};
    while (M!=0) {
        M--;
        vector<ll> index;
        for (ll i=0; i<N; i++) {
            if (count(curr.begin(),curr.end(),P[i])) index.push_back(i+1);
        }
        curr = index;
        ans+=min<ll>(K,curr.size());
    }
    cout << max<ll>(ans-count(P.begin(),P.end(),0),ans-min<ll>(K,curr.size())) << endl;
}

int main() {
    int t; cin >> t;
    while (t--) {
        solve();
    }
}