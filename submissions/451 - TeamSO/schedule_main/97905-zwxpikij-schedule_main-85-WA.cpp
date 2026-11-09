#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ll t; cin >> t;
    while (t--){
        ll N, M, K; cin >> N >> M >> K;
        vector<ll> ID(N);
        vector<vector<ll>> freq(N + 1);
        vector<ll> idu;
        for (ll i = 0; i < N; i++){
            cin >> ID[i];
            freq[ID[i]].push_back(i + 1);
            if (ID[i] == 0) {
                idu.push_back(i + 1);
            }
        }
        ll total = 0;
        while ((M--) && (!idu.empty())){
            ll s = min((ll)idu.size(), K);
            vector<ll> desb;
            total += s;
            for (ll i = 0; i < s; i++){
                ll curso = idu[i];
                for (ll c : freq[curso]){
                    desb.push_back(c);
                }
            }
            vector<ll> sig;
            for (ll i = s; i < (ll)idu.size(); i++){
                sig.push_back(idu[i]);
            }
            for (ll c : desb){
                sig.push_back(c);
            }
            idu = sig;
        }
        cout << total << '\n';
    }
}