#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ll t; cin >> t;
    while (t--){
        ll N, M, K; cin >> N >> M >> K;
        vector<vector<ll>> freq(N + 1);
        vector<ll> idu;
        for (ll i = 1; i <= N; i++){
            ll p; cin >> p;
            freq[p].push_back(i);
            if (p == 0) {
                idu.push_back(i);
            }
        }
        ll total = 0;
        ll pos = 0;
        while ((M--) && (pos < (ll)idu.size())){
            ll s = min(K, (ll)idu.size() - pos);
            vector<ll> desb;
            for (ll i = 0; i < s; i++){
                ll curso = idu[pos + i];
                for (ll c : freq[curso]){
                    desb.push_back(c);
                }
            }
            pos += s;
            total += s;
            for (ll c : desb){
                idu.push_back(c);
            }
        }
        cout << total << '\n';
    }
}