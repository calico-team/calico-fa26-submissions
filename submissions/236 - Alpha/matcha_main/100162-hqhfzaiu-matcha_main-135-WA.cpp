#include <bits/stdc++.h>
using namespace std;
using ll = long long;
vector<pair<int, int>> grp[30];
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
        for (auto &g : grp) g.clear();
        int fut[30] = {}, cnt[30] = {};
        auto addb = [&](int *a, int x, int d){
            for (int k = 0; k < 30; k++) if (x >> k & 1) a[k] += d; };
        int K = 0;
        for (int i = 0; i < n; i++){
            if (l[i] == r[i]){
                K ^= l[i]; continue;
            }
            int b = 31 - __builtin_clz(l[i] ^ r[i]);
            int M = (r[i] >> b) << b, P = (r[i] >> (b + 1)) << (b + 1);
            int w = r[i] - M, u = (1 << b) - 1 - (l[i] & ((1 << b) - 1));
            K ^= P ^ ((1 << b) - 1);
            grp[b].push_back({w, u});
            addb(fut, max(w, u), 1);
        }
        int F = 0, ans = 0;
        bool sat = false;
        for (int j = 29; j >= 0; j--){
            if (cnt[j] >= 2) sat = true;
            bool z = sat || cnt[j] >= 1;
            int c = (K >> j & 1) ^ F;
            auto &G = grp[j];
            int g = G.size();
            if (g == 0){
                if (z){
                    if (c){
                        ans |= (1 << (j + 1)) - 1; break;}
                    ans |= 1 << j;
                } else ans |= c << j; continue; }
            if (z){ ans |= (1 << (j + 1)) - 1; break;}
            ans |= 1 << j;
            int p = 1 ^ c;
            for (auto &[w, u] : G) addb(fut, max(w, u), -1);
            vector<char> s(g);
            int c1 = 0;
            for (int i = 0; i < g; i++){
                s[i] = G[i].first >= G[i].second; c1 += s[i]; }
            if ((c1 & 1) != p){
                int ctx[30];
                for (int k = 0; k < 30; k++) ctx[k] = cnt[k] + fut[k];
                for (int i = 0; i < g; i++) addb(ctx, s[i] ? G[i].first : G[i].second, 1);
                int best = -1, bi = 0;
                for (int i = 0; i < g; i++){
                    int hi = s[i] ? G[i].first : G[i].second;
                    int lo = s[i] ? G[i].second : G[i].first;
                    addb(ctx, hi, -1); addb(ctx, lo, 1);
                    int v = 0;
                    for (int k = j - 1; k >= 0; k--){
                        if (ctx[k] >= 2){ v |= (1 << (k + 1)) - 1; break; }
                        if (ctx[k] == 1) v |= 1 << k; }
                    if (v > best) best = v, bi = i;
                    addb(ctx, lo, -1); addb(ctx, hi, 1); }
                s[bi] ^= 1; }
            F ^= p;
            for (int i = 0; i < g; i++) addb(cnt, s[i] ? G[i].first : G[i].second, 1); }
        cout << ans << "\n";}}