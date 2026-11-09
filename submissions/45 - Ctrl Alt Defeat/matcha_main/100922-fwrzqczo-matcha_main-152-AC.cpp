#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// I am prettu sure we can always simplify a range to 2 choices of something xor range [0...something else]
// obviously ranges with higher set bits matter more

ll X;
vector<pair<ll,ll>> bucket[31];

// largest differing bit
void add(ll l, ll r) {
    if (l == r) { X ^= l; return; }
    int p = 63 - __builtin_clzll(l ^ r);
    ll mask = (1LL << (p + 1)) - 1;
    X ^= l & ~mask;
    bucket[p].push_back({l & mask, r & mask});
}

// largest value of x1^x2^...^xk with 0 <= xi <= v[i]
ll best(vector<ll> v) {
    ll res = 0;
    while (true) {
        sort(v.rbegin(), v.rend());
        if (v.empty() || v[0] == 0) return res;
        int h = 63 - __builtin_clzll(v[0]);
        if (v.size() > 1 && (v[1] >> h)) return res + (1LL << (h + 1)) - 1;
        res += 1LL << h;
        v[0] -= 1LL << h;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<ll> L(n), R(n);
        for (int i = 0; i < n; i++) cin >> L[i];
        for (int i = 0; i < n; i++) cin >> R[i];

        X = 0;
        for (int p = 0; p < 31; p++) bucket[p].clear();
        for (int i = 0; i < n; i++) add(L[i], R[i]);

        for (int p = 30; p >= 0; p--) {
            if (bucket[p].empty()) continue;
            vector<pair<ll,ll>> items = bucket[p];
            bucket[p].clear();

            ll H = 1LL << p, M = H - 1;
            int need = ((X >> p) & 1) ^ 1;
            int s = items.size();

            if (s == 1) {
                if (need) { X ^= H; add(0, items[0].second - H); }
                else add(items[0].first, M);
                continue;
            }

            vector<pair<ll,ll>> e;
            int on = 0;
            for (auto it : items) {
                ll a = it.second - H, d = M - it.first;
                if (a >= d) on++;
                e.push_back({max(a, d), min(a, d)});
            }
            sort(e.rbegin(), e.rend());

            int K = min(s, 34);
            vector<ll> top;
            for (int i = 0; i < K; i++) top.push_back(e[i].first);

            ll C;
            if (on % 2 == need) {
                C = best(top);
            } else {
                C = (s > K) ? best(top) : -1;
                for (int i = 0; i < K; i++) {
                    vector<ll> v = top;
                    v[i] = e[i].second;
                    if (s > K) v.push_back(e[K].first);
                    C = max(C, best(v));
                }
                on ^= 1;
            }
            if (on % 2) X ^= H;
            if ((s - on) % 2) X ^= M;
            add(0, C);
        }
        cout << X << "\n";
    }
}