
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ll t; cin >> t;
    while (t--){
        ll N, M, K; cin >> N >> M >> K;
        vector<ll> ID(N + 1);
        vector<vector<ll>> freq(N + 1);
        vector<ll> hijos(N + 1, 0);
        vector<ll> altura(N + 1, 1);
        for (ll i = 1; i <= N; i++){
            cin >> ID[i];
            freq[ID[i]].push_back(i);
            if (ID[i] != 0){
                hijos[ID[i]]++;
            }
        }
        queue<ll> q;
        vector<ll> restantes = hijos;
        for (ll i = 1; i <= N; i++){
            if (hijos[i] == 0){
                q.push(i);
            }
        }
        while (!q.empty()){
            ll u = q.front();
            q.pop();
            ll p = ID[u];
            if (p != 0) {
                altura[p] = max(altura[p], altura[u] + 1);
                restantes[p]--;
                if (restantes[p] == 0){
                    q.push(p);
                }
            }
        }
        priority_queue<pair<ll, ll>> idu;
        for (ll i = 1; i <= N; i++){
            if (ID[i] == 0){
                idu.push({altura[i], i});
            }
        }
        ll total = 0;
        while ((M--) && (!idu.empty())){
            ll s = min(K, (ll)idu.size());
            vector<ll> desb;
            total += s;
            for (ll i = 0; i < s; i++){
                ll curso = idu.top().second;
                idu.pop();
                for (ll c : freq[curso]){
                    desb.push_back(c);
                }
            }
            for (ll c : desb){
                idu.push({altura[c], c});
            }
        }
        cout << total << '\n';
    }
}
