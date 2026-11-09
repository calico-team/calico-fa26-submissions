#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--){
        int n;
        cin >> n;
        vector<int> l(n), r(n);
        for (auto &x : l) cin >> x;
        for (auto &x : r) cin >> x;
        vector<pair<int, int>> g[30];
        int K = 0;
        for (int i = 0; i < n; i++){
            if (l[i] == r[i]){
                K ^= l[i];
                continue; }
            int b = 31 - __builtin_clz(l[i] ^ r[i]), m = (1 << b) - 1;
            K ^= (r[i] >> (b + 1) << (b + 1)) ^ m;
            g[b].push_back({r[i] & m, m - (l[i] & m)});}
        int c[30], a[30], cnt[30] = {}, F = 0;
        vector<vector<pair<int, int>>> cd;
        for (int k = 29; k >= 0; k--){
            c[k] = (K >> k & 1) ^ F;
            a[k] = !g[k].empty() || c[k];
            if (g[k].empty()) continue;
            int p = 1 ^ c[k], c1 = 0;
            vector<pair<int, int>> v;
            for (auto [w, u] : g[k]){
                c1 += w >= u;
                v.push_back({max(w, u), min(w, u)});
                for (int j = 0; j < 30; j++) cnt[j] += max(w, u) >> j & 1;}
            F ^= p;
            if ((c1 & 1) != p) cd.push_back(v);}
        int ans = 0;
        for (int k = 29; k >= 0; k--){
            int T = cnt[k];
            vector<int> mx;
            for (auto &v : cd){
                int b = -1;
                for (auto [h, o] : v) b = max(b, (o >> k & 1) - (h >> k & 1));
                mx.push_back(b);
                T += b;}
            if (T >= (a[k] ? 1 : 2)){
                ans |= (1 << (k + 1)) - 1;
                break;}
            ans |= (T >= 1 || a[k]) << k;
            for (int i = 0; i < (int)cd.size(); i++){
                int b = mx[i];
                cd[i].erase(remove_if(cd[i].begin(), cd[i].end(), [&](pair<int, int> x){ return (x.second >> k & 1) - (x.first >> k & 1) != b;}), cd[i].end());}}
        cout << ans << "\n";}}